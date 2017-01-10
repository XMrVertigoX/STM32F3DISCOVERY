#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "gpio.hpp"
#include "radiotask.hpp"

using namespace xXx;

static char buffer[] = "Lorem ipsum dolor sit amet, con";

RadioTask::RadioTask(nRF24L01P &nRF24L01_1, nRF24L01P &nRF24L01_2)
    : ArduinoTask(1024, 1), _nRF24L01_1(nRF24L01_1), _nRF24L01_2(nRF24L01_2) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    _nRF24L01_1.init();
    _nRF24L01_2.init();

    _nRF24L01_1.powerUp();
    _nRF24L01_2.powerUp();

    vTaskDelay(5 / portTICK_PERIOD_MS);

    _nRF24L01_1.configureTxPipe();
    _nRF24L01_2.configureRxPipe(0);

    _nRF24L01_2.startListening();
}

void RadioTask::loop() {
    _nRF24L01_1.startWrite((uint8_t *)buffer, sizeof(buffer));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
