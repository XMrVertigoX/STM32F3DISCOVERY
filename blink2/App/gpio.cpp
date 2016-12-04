#include <stm32f3xx_hal.h>

#include <xXx/interfaces/igpio.hpp>

#include "gpio.hpp"

Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin) : _port(port), _pin(pin) {}

Gpio::~Gpio() {}

bool Gpio::read() {
    return ((bool)HAL_GPIO_ReadPin(_port, _pin));
}

void Gpio::toggle() {
    HAL_GPIO_TogglePin(_port, _pin);
}

void Gpio::write(bool state) {
    HAL_GPIO_WritePin(_port, _pin, (GPIO_PinState)state);
}

void Gpio::disableInterrupt() {
    _callback[_pin] = NULL;
    _user[_pin]     = NULL;
}

void Gpio::enableInterrupt(IGpio_Callback_t callback, void *user) {
    if (_callback[_pin]) {
        return;
    }

    _callback[_pin] = callback;
    _user[_pin]     = user;
}

IGpio_Callback_t Gpio::_callback[16];
void *Gpio::_user[16];

void Gpio::callback(uint16_t pin) {
    if (_callback[pin]) {
        _callback[pin](_user[pin]);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    Gpio::callback(GPIO_Pin);
}
