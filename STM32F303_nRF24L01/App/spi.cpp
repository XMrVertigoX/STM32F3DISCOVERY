#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stm32f3xx_hal_conf.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/templates/queue.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

namespace xXx {

SemaphoreHandle_t Spi::_semaphore[2];

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(&hspi), _cs(cs) {
    if (_semaphore[0] == NULL) {
        _semaphore[0] = xSemaphoreCreateBinary();
        assert(_semaphore[0] != NULL);
    }

    if (_semaphore[1] == NULL) {
        _semaphore[1] = xSemaphoreCreateBinary();
        assert(_semaphore[1] != NULL);
    }

    xSemaphoreGive(_semaphore[0]);

    assert(uxSemaphoreGetCount(_semaphore[0]) == 1);
    assert(uxSemaphoreGetCount(_semaphore[1]) == 0);
}

Spi::~Spi() {}

uint8_t Spi::transmit_receive(uint8_t txBytes[], uint8_t rxBytes[], size_t numBytes) {
    xSemaphoreTake(_semaphore[0], portMAX_DELAY);
    _cs.clear();
    taskENTER_CRITICAL();

    HAL_SPI_TransmitReceive_IT(_hspi, txBytes, rxBytes, numBytes);

    taskEXIT_CRITICAL();
    xSemaphoreTake(_semaphore[1], portMAX_DELAY);
    _cs.set();
    xSemaphoreGive(_semaphore[0]);

    assert(uxSemaphoreGetCount(_semaphore[0]) == 1);
    assert(uxSemaphoreGetCount(_semaphore[1]) == 0);

    return (EXIT_SUCCESS);
}

void Spi::irq(SPI_HandleTypeDef *hspi) {
    xSemaphoreGiveFromISR(_semaphore[1], NULL);
}

extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
    LOG("HAL_SPI_ErrorCallback");
}

extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    Spi::irq(hspi);
}

} /* namespace xXx */
