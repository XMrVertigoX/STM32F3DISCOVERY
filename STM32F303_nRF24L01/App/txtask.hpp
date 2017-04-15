#ifndef __TXTASK_HPP
#define __TXTASK_HPP

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

#include "app.h"
#include "led.hpp"

using namespace xXx;

class TxTask : public SimpleTask {
   private:
    nRF24L01P_ESB &_transmitter;

   public:
    TxTask(nRF24L01P_ESB &transmitter);
    ~TxTask();

    void loop();
    void setup();
};

#endif /* __TXTASK_HPP */
