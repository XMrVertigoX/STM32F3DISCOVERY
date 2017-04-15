#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "txtask.hpp"

static uint64_t counter = 0;

using namespace xXx;

TxTask::TxTask(nRF24L01P_ESB &transmitter) : _transmitter(transmitter) {}

TxTask::~TxTask() {}

void TxTask::setup() {
    _transmitter.configureTxPipe(address);
    _transmitter.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    _transmitter.send((uint8_t *)&counter, sizeof(counter), NULL, NULL);
}

void TxTask::loop() {
    _transmitter.send((uint8_t *)&counter, sizeof(counter), NULL, NULL);
    counter++;

    vTaskDelay(1);
}
