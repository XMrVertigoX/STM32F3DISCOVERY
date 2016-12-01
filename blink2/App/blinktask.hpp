#ifndef BLINKTASK_HPP_
#define BLINKTASK_HPP_

#include <xXx/os/arduinotask.hpp>

#include "led.hpp"

using namespace xXx;

const uint8_t numLeds = 8;

class BlinkTask : public ArduinoTask {
  public:
    BlinkTask();
    ~BlinkTask();

    void reverse();

    void loop();
    void setup();

  private:
    Led _leds[numLeds];
    bool _reverse = false;
};

#endif /* BLINKTASK_HPP_ */
