#ifndef GPIO_HPP_
#define GPIO_HPP_

#include <stm32f3xx_hal.h>

typedef void (*Gpio_Callback_t)(void *user);

class Gpio {
  public:
    Gpio(GPIO_TypeDef *port, uint16_t pin);
    virtual ~Gpio();

    void disableInterrupt();
    int enableInterrupt(Gpio_Callback_t callback, void *user);
    void toggle();

    static void callback(uint16_t pin);

  private:
    GPIO_TypeDef *_port;
    uint16_t _pin;

    static Gpio_Callback_t _callback[];
    static void *_user[];
};

#endif /* GPIO_HPP_ */
