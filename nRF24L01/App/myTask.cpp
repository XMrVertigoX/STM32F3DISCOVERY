#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "myTask.hpp"

using namespace xXx;

MyTask::MyTask(nRF24L01P_API &transmitter, nRF24L01P_API &receiver)
    : ArduinoTask(256, 1), _rxQueue(Queue<uint8_t>(256)), _txQueue(Queue<uint8_t>(128)),
      _transmitter(transmitter), _receiver(receiver) {}

MyTask::~MyTask() {}

void MyTask::setup() {
    _receiver.configureRxPipe(0, _rxQueue, 0xF);
    _receiver.setCrcConfig(Crc_t::CRC16);
    _receiver.setDataRate(DataRate_t::DataRate_1MBPS);
    _receiver.switchOperatingMode(OperatingMode_t::Rx);

    _transmitter.configureTxPipe(_txQueue, 0xF);
    _transmitter.setCrcConfig(Crc_t::CRC16);
    _transmitter.setDataRate(DataRate_t::DataRate_1MBPS);
    _transmitter.switchOperatingMode(OperatingMode_t::Tx);

    uint8_t i = 0;
    while (_txQueue.freeSlots()) {
        _txQueue.enqueue(i);
        i++;
    }
}

void MyTask::loop() {
    uint8_t tmp;
    _rxQueue.dequeue(tmp);
    LOG("%d", tmp);
}
