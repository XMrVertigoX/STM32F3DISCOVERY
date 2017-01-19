#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static uint64_t address1 = 0x0F;
static uint64_t address2 = 0xF0;

static union {
    uint32_t counter_32 = 0;
    uint8_t counter_8[4];
} counter_out;

RadioTask::RadioTask(nRF24L01P_ShockBurst &nRF24L01_1,
                     nRF24L01P_ShockBurst &nRF24L01_2)
    : ArduinoTask(1024, 1), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2),
      _txQueue1{Queue<uint8_t>(256)}, _txQueue2{Queue<uint8_t>(256)},
      _rxQueue1{Queue<uint8_t>(256)}, _rxQueue2{Queue<uint8_t>(256)} {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
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
}

void RadioTask::loop() {
    for (int i = 0; i < sizeof(counter_out) + 1; ++i) {
        UBaseType_t success = _txQueue1.enqueue(counter_out.counter_8[i]);

        if (!success) {
            break;
        }
    }

    UBaseType_t usedSlots = _rxQueue2.usedSlots();

    uint8_t counter_in[4];

    if (usedSlots) {
        for (int i = 0; i < usedSlots; ++i) {
            _rxQueue2.dequeue(counter_in[i]);
        }

        BUFFER("counter_in", counter_in, 4);
    }

    counter_out.counter_32++;

    _nRF24L01_1.update();
    _nRF24L01_2.update();

    vTaskDelay(100 / portTICK_PERIOD_MS);
}
