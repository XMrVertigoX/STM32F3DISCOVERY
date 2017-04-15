#ifndef MYTASK_HPP_
#define MYTASK_HPP_

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

#include "led.hpp"

using namespace xXx;

class MyTask : public SimpleTask {
   private:
    nRF24L01P_ESB &_transmitter;
    nRF24L01P_ESB &_receiver;
    Queue<Package_t> _rxQueue;
    Led _led[8];

   public:
    MyTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver);
    ~MyTask();

    void loop();
    void setup();
};

#endif /* MYTASK_HPP_ */
