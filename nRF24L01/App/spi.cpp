#include <assert.h>
#include <string.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <spi.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

namespace xXx {

Gpio *Spi::_foo[2];
SemaphoreHandle_t Spi::_semaphore;
ISpi_Callback_t Spi::_callback[2];
void *Spi::_user[2];

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(&hspi) {
    if (_hspi == &hspi2) {
        _foo[0] = &cs;
    } else if (_hspi == &hspi3) {
        _foo[1] = &cs;
    }

    vSemaphoreCreateBinary(_semaphore);
}

Spi::~Spi() {}

uint8_t Spi::transmit(uint8_t mosiBytes[], size_t numBytes) {
    return (1);
}

uint8_t Spi::receive(uint8_t misoBytes[], size_t numBytes) {
    return (1);
}

uint8_t Spi::transmit_receive(Queue<uint8_t> mosiQueue,
                              Queue<uint8_t> misoQueue, ISpi_Callback_t cb,
                              void *user) {
    xSemaphoreTake(_semaphore, portMAX_DELAY);

    if (_hspi == &hspi2) {
        _callback[0] = cb;
        _user[0]     = user;
        _foo[0]->clear();
    } else if (_hspi == &hspi3) {
        _callback[1] = cb;
        _user[1]     = user;
        _foo[1]->clear();
    }

    HAL_StatusTypeDef status =
        HAL_SPI_TransmitReceive_IT(_hspi, mosiBytes, misoBytes, numBytes);

    assert(status == HAL_OK);

    // TODO: Return actual status
    return (0);
}

void Spi::irq(SPI_HandleTypeDef *hspi) {
    if (hspi == &hspi2) {
        if (_callback[0]) {
            _callback[0](_user[0]);
        }

        _foo[0]->set();
    } else if (hspi == &hspi3) {
        if (_callback[1]) {
            _callback[1](_user[1]);
        }

        _foo[1]->set();
    }

    xSemaphoreGiveFromISR(_semaphore, NULL);
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {}

extern "C" void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {}

extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    Spi::irq(hspi);
}

} /* namespace xXx */
