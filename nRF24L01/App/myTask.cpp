#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "myTask.hpp"

using namespace xXx;

MyTask::MyTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver)
    : ArduinoTask(256, 1), _rxQueue(Queue<uint8_t>(256)), _txQueue(Queue<uint8_t>(128)),
      _transmitter(transmitter), _receiver(receiver) {}

MyTask::~MyTask() {}

void MyTask::setup() {
    _receiver.configureRxPipe(0, _rxQueue, 0xF);
    _receiver.switchOperatingMode(OperatingMode_Rx);

    _transmitter.configureTxPipe(0xF);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    uint8_t i = 0;
    while (_txQueue.queueSpacesAvailable()) {
        _txQueue.enqueue(i);
        i++;
    }

    _transmitter.transfer(_txQueue);
}

void MyTask::loop() {
    uint8_t tmp;
    _rxQueue.dequeue(tmp);
    LOG("%x", tmp);
}
