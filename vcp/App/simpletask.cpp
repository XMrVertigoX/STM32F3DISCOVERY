#include <FreeRTOS.h>
#include <task.h>

#include <usbd_cdc_if.h>

#include <xXx/os/arduinotask.hpp>

#include <simpletask.hpp>

using namespace xXx;

SimpleTask::SimpleTask() : ArduinoTask(128, 1) {}

SimpleTask::~SimpleTask() {}

void SimpleTask::setup() {}

void SimpleTask::loop() {
    uint8_t message[] = {'H', 'e', 'l', 'l', 'o', '\n'};

    CDC_Transmit_FS(message, sizeof(message));

    vTaskDelay(500 / portTICK_PERIOD_MS);
}
