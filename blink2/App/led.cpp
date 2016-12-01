#include <stm32f3xx_hal.h>

#include "led.hpp"

Led::Led(LedPin_t ledPin) : _ledPin((uint16_t)ledPin) {}

Led::~Led() {}

void Led::toggle() {
    HAL_GPIO_TogglePin(GPIOE, _ledPin);
}
