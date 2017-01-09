#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static char buffer[]    = "Lorem ipsum dolor sit amet, con";
static uint64_t address = 0xE7E7E7E7E7;
static uint8_t channel  = 2;

RadioTask::RadioTask(nRF24L01 &nRF24L01_1, nRF24L01 &nRF24L01_2)
    : ArduinoTask(1024, 1), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01_1.init();
    _nRF24L01_2.init();

    _nRF24L01_1.setPowerState(true);
    _nRF24L01_2.setPowerState(true);

    vTaskDelay(5 / portTICK_PERIOD_MS);

    _nRF24L01_1.setTxAddress(address);
    _nRF24L01_1.setRxAddress(0, address);
    _nRF24L01_1.setCRCConfig(RF24_CRC_16);
    _nRF24L01_1.setChannel(channel);
    _nRF24L01_1.setDataRate(SPEED_1MBPS);
    _nRF24L01_1.setPowerLevel(RF24_PA_0dBm);
    _nRF24L01_1.setRetries(0xF, 0xF);

    _nRF24L01_2.setTxAddress(address);
    _nRF24L01_2.setRxAddress(0, address);
    _nRF24L01_2.setCRCConfig(RF24_CRC_16);
    _nRF24L01_2.setChannel(channel);
    _nRF24L01_2.setDataRate(SPEED_1MBPS);
    _nRF24L01_2.setPowerLevel(RF24_PA_0dBm);
    _nRF24L01_2.setRetries(0xF, 0xF);

    _nRF24L01_1.startListening();
}

void RadioTask::loop() {
    _nRF24L01_2.startWrite((uint8_t *)buffer, sizeof(buffer));

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
