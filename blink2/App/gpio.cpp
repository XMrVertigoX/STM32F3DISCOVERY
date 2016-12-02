#include <stm32f3xx_hal.h>

#include "gpio.hpp"

static inline void limit(uint8_t &value, uint8_t max) {
    if (value > max) value = max;
}

Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin) : _port(port), _pin(pin) {}

Gpio::~Gpio() {}

void Gpio::disableInterrupt() {
    _callback[_pin] = NULL;
    _user[_pin]     = NULL;
}

uint8_t Gpio::enableInterrupt(Gpio_Callback_t callback, void *user) {
    if (_callback[_pin]) {
        return (1);
    }

    _callback[_pin] = callback;
    _user[_pin]     = user;

    return (0);
}

uint8_t Gpio::read() {
    return ((int)HAL_GPIO_ReadPin(_port, _pin));
}

void Gpio::toggle() {
    HAL_GPIO_TogglePin(_port, _pin);
}

void Gpio::write(uint8_t pinState) {
    limit(pinState, 1);
    HAL_GPIO_WritePin(_port, _pin, (GPIO_PinState)pinState);
}

/* ----- Static -------------------------------------------------------------*/

Gpio_Callback_t Gpio::_callback[16];
void *Gpio::_user[16];

void Gpio::callback(uint16_t pin) {
    if (_callback[pin]) {
        _callback[pin](_user[pin]);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    Gpio::callback(GPIO_Pin);
}
