#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "txtask.hpp"

uint8_t buffer[10240] = {0};

static void callback(uint8_t bytes[], size_t numBytes, void* user) {
    TxTask* self = static_cast<TxTask*>(user);
    buffer[0]++;
    self->_transmitter.send(buffer, sizeof(buffer), callback, self);
};

using namespace xXx;

TxTask::TxTask(nRF24L01P_ESB& transmitter) : _transmitter(transmitter) {}

TxTask::~TxTask() {}

void TxTask::setup() {
    _transmitter.configureTxPipe(address);
    _transmitter.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _transmitter.setOutputPower(OutputPower_m18dBm);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    _transmitter.send(buffer, sizeof(buffer), callback, this);
}

void TxTask::loop() {}
