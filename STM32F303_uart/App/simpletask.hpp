#ifndef SIMPLETASK_HPP_
#define SIMPLETASK_HPP_

#include <xXx/os/arduinotask.hpp>

using namespace xXx;

class SimpleTask : public ArduinoTask {
  public:
    SimpleTask();
    ~SimpleTask();

    void loop();
    void setup();
};

#endif /* SIMPLETASK_HPP_ */
