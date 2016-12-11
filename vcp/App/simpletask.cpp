#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include <simpletask.hpp>

using namespace xXx;

SimpleTask::SimpleTask() : ArduinoTask(128, 1) {}

SimpleTask::~SimpleTask() {}

void SimpleTask::setup() {}

void SimpleTask::loop() {
    LOG("Test");

    vTaskDelay(500 / portTICK_PERIOD_MS);
}
