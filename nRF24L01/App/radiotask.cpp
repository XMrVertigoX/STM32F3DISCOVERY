#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "radiotask.hpp"

using namespace xXx;

RadioTask::RadioTask() : ArduinoTask(1024, 1) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {}

void RadioTask::loop() {}
