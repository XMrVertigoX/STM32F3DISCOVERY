#ifndef MYTASK_HPP_
#define MYTASK_HPP_

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

using namespace xXx;

class MyTask : public SimpleTask {
   private:
    nRF24L01P_ESB &_transmitter;
    nRF24L01P_ESB &_receiver;

    Queue<uint8_t> _rxQueue;
    Queue<uint8_t> _txQueue;

   public:
    MyTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver);
    ~MyTask();

    void loop();
    void setup();
};

#endif /* MYTASK_HPP_ */
