#include "rxtask.hpp"

#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"

static Package_t package;

using namespace xXx;

RxTask::RxTask(nRF24L01P_ESB &receiver)
    : _receiver(receiver), _rxQueue(Queue<Package_t>(10)), _led{Led(LD3), Led(LD5),  Led(LD7),
                                                                Led(LD9), Led(LD10), Led(LD8),
                                                                Led(LD6), Led(LD4)} {}

RxTask::~RxTask() {}

void RxTask::setup() {
    _receiver.configureRxPipe(0, _rxQueue, address);
    _receiver.setDataRate(DataRate_2MBPS);
    _receiver.setCrcConfig(CrcConfig_2Bytes);
    _receiver.setChannel(2);
    _receiver.switchOperatingMode(OperatingMode_Rx);
}

void RxTask::loop() {
    _rxQueue.dequeue(package);

    for (uint8_t i = 0; i < package.numBytes; ++i) {
        if (package.bytes[i] > 0) {
            _led[i].set();
        }
    }
}