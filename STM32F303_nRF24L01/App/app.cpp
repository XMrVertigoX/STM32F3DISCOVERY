#include <stm32f3xx_hal_conf.h>

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/utils/logging.hpp>

#include "../Inc/main.h"

#include "gpio.hpp"
#include "radiotask.hpp"
#include "spi.hpp"

extern SPI_HandleTypeDef hspi2;

Gpio port1_CE(PORT1_CE_GPIO_Port, PORT1_CE_Pin);
Gpio port1_CS(PORT1_CS_GPIO_Port, PORT1_CS_Pin);
Gpio port1_INT(PORT1_INT_GPIO_Port, PORT1_INT_Pin);

Gpio port2_CE(PORT2_CE_GPIO_Port, PORT2_CE_Pin);
Gpio port2_CS(PORT2_CS_GPIO_Port, PORT2_CS_Pin);
Gpio port2_INT(PORT2_INT_GPIO_Port, PORT2_INT_Pin);

Spi port1_SPI(hspi2, port1_CS);
Spi port2_SPI(hspi2, port2_CS);

nRF24L01P_ESB transmitter(port1_SPI, port1_CE, port1_INT);
nRF24L01P_ESB receiver(port2_SPI, port2_CE, port2_INT);

RadioTask radioTask(transmitter, receiver);

extern "C" void appInit() {
    radioTask.taskCreate();
}
