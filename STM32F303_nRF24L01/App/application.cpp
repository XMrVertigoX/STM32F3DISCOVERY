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

const uint32_t baseAddress_0 = 0xE7E7E7E7;
const uint32_t baseAddress_1 = 0xC2C2C2C2;
const uint8_t addressPrefix  = 0xE7;

union Counter_t {
    uint8_t m8[4];
    uint32_t m32;
};

Counter_t counter = {.m32 = 0};

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
    counter.m32++;

    if (numRetries > 0) {
        LOG("numRetries: %d", numRetries);
    }
};

static void rxCallback(uint8_t bytes[], size_t numBytes, void* user) {
    BUFFER("bytes:", bytes, numBytes);
};

static void buttonCallback(void* user){
    //    button.disableInterrupt();
    //    transmitter.queueTransmission(counter.m8, sizeof(counter), txCallback, NULL);
    //    led[1].toggle();
    //    transmitter.notifyFromISR();
};

extern "C" void initializeApplication() {
    button.enableInterrupt(buttonCallback, NULL);

    transmitter.create(256, Task_Priority_MID);
    receiver.create(256, Task_Priority_HIGH);
}

extern "C" void applicationTaskFunction(void const* argument) {
    vTaskDelay(1000);

    transmitter.setTxBaseAddress(baseAddress_0);
    transmitter.setTxAddressPrefix(addressPrefix);

    transmitter.setDataRate(DataRate_2MBPS);
    transmitter.setCrcConfig(CrcConfig_2Bytes);
    transmitter.setChannel(2);
    transmitter.setOutputPower(OutputPower_m18dBm);
    transmitter.setRetryCount(0xF);
    transmitter.setRetryDelay(0xF);

    receiver.setRxBaseAddress_0(baseAddress_0);
    receiver.setRxAddressPrefix(0, addressPrefix);

    receiver.setDataRate(DataRate_2MBPS);
    receiver.setCrcConfig(CrcConfig_2Bytes);
    receiver.setChannel(2);
    receiver.setOutputPower(OutputPower_m18dBm);
    receiver.setRetryCount(0xF);
    receiver.setRetryDelay(0xF);

    receiver.startListening(0, rxCallback, NULL);

    transmitter.switchOperatingMode(OperatingMode_Tx);
    receiver.switchOperatingMode(OperatingMode_Rx);

    for (;;) {
        led[0].set();
        transmitter.queueTransmission(counter.m8, sizeof(counter), txCallback, NULL);
        transmitter.notify();
        led[0].clear();

        vTaskDelay(250);
    }
}
