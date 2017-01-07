#ifndef SPI_HPP_
#define SPI_HPP_

#include <xXx/interfaces/ispi.hpp>

namespace xXx {

class Spi : public ISpi {
  public:
    Spi();
    ~Spi();

    uint8_t transmit(uint8_t mosiBytes[], uint8_t misoBytes[], size_t numBytes);
};

} /* namespace xXx */

#endif /* SPI_HPP_ */
