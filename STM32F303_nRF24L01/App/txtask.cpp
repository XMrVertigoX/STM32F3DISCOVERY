#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "txtask.hpp"

static union {
    uint8_t p8[sizeof(uint32_t)];
    uint32_t u32;
} counter;

using namespace xXx;

TxTask::TxTask(nRF24L01P_ESB& transmitter) : _transmitter(transmitter) {
    counter.u32 = 0;
}

TxTask::~TxTask() {}

void TxTask::setup() {
    _transmitter.configureTxPipe(address);
    _transmitter.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _transmitter.switchOperatingMode(OperatingMode_Tx);

    _transmitter.send(counter.p8, sizeof(counter), [](void* user) { LOG("Initial send done"); },
                      NULL);
}

void TxTask::loop() {
    _transmitter.send(counter.p8, sizeof(counter), NULL, NULL);
    counter.u32++;

    vTaskDelay(1);
}
