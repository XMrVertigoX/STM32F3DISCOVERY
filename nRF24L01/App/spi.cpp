#include <stm32f3xx_hal.h>

#include <spi.h>

#include "spi.hpp"

namespace xXx {

Spi::Spi(Gpio &cs) : _cs(cs) {}

Spi::~Spi() {}

uint8_t Spi::transmit(uint8_t mosiBytes[], uint8_t misoBytes[],
                      size_t numBytes) {
    _cs.clear();

    // TODO: Magic timeout number: Timeout after 1000 ms. Why? I don't know...
    HAL_SPI_TransmitReceive(&hspi2, mosiBytes, misoBytes, numBytes, 1000);

    _cs.set();

    // TODO: Return actual status
    return (0);
}

} /* namespace xXx */
