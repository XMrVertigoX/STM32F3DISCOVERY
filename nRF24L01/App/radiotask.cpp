#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

RadioTask::RadioTask(nRF24L01 &nRF24L01)
    : ArduinoTask(1024, 1), _nRF24L01(nRF24L01) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    LOG("%s", __PRETTY_FUNCTION__);

    _nRF24L01.init();
    _nRF24L01.openWritingPipe(0xe0e1e2e3e4);
}

void RadioTask::loop() {
    LOG("%s", __PRETTY_FUNCTION__);

    uint8_t buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    _nRF24L01.startWrite(buffer, sizeof(buffer));
}
