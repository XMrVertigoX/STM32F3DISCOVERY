#include <stm32f3xx_hal.h>

#include <usart.h>

extern "C" int _write(int f, char *bytes, int numBytes) {
    HAL_UART_Transmit(&huart2, (uint8_t *)bytes, numBytes,
                      HAL_UART_TIMEOUT_VALUE);
    return (numBytes);
}

extern "C" int _write_r(struct _reent *r, int f, const void *bytes,
                        size_t numBytes) {
    HAL_UART_Transmit(&huart2, (uint8_t *)bytes, numBytes,
                      HAL_UART_TIMEOUT_VALUE);
    return (numBytes);
}
