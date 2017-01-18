#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static uint8_t buffer[32];
static uint64_t address1 = 0x0F;
static uint64_t address2 = 0xF0;

RadioTask::RadioTask(nRF24L01P &nRF24L01_1, nRF24L01P &nRF24L01_2)
    : ArduinoTask(1024, 1), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2),
      _txQueue1{Queue<uint8_t>(256)}, _txQueue2{Queue<uint8_t>(256)},
      _rxQueue1{Queue<uint8_t>(256)}, _rxQueue2{Queue<uint8_t>(256)} {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01_1.init();
    _nRF24L01_1.powerUp();

    _nRF24L01_2.init();
    _nRF24L01_2.powerUp();

    vTaskDelay(5 / portTICK_PERIOD_MS);

    _nRF24L01_1.configureTxPipe(_txQueue1, address1);
    _nRF24L01_1.configureRxPipe(1, _rxQueue1, address2);

    _nRF24L01_2.configureTxPipe(_txQueue2, address2);
    _nRF24L01_2.configureRxPipe(1, _rxQueue2, address1);

    _nRF24L01_1.enterTxMode();

    _nRF24L01_2.enterRxMode();
}

void RadioTask::loop() {
    LOG("StackHighWaterMark: %d", uxTaskGetStackHighWaterMark(_handle));

    uint8_t length = snprintf(reinterpret_cast<char *>(buffer), sizeof(buffer),
                              "%ld", xTaskGetTickCount());

    for (int i = 0; i < length + 1; ++i) {
        UBaseType_t success = _txQueue1.enqueue(buffer[i]);

        if (!success) {
            break;
        }
    }

    UBaseType_t usedSlots = _rxQueue2.usedSlots();

    if (usedSlots) {
        uint8_t buffer[usedSlots];

        for (int i = 0; i < usedSlots; ++i) {
            _rxQueue2.dequeue(buffer[i]);
        }

        LOG("%s", buffer);
    }

    _nRF24L01_1.update();
    _nRF24L01_2.update();

    vTaskDelay(100 / portTICK_PERIOD_MS);
}
