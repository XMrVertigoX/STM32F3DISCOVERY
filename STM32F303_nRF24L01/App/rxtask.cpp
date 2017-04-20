#include "rxtask.hpp"

#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"

#define LAMBDA []

using namespace xXx;

static void callback(uint8_t bytes[], size_t numBytes, void *user) {
    RxTask *self = static_cast<RxTask *>(user);
    self->_led[bytes[0] % 8].toggle();
};

RxTask::RxTask(nRF24L01P_ESB &receiver)
    : _receiver(receiver), _led{Led(LD3),  Led(LD5), Led(LD7), Led(LD9),
                                Led(LD10), Led(LD8), Led(LD6), Led(LD4)} {}

RxTask::~RxTask() {}

void RxTask::setup() {
    _receiver.setup();

    _receiver.configureRxPipe(0, address);
    _receiver.setDataRate(DataRate_2MBPS);
    _receiver.setCrcConfig(CrcConfig_2Bytes);
    _receiver.setChannel(2);
    _receiver.setOutputPower(OutputPower_m18dBm);
    _receiver.switchOperatingMode(OperatingMode_Rx);

    _receiver.startListening(0, callback, this);
}

void RxTask::loop() {
    _receiver.loop();
}
