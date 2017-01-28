#include <stm32f3xx_hal.h>

#include <spi.h>

#include "gpio.hpp"
#include "myTask.hpp"
#include "spi.hpp"

static Gpio nRF24L01_1_CE(GPIOD, GPIO_PIN_13);
static Gpio nRF24L01_1_IRQ(GPIOB, GPIO_PIN_11);
static Gpio nRF24L01_1_CSN(GPIOD, GPIO_PIN_15);
static Spi nRF24L01_1_SPI(hspi2, nRF24L01_1_CSN);
static nRF24L01P_API nRF24L01_1(nRF24L01_1_SPI, nRF24L01_1_CE, nRF24L01_1_IRQ);

static Gpio nRF24L01_2_CE(GPIOF, GPIO_PIN_6);
static Gpio nRF24L01_2_IRQ(GPIOC, GPIO_PIN_9);
static Gpio nRF24L01_2_CS(GPIOA, GPIO_PIN_15);
static Spi nRF24L01_2_SPI(hspi3, nRF24L01_2_CS);
static nRF24L01P_API nRF24L01_2(nRF24L01_2_SPI, nRF24L01_2_CE, nRF24L01_2_IRQ);

static MyTask myTask(nRF24L01_1, nRF24L01_2);
