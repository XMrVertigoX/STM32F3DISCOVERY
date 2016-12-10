#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>

#include "blinktask.hpp"

using namespace xXx;

static inline TickType_t ms2ticks(TickType_t ms) {
    return (ms / portTICK_PERIOD_MS);
}

static inline void buttonInterruptCallback(void *user) {
    static_cast<BlinkTask *>(user)->reverse();
}

BlinkTask::BlinkTask()
    : ArduinoTask(128, 1), _led{Led(LD3),  Led(LD5), Led(LD7), Led(LD9),
                                Led(LD10), Led(LD8), Led(LD6), Led(LD4)},
      _button(Gpio(GPIOA, GPIO_PIN_0)), _reverse(false) {}

BlinkTask::~BlinkTask() {}

void BlinkTask::reverse() {
    _reverse = !_reverse;
}

void BlinkTask::setup() {
    _button.enableInterrupt(buttonInterruptCallback, this);
}

void BlinkTask::loop() {
    for (int i = 0; i < numLeds; ++i) {
        int led;

        if (_reverse) {
            led = (numLeds - 1) - i;
        } else {
            led = i;
        }

        _led[led].toggle();
        vTaskDelay(ms2ticks(125));
        _led[led].toggle();
    }
}
