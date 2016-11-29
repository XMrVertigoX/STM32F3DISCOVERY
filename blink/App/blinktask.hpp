#ifndef BLINKTASK_HPP_
#define BLINKTASK_HPP_

#include <xXx/os/arduinotask.hpp>

#include "led.hpp"

using namespace xXx;

const uint8_t numLeds = 4;

class BlinkTask : public ArduinoTask {
  public:
    BlinkTask();
    ~BlinkTask();

    void loop();
    void setup();

  private:
    Led _leds[numLeds];
};

#endif /* BLINKTASK_HPP_ */
