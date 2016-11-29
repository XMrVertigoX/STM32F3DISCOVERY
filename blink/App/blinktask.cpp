#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>

#include "blinktask.hpp"

using namespace xXx;

static inline TickType_t ms2ticks(TickType_t ms) {
    return (ms / portTICK_PERIOD_MS);
}

BlinkTask::BlinkTask()
    : ArduinoTask(128, 1), _leds{Led(LD3), Led(LD5), Led(LD6), Led(LD4)} {}

BlinkTask::~BlinkTask() {}

void BlinkTask::setup() {}

void BlinkTask::loop() {
    for (int i = 0; i < numLeds; ++i) {
        _leds[i].toggle();
        vTaskDelay(ms2ticks(125));
        _leds[i].toggle();
    }
}
