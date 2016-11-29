#ifndef LED_HPP_
#define LED_HPP_

#include <stm32f3xx_hal.h>

enum LedPin_t {
    LD3 = GPIO_PIN_6,
    LD4 = GPIO_PIN_8,
    LD5 = GPIO_PIN_9,
    LD6 = GPIO_PIN_7
};

class Led {
  public:
    Led(LedPin_t ledPin);
    ~Led();

    void toggle();

  private:
    LedPin_t _ledPin;
};

#endif /* LED_HPP_ */
