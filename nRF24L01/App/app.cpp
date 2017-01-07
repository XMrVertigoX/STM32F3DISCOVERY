#include <stm32f3xx_hal.h>

#include "gpio.hpp"
#include "radiotask.hpp"

static Gpio nRF24L01_CE(GPIOF, GPIO_PIN_2);
static Gpio nRF24L01_IRQ(GPIOC, GPIO_PIN_2);

static RadioTask radioTask;
