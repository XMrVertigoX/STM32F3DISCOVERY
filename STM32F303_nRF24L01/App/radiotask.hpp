#ifndef __TXTASK_HPP
#define __TXTASK_HPP

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

#include "led.hpp"

using namespace xXx;

class RadioTask : public SimpleTask {
   public:
    nRF24L01P_ESB &_transmitter;
    nRF24L01P_ESB &_receiver;
    Led _led[8];

    RadioTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver);
    ~RadioTask();

    void loop();
    void setup();
};

#endif /* __TXTASK_HPP */
