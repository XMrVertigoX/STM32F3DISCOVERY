#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stm32f3xx_hal_conf.h>

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/templates/queue.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "led.hpp"
#include "spi.hpp"

const uint64_t address = 0xE7E7E7E7E7;

union {
    uint8_t m8[sizeof(uint32_t)];
    uint32_t m32 = 1;
} counter;

extern SPI_HandleTypeDef hspi2;

Gpio port1_CE(PORT1_CE_GPIO_Port, PORT1_CE_Pin);
Gpio port1_CS(PORT1_CS_GPIO_Port, PORT1_CS_Pin);
Gpio port1_INT(PORT1_INT_GPIO_Port, PORT1_INT_Pin);

Gpio port2_CE(PORT2_CE_GPIO_Port, PORT2_CE_Pin);
Gpio port2_CS(PORT2_CS_GPIO_Port, PORT2_CS_Pin);
Gpio port2_INT(PORT2_INT_GPIO_Port, PORT2_INT_Pin);

Spi port1_SPI(hspi2, port1_CS);
Spi port2_SPI(hspi2, port2_CS);

Gpio button(BUTTON_GPIO_Port, BUTTON_Pin);

nRF24L01P_ESB transmitter(port1_SPI, port1_CE, port1_INT);
nRF24L01P_ESB receiver(port2_SPI, port2_CE, port2_INT);

Led led[] = {Led(LD3), Led(LD5), Led(LD7), Led(LD9), Led(LD10), Led(LD8), Led(LD6), Led(LD4)};

static void txCallback(int8_t numRetries, void* user) {
    LOG("numRetries: %d", numRetries);
    //    counter.m32++;
    //    transmitter.queueTransmission(counter.m8, sizeof(counter), txCallback, NULL);
    //    transmitter.notify();
};

static void rxCallback(uint8_t bytes[], size_t numBytes, void* user) {
    LOG("%d", *(reinterpret_cast<uint32_t*>(bytes)));
};

static void buttonCallback(void* user){
    //    button.disableInterrupt();
    //    transmitter.queueTransmission(counter.m8, sizeof(counter), txCallback, NULL);
    //    led[1].toggle();
    //    transmitter.notifyFromISR();
};

extern "C" void initializeApplication() {
    transmitter.create(256, Task_Priority_MID);
    receiver.create(256, Task_Priority_HIGH);
}

extern "C" void applicationTaskFunction(void const* argument) {
    vTaskDelay(1000);

    button.enableInterrupt(buttonCallback, NULL);

    transmitter.configureTxPipe(address);
    transmitter.setDataRate(DataRate_1MBPS);
    transmitter.setCrcConfig(CrcConfig_2Bytes);
    transmitter.setChannel(2);
    transmitter.setOutputPower(OutputPower_m18dBm);
    transmitter.setRetryCount(0xF);
    transmitter.setRetryDelay(0xF);
    transmitter.switchOperatingMode(OperatingMode_Tx);

    receiver.configureRxPipe(0, address);
    receiver.setDataRate(DataRate_1MBPS);
    receiver.setCrcConfig(CrcConfig_2Bytes);
    receiver.setChannel(2);
    receiver.setOutputPower(OutputPower_m18dBm);
    receiver.switchOperatingMode(OperatingMode_Rx);

    receiver.startListening(0, rxCallback, NULL);

    for (;;) {
        led[0].toggle();
        transmitter.queueTransmission(counter.m8, sizeof(counter), txCallback, NULL);
        transmitter.notify();
        vTaskDelay(250);
        led[0].toggle();
        vTaskDelay(250);
    }
}
