#include "blinktask.hpp"

extern "C" void App_createStatic(void) {
    static BlinkTask blinkTask;
}
