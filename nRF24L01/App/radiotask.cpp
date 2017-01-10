#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static char buffer[] = "Lorem ipsum dolor sit amet, con";

RadioTask::RadioTask(nRF24L01 &nRF24L01_1, nRF24L01 &nRF24L01_2)
    : ArduinoTask(1024, 1), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01_1.init();
    _nRF24L01_2.init();

    _nRF24L01_1.setPowerState(true);
    _nRF24L01_2.setPowerState(true);

    _nRF24L01_2.enterRxMode();
    _nRF24L01_1.startWrite((uint8_t *)buffer, sizeof(buffer));
}

void RadioTask::loop() {
    _nRF24L01_1.startWrite((uint8_t *)buffer, sizeof(buffer));
    vTaskDelay(1000);
}
