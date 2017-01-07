#include <FreeRTOS.h>
#include <task.h>

#include <xXx/os/arduinotask.hpp>
#include <xXx/utils/logging.hpp>

#include "radiotask.hpp"

using namespace xXx;

RadioTask::RadioTask(nRF24L01 &nRF24L01)
    : ArduinoTask(1024, 1), _nRF24L01(nRF24L01) {}

RadioTask::~RadioTask() {}

void RadioTask::setup() {}

void RadioTask::loop() {}
