#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "mytask.hpp"

static const uint64_t address = 0xE7E7E7E7E7;

static uint64_t counter = 0;
static uint8_t buffer[sizeof(counter)];

using namespace xXx;

MyTask::MyTask(nRF24L01P_ESB &transmitter, nRF24L01P_ESB &receiver)
    : _transmitter(transmitter),
      _receiver(receiver),
      _rxQueue(Queue<Package_t>(256)),
      _led{Led(LD3), Led(LD5), Led(LD7), Led(LD9), Led(LD10), Led(LD8), Led(LD6), Led(LD4)} {}

MyTask::~MyTask() {}

void MyTask::setup() {
    _transmitter.configureTxPipe(address);
    _transmitter.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    _receiver.configureRxPipe(0, _rxQueue, address);
    _receiver.setDataRate(DataRate_2MBPS);
    _receiver.setCrcConfig(CrcConfig_2Bytes);
    _receiver.setChannel(2);
    _receiver.switchOperatingMode(OperatingMode_Rx);

    _transmitter.send(buffer, sizeof(buffer), NULL, NULL);
}

void MyTask::loop() {
    Package_t tmp;
    _rxQueue.dequeue(tmp);
    // BUFFER("tmp", tmp.bytes, tmp.numBytes);
    _led[tmp.bytes[0] % 8].toggle();

    counter++;
    memcpy(buffer, &counter, sizeof(counter));
    _transmitter.send(buffer, sizeof(buffer), NULL, NULL);

    vTaskDelay(10);
}
