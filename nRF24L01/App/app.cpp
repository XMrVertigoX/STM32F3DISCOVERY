#include <stm32f3xx_hal.h>

#include "gpio.hpp"
#include "radiotask.hpp"
#include "spi.hpp"

static Gpio nRF24L01_CE(GPIOF, GPIO_PIN_2);
static Gpio nRF24L01_IRQ(GPIOC, GPIO_PIN_2);
static Spi nRF24L01_SPI;

static nRF24L01 nRF24L01(nRF24L01_SPI, nRF24L01_CE, nRF24L01_IRQ);

static RadioTask radioTask(nRF24L01);
