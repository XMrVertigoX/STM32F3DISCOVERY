#include <assert.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <spi.h>

#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

namespace xXx {

Gpio *Spi::_foo[2];

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(&hspi) {
    if (_hspi == &hspi2) {
        _foo[0] = &cs;
    } else if (_hspi == &hspi3) {
        _foo[1] = &cs;
    }
}

Spi::~Spi() {}

uint8_t Spi::transmit(uint8_t mosiBytes[], size_t numBytes) {
    return (1);
}

uint8_t Spi::receive(uint8_t misoBytes[], size_t numBytes) {
    return (1);
}

uint8_t Spi::transmit_receive(uint8_t mosiBytes[], uint8_t misoBytes[],
                              size_t numBytes) {
    if (_hspi == &hspi2) {
        _foo[0]->clear();
    } else if (_hspi == &hspi3) {
        _foo[1]->clear();
    }

    HAL_StatusTypeDef status =
        HAL_SPI_TransmitReceive_IT(_hspi, mosiBytes, misoBytes, numBytes);

    assert(status == HAL_OK);

    //    BUFFER("mosiBytes", mosiBytes, numBytes);
    //    BUFFER("misoBytes", misoBytes, numBytes);

    if (_hspi == &hspi2) {
        _foo[0]->set();
    } else if (_hspi == &hspi3) {
        _foo[1]->set();
    }

    // TODO: Return actual status
    return (0);
}

void Spi::irq(SPI_HandleTypeDef *hspi) {
    if (hspi == &hspi2) {
        _foo[0]->set();
    } else if (hspi == &hspi3) {
        _foo[1]->set();
    }
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {}

extern "C" void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {}

extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    Spi::irq(hspi);
}

} /* namespace xXx */
