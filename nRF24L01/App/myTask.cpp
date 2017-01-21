#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "myTask.hpp"

using namespace xXx;

MyTask::MyTask(nRF24L01P_API &transmitter, nRF24L01P_API &receiver)
    : ArduinoTask(1024, 1), _rxQueue(Queue<uint8_t>(255)),
      _txQueue(Queue<uint8_t>(255)), _transmitter(transmitter),
      _receiver(receiver) {}

MyTask::~MyTask() {}

void MyTask::setup() {
    LOG("%s", __PRETTY_FUNCTION__);

    _transmitter.configureTxPipe(_txQueue);

    _receiver.configureRxPipe(0, _rxQueue);
    _receiver.switchOperatingMode(OperatingMode_t::Rx);
}

void MyTask::loop() {
    for (uint8_t i = 0; i < 255; ++i) {
        BaseType_t success = _txQueue.enqueue(i);

        if (success != pdTRUE) {
            break;
        }
    }

    _transmitter.foo();

    size_t usedSlots = _rxQueue.usedSlots();

    if (usedSlots) {
        for (int i = 0; i < usedSlots; ++i) {
            uint8_t tmp;
            _rxQueue.dequeue(tmp);
            LOG("%d", tmp);
        }
    }

    vTaskDelay(100);
}
