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

static const RF24_Address_t address = {.components = {0xE1, 0xE2E3E4E5}};

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

RF24_ESB transmitter(port1_SPI, port1_CE, port1_INT);
RF24_ESB receiver(port2_SPI, port2_CE, port2_INT);

Led led[] = {Led(LD3), Led(LD5), Led(LD7), Led(LD9), Led(LD10), Led(LD8), Led(LD6), Led(LD4)};

static void txCallback(int8_t numRetries, void* user) {
    LOG("txCallback");
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
    Queue<RF24_Package_t> rxQueue(3);
    RF24_Status_t status = RF24_Status_Success;

    status = transmitter.setTxAddress(address);
    LOG("setTxAddress: %d", status);
    status = transmitter.setDataRate(RF24_DataRate::High_2MBPS);
    LOG("setDataRate: %d", status);
    status = transmitter.setCrcConfig(RF24_CRCConfig::CRC_16);
    LOG("setCrcConfig: %d", status);
    status = transmitter.setChannel(2);
    LOG("setChannel: %d", status);
    status = transmitter.setOutputPower(RF24_OutputPower::Power_m18dBm);
    LOG("setOutputPower: %d", status);
    status = transmitter.setRetryCount(0xF);
    LOG("setRetryCount: %d", status);
    status = transmitter.setRetryDelay(0xF);
    LOG("setRetryDelay: %d", status);

    status = receiver.setRxAddress(0, address);
    LOG("setRxAddress: %d", status);
    status = receiver.setDataRate(RF24_DataRate::High_2MBPS);
    LOG("setDataRate: %d", status);
    status = receiver.setCrcConfig(RF24_CRCConfig::CRC_16);
    LOG("setCrcConfig: %d", status);
    status = receiver.setChannel(2);
    LOG("setChannel: %d", status);
    status = receiver.setOutputPower(RF24_OutputPower::Power_m18dBm);
    LOG("setOutputPower: %d", status);

    transmitter.enterTxMode();
    receiver.enterRxMode();

    vTaskDelay(1000);

    for (;;) {
        led[0].set();
        transmitter.queuePackage(counter.m8, sizeof(counter), txCallback, NULL);
        transmitter.notify();

        RF24_Package_t package;
        rxQueue.dequeue(package);
        BUFFER("package", package.bytes, package.numBytes);
        led[0].clear();
    }
}
