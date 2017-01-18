#ifndef RADIOTASK_HPP_
#define RADIOTASK_HPP_

#include <xXx/components/wireless/nRF24L01P/nRF24L01P.hpp>
#include <xXx/os/arduinotask.hpp>

using namespace xXx;

class RadioTask : public ArduinoTask {
  private:
    nRF24L01P &_nRF24L01_1, &_nRF24L01_2;
    Queue<uint8_t> _txQueue1, _txQueue2;
    Queue<uint8_t> _rxQueue1, _rxQueue2;

  public:
    RadioTask(nRF24L01P &nRF24L01_1, nRF24L01P &nRF24L01_2);
    ~RadioTask();

    void loop();
    void setup();
};

#endif /* RADIOTASK_HPP_ */
