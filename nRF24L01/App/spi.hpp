#ifndef SPI_HPP_
#define SPI_HPP_

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <xXx/interfaces/ispi.hpp>
#include <xXx/os/arduinotask.hpp>
#include <xXx/templates/queue.hpp>

#include "gpio.hpp"

namespace xXx {

class Spi : public ISpi {
  private:
    SPI_HandleTypeDef *_hspi;
    Gpio &_cs;

    static SemaphoreHandle_t _semaphore[2];

  public:
    Spi(SPI_HandleTypeDef &hspi, Gpio &cs);
    ~Spi();

    uint8_t transmit_receive(Queue<uint8_t> &mosiQueue, Queue<uint8_t> &misoQueue);

    static void irq(SPI_HandleTypeDef *hspi);
};

} /* namespace xXx */

#endif /* SPI_HPP_ */
