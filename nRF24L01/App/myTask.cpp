#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "myTask.hpp"

using namespace xXx;

MyTask::MyTask(nRF24L01P_API &transmitter, nRF24L01P_API &receiver)
    : ArduinoTask(256, 1), _rxQueue(Queue<uint8_t>(256)),
      _txQueue(Queue<uint8_t>(256)), _transmitter(transmitter),
      _receiver(receiver) {}

MyTask::~MyTask() {}

void MyTask::setup() {
    _transmitter.configureTxPipe(_txQueue, 0xF);

    _receiver.configureRxPipe(0, _rxQueue, 0xF);
    _receiver.switchOperatingMode(OperatingMode_t::Rx);
}

void MyTask::loop() {
    for (uint8_t i = 0; i < 255; ++i) {
        BaseType_t success = _txQueue.enqueue(i);

        if (success != pdTRUE) {
            break;
        }
    }

    if (_txQueue.usedSlots()) {
        _transmitter.notify();
    }

    size_t usedSlots = _rxQueue.usedSlots();

    if (usedSlots) {
        for (int i = 0; i < usedSlots; ++i) {
            uint8_t tmp;
            _rxQueue.dequeue(tmp);
            LOG("%d", tmp);
        }
    }

    vTaskDelay(1000);
}
