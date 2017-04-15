#ifndef __RXTASK_HPP
#define __RXTASK_HPP

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

#include "app.h"
#include "led.hpp"

using namespace xXx;

class RxTask : public SimpleTask {
   private:
    nRF24L01P_ESB &_receiver;
    Queue<Package_t> _rxQueue;
    Led _led[8];

   public:
    RxTask(nRF24L01P_ESB &receiver);
    ~RxTask();

    void loop();
    void setup();
};

#endif /* __RXTASK_HPP */
