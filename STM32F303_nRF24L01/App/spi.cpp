#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <spi.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/templates/queue.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

namespace xXx {

SemaphoreHandle_t Spi::_semaphore[2];

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(&hspi), _cs(cs) {
    if (_semaphore[0] == NULL) {
        vSemaphoreCreateBinary(_semaphore[0]);
    }

    if (_semaphore[1] == NULL) {
        _semaphore[1] = xSemaphoreCreateBinary();
    }
}

Spi::~Spi() {}

uint8_t Spi::transmit_receive(uint8_t bytes[], uint32_t numBytes) {
    BaseType_t semaphoreTaken;
    HAL_StatusTypeDef spiStatus;

    semaphoreTaken = xSemaphoreTake(_semaphore[0], portMAX_DELAY);

    if (semaphoreTaken == pdFALSE) {
        return (EXIT_FAILURE);
    }

    _cs.clear();

    spiStatus = HAL_SPI_TransmitReceive_DMA(_hspi, bytes, bytes, numBytes);
    assert(spiStatus == HAL_OK);

    semaphoreTaken = xSemaphoreTake(_semaphore[1], portMAX_DELAY);

    _cs.set();

    if (semaphoreTaken == pdFALSE) {
        return (EXIT_FAILURE);
    }

    xSemaphoreGive(_semaphore[0]);

    return (EXIT_SUCCESS);
}

void Spi::irq(SPI_HandleTypeDef *hspi) {
    BaseType_t higherPriorityTaskWoken;

    xSemaphoreGiveFromISR(_semaphore[1], &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
    LOG("HAL_SPI_ErrorCallback");
}

extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    Spi::irq(hspi);
}

} /* namespace xXx */
