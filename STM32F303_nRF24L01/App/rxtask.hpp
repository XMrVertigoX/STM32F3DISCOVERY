#ifndef __RXTASK_HPP
#define __RXTASK_HPP

#include <xXx/components/wireless/nrf24l01p/nrf24l01p_esb.hpp>
#include <xXx/os/simpletask.hpp>

#include "app.h"
#include "led.hpp"

using namespace xXx;

struct Package_t {
    uint8_t bytes[rxFifoSize];
    uint8_t numBytes;
};

class RxTask : public SimpleTask {
   public:
    nRF24L01P_ESB &_receiver;
    Led _led[8];

    RxTask(nRF24L01P_ESB &receiver);
    ~RxTask();

    void loop();
    void setup();
};

#endif /* __RXTASK_HPP */
