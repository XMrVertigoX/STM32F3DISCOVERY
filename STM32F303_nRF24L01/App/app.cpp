#include <stm32f3xx_hal_conf.h>

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "mytask.hpp"
#include "spi.hpp"

#include "../Inc/main.h"

extern SPI_HandleTypeDef hspi2;

static Gpio port1_CE(PORT1_CE_GPIO_Port, PORT1_CE_Pin);
static Gpio port1_CS(PORT1_CS_GPIO_Port, PORT1_CS_Pin);
static Gpio port1_INT(PORT1_INT_GPIO_Port, PORT1_INT_Pin);

static Gpio port2_CE(PORT2_CE_GPIO_Port, PORT2_CE_Pin);
static Gpio port2_CS(PORT2_CS_GPIO_Port, PORT2_CS_Pin);
static Gpio port2_INT(PORT2_INT_GPIO_Port, PORT2_INT_Pin);

static Spi port1_SPI(hspi2, port1_CS);
static Spi port2_SPI(hspi2, port2_CS);

static nRF24L01P_ESB transmitter(port1_SPI, port1_CE, port1_INT);
static nRF24L01P_ESB receiver(port2_SPI, port2_CE, port2_INT);

static MyTask myTask(transmitter, receiver);

extern "C" void appInit() {
    LOG("%s", __FUNCTION__);

    transmitter.taskCreate();
    receiver.taskCreate();
    myTask.taskCreate();
}
