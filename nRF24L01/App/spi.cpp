#include <assert.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <task.h>

#include <spi.h>

#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "spi.hpp"

namespace xXx {

Spi::Spi(SPI_HandleTypeDef &hspi, Gpio &cs) : _hspi(hspi), _cs(cs) {}

Spi::~Spi() {}

uint8_t Spi::transmit(uint8_t mosiBytes[], uint8_t misoBytes[],
                      size_t numBytes) {
    portENTER_CRITICAL();

    _cs.clear();

    // TODO: Magic timeout number: Timeout after 1000 ms. Why? I don't know...
    HAL_StatusTypeDef status =
        HAL_SPI_TransmitReceive(&_hspi, mosiBytes, misoBytes, numBytes, 1000);

    assert(status == HAL_OK);

    _cs.set();

    portEXIT_CRITICAL();

    // TODO: Return actual status
    return (0);
}

} /* namespace xXx */
