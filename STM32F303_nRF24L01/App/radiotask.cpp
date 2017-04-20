#include "radiotask.hpp"

#include <assert.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/simpletask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"

static const uint64_t address = 0xE7E7E7E7E7;

uint8_t buffer[10240] = {0};

static void txCallback(uint8_t bytes[], size_t numBytes, void* user) {
    RadioTask* self = static_cast<RadioTask*>(user);
    buffer[0]++;
    self->_transmitter.send(buffer, sizeof(buffer), txCallback, self);
};

static void rxCallback(uint8_t bytes[], size_t numBytes, void* user) {
    RadioTask* self = static_cast<RadioTask*>(user);
    self->_led[bytes[0] % 8].toggle();
};

using namespace xXx;

RadioTask::RadioTask(nRF24L01P_ESB& transmitter, nRF24L01P_ESB& receiver)
    : _transmitter(transmitter), _receiver(receiver), _led{Led(LD3), Led(LD5),  Led(LD7),
                                                           Led(LD9), Led(LD10), Led(LD8),
                                                           Led(LD6), Led(LD4)} {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    _transmitter.setup();
    _receiver.setup();

    _transmitter.configureTxPipe(address);
    _receiver.configureRxPipe(0, address);
    _transmitter.setDataRate(DataRate_2MBPS);
    _receiver.setDataRate(DataRate_2MBPS);
    _transmitter.setCrcConfig(CrcConfig_2Bytes);
    _receiver.setCrcConfig(CrcConfig_2Bytes);
    _transmitter.setChannel(2);
    _receiver.setChannel(2);
    _transmitter.setOutputPower(OutputPower_m18dBm);
    _receiver.setOutputPower(OutputPower_m18dBm);
    _transmitter.switchOperatingMode(OperatingMode_Tx);
    _receiver.switchOperatingMode(OperatingMode_Rx);

    _receiver.startListening(0, rxCallback, this);

    _transmitter.send(buffer, sizeof(buffer), txCallback, this);
}

void RadioTask::loop() {
    _transmitter.loop();
    _receiver.loop();
}
