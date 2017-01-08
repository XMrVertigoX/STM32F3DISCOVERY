#ifndef SPI_HPP_
#define SPI_HPP_

#include <stm32f3xx_hal.h>

#include <xXx/interfaces/ispi.hpp>

#include "gpio.hpp"

namespace xXx {

class Spi : public ISpi {
  private:
    Gpio &_cs;

  public:
    Spi(Gpio &cs);
    ~Spi();

    uint8_t transmit(uint8_t mosiBytes[], uint8_t misoBytes[], size_t numBytes);
};

} /* namespace xXx */

#endif /* SPI_HPP_ */
