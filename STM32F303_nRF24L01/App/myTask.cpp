#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/utils/logging.hpp>

#include <xXx/os/simpletask.hpp>
#include "gpio.hpp"
#include "myTask.hpp"

static const uint64_t txAddress = 0xE7E7E7E7E7;
static const uint64_t rxAddress = 0xC2C2C2C2C2;

using namespace xXx;

MyTask::MyTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver)
    : _rxQueue(Queue<uint8_t>(256)),
      _txQueue(Queue<uint8_t>(256)),
      _transmitter(transmitter),
      _receiver(receiver),
      _led{Led(LD3), Led(LD5), Led(LD7), Led(LD9), Led(LD10), Led(LD8), Led(LD6), Led(LD4)} {}

MyTask::~MyTask() {}

void MyTask::setup() {
    _receiver.configureRxPipe(0, _rxQueue, txAddress);
    _receiver.setDataRate(DataRate_2MBPS);
    _receiver.setCrcConfig(CrcConfig_2Bytes);
    _receiver.setChannel(2);
    _receiver.switchOperatingMode(OperatingMode_Rx);

    _transmitter.configureTxPipe(txAddress);
    _transmitter.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    uint8_t i = 0;
    while (_txQueue.queueSpacesAvailable()) {
        _txQueue.enqueue(i);
        i++;
    }

    _transmitter.send(_txQueue);
}

void MyTask::loop() {
    uint8_t tmp;
    _rxQueue.dequeue(tmp);
    _led[tmp % 8].toggle();

    LOG("%d", tmp);
}
