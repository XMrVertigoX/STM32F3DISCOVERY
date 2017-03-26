#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>

#include "blinktask.hpp"

using namespace xXx;

static inline TickType_t ms2ticks(TickType_t ms) {
    return (ms / portTICK_PERIOD_MS);
}

BlinkTask::BlinkTask()
    : ArduinoTask(128, 1), _led{Led(LD3),  Led(LD5), Led(LD7), Led(LD9),
                                 Led(LD10), Led(LD8), Led(LD6), Led(LD4)} {}

BlinkTask::~BlinkTask() {}

void BlinkTask::setup() {}

void BlinkTask::loop() {
    for (int i = 0; i < numLeds; ++i) {
        _led[i].toggle();
        vTaskDelay(ms2ticks(125));
        _led[i].toggle();
    }
}
