#ifndef GPIO_HPP_
#define GPIO_HPP_

#include <stm32f3xx_hal.h>

typedef void (*Gpio_InterruptCallback_t)(void *user);

enum Gpio_Status_t { Gpio_SUCCESS, Gpio_FAILURE };

class Gpio {
  public:
    Gpio(GPIO_TypeDef *port, uint16_t pin);
    virtual ~Gpio();

    Gpio_Status_t disableInterrupt();
    Gpio_Status_t enableInterrupt(Gpio_InterruptCallback_t callback,
                                  void *user);
    Gpio_Status_t toggle();

    static void callback(uint16_t pin);

  private:
    GPIO_TypeDef *_port;
    uint16_t _pin;

    static Gpio_InterruptCallback_t _callback[];
    static void *_user[];
};

#endif /* GPIO_HPP_ */
