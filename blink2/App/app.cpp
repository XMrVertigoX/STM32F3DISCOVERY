#include "blinktask.hpp"

#include "app.h"

using namespace xXx;

extern "C" void App_createStatic(void) {
    static BlinkTask blinkTask;
}
