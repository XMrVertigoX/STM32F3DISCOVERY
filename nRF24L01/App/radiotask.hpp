#ifndef RADIOTASK_HPP_
#define RADIOTASK_HPP_

#include <xXx/components/wireless/nRF24L01/nRF24L01.hpp>
#include <xXx/os/arduinotask.hpp>

using namespace xXx;

class RadioTask : public ArduinoTask {
  private:
    nRF24L01 &_nRF24L01_1;
    nRF24L01 &_nRF24L01_2;

  public:
    RadioTask(nRF24L01 &nRF24L01_1, nRF24L01 &nRF24L01_2);
    ~RadioTask();

    void loop();
    void setup();
};

#endif /* RADIOTASK_HPP_ */
