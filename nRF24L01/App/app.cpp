#include <stm32f3xx_hal.h>

#include "gpio.hpp"
#include "radiotask.hpp"
#include "spi.hpp"

static Gpio nRF24L01_1_CE(GPIOF, GPIO_PIN_2);
static Gpio nRF24L01_1_IRQ(GPIOC, GPIO_PIN_2);
static Gpio nRF24L01_1_CS(GPIOB, GPIO_PIN_12);
static Spi nRF24L01_1_SPI(nRF24L01_1_CS);
static nRF24L01P nRF24L01_1(nRF24L01_1_SPI, nRF24L01_1_CE, nRF24L01_1_IRQ);

static Gpio nRF24L01_2_CE(GPIOD, GPIO_PIN_13);
static Gpio nRF24L01_2_IRQ(GPIOB, GPIO_PIN_11);
static Gpio nRF24L01_2_CS(GPIOD, GPIO_PIN_15);
static Spi nRF24L01_2_SPI(nRF24L01_2_CS);
static nRF24L01P nRF24L01_2(nRF24L01_2_SPI, nRF24L01_2_CE, nRF24L01_2_IRQ);

static RadioTask radioTask(nRF24L01_1, nRF24L01_2);
