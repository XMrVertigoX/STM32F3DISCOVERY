#ifndef SPI_HPP_
#define SPI_HPP_

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <xXx/interfaces/ispi.hpp>
#include <xXx/os/arduinotask.hpp>

#include "gpio.hpp"

namespace xXx {

class Spi : public ISpi {
  private:
    SPI_HandleTypeDef *_hspi;

    static ISpi_Callback_t _callback[];
    static void *_user[];
    static Gpio *_foo[];
    static SemaphoreHandle_t _semaphore;

  public:
    Spi(SPI_HandleTypeDef &hspi, Gpio &cs);
    ~Spi();

    uint8_t transmit(uint8_t mosiBytes[], size_t numBytes);
    uint8_t receive(uint8_t misoBytes[], size_t numBytes);
    uint8_t transmit_receive(Queue<uint8_t> mosiQueue, Queue<uint8_t> misoQueue,
                             ISpi_Callback_t callback, void *user);

    static void irq(SPI_HandleTypeDef *hspi);
};

} /* namespace xXx */

#endif /* SPI_HPP_ */
