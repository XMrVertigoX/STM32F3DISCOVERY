#include <assert.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static uint64_t address1 = 0x0F;
static uint64_t address2 = 0xF0;
static uint8_t counter   = 0;
static uint8_t lastItem  = 0;

RadioTask::RadioTask(nRF24L01P_API &nRF24L01_1, nRF24L01P_API &nRF24L01_2)
    : ArduinoTask(1024, 2), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2),
      _txQueue1{Queue<uint8_t>(256)}, _txQueue2{Queue<uint8_t>(256)},
      _rxQueue1{Queue<uint8_t>(256)}, _rxQueue2{Queue<uint8_t>(256)} {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    LOG("%s", __PRETTY_FUNCTION__);

    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01_1.init();
    _nRF24L01_1.switchOperatingMode(OperatingMode_t::Standby);

    _nRF24L01_2.init();
    _nRF24L01_2.switchOperatingMode(OperatingMode_t::Standby);

    vTaskDelay(5 / portTICK_PERIOD_MS);

    _nRF24L01_1.configureTxPipe(_txQueue1, address1);
    _nRF24L01_1.configureRxPipe(1, _rxQueue1, address2);
    _nRF24L01_1.switchOperatingMode(OperatingMode_t::Tx);

    _nRF24L01_2.configureTxPipe(_txQueue2, address2);
    _nRF24L01_2.configureRxPipe(1, _rxQueue2, address1);
    _nRF24L01_2.switchOperatingMode(OperatingMode_t::Rx);

    for (int i = 0; i < _txQueue1.size(); ++i) {
        _txQueue1.enqueue(counter);
        counter++;
    }
}

void RadioTask::loop() {
    _nRF24L01_1.update();
    _nRF24L01_2.update();

    UBaseType_t numBytes = _rxQueue2.usedSlots();

    if (numBytes) {
        uint8_t tmp;
        _rxQueue2.dequeue(tmp);
        LOG("%d", tmp);
        assert(lastItem == tmp);
        lastItem++;
    }
}
