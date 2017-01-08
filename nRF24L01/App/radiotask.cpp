#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static char buffer[] = "Lorem ipsum dolor sit amet, con";

RadioTask::RadioTask(nRF24L01 &nRF24L01)
    : ArduinoTask(1024, 1), _nRF24L01(nRF24L01) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    LOG("%s", __PRETTY_FUNCTION__);

    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01.init();
    _nRF24L01.openWritingPipe(0);
}

void RadioTask::loop() {
    _nRF24L01.startWrite((uint8_t *)buffer, sizeof(buffer));

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
