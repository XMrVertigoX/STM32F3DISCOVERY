#include <assert.h>
#include <string.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <spi.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/templates/queue.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

static uint32_t spiTimeout = 1000;

namespace xXx {

Gpio *Spi::_cs[2];
SemaphoreHandle_t Spi::_semaphore;

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(&hspi) {
    if (_hspi == &hspi2) {
        _cs[0] = &cs;
    } else if (_hspi == &hspi3) {
        _cs[1] = &cs;
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

uint8_t Spi::transmit_receive(Queue<uint8_t> &mosiQueue, Queue<uint8_t> &misoQueue) {
    xSemaphoreTake(_semaphore, portMAX_DELAY);

    if (_hspi == &hspi2) {
        _cs[0]->clear();
    } else if (_hspi == &hspi3) {
        _cs[1]->clear();
    }

    uint8_t numBytes = mosiQueue.usedSlots();

    uint8_t mosiBytes[numBytes];
    uint8_t misoBytes[numBytes];

    for (int i = 0; i < numBytes; ++i) {
        mosiQueue.dequeue(mosiBytes[i]);
    }

    HAL_StatusTypeDef status =
        HAL_SPI_TransmitReceive(_hspi, mosiBytes, misoBytes, numBytes, spiTimeout);

    assert(status == HAL_OK);

    for (int i = 0; i < numBytes; ++i) {
        misoQueue.enqueue(misoBytes[i]);
    }

    if (_hspi == &hspi2) {
        _cs[0]->set();
    } else if (_hspi == &hspi3) {
        _cs[1]->set();
    }

    xSemaphoreGive(_semaphore);

    // TODO: Return actual status
    return (0);
}

void Spi::irq(SPI_HandleTypeDef *hspi) {
    LOG("IRQ");
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    Spi::irq(hspi);
}

} /* namespace xXx */
