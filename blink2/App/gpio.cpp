#include <stm32f3xx_hal.h>

#include "gpio.hpp"

Gpio_InterruptCallback_t Gpio::_callback[16];
void *Gpio::_user[16];

Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin) : _port(port), _pin(pin) {}

Gpio::~Gpio() {}

Gpio_Status_t Gpio::disableInterrupt() {
    _callback[_pin] = NULL;
    _user[_pin]     = NULL;

    return Gpio_SUCCESS;
}

Gpio_Status_t Gpio::enableInterrupt(Gpio_InterruptCallback_t callback,
                                    void *user) {
    if (_callback[_pin]) {
        return Gpio_FAILURE;
    }

    _callback[_pin] = callback;
    _user[_pin]     = user;

    return Gpio_SUCCESS;
}

Gpio_Status_t Gpio::toggle() {
    HAL_GPIO_TogglePin(_port, _pin);

    return Gpio_SUCCESS;
}

void Gpio::callback(uint16_t pin) {
    if (_callback[pin]) {
        _callback[pin](_user[pin]);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    Gpio::callback(GPIO_Pin);
}
