#ifndef MYTASK_HPP_
#define MYTASK_HPP_

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_api.hpp>
#include <xXx/os/arduinotask.hpp>

using namespace xXx;

class MyTask : public ArduinoTask {
  private:
    nRF24L01P_API &_transmitter;
    nRF24L01P_API &_receiver;

    Queue<uint8_t> _rxQueue;
    Queue<uint8_t> _txQueue;

  public:
    MyTask(nRF24L01P_API &transmitter, nRF24L01P_API &receiver);
    ~MyTask();

    void loop();
    void setup();
};

#endif /* MYTASK_HPP_ */
