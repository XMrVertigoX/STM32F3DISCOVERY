#ifndef NRF24L01_CONFIG_H_
#define NRF24L01_CONFIG_H_

#include <FreeRTOS.h>
#include <task.h>

static inline void delayMs(uint32_t ms) {
    // TODO: Find more accurate version
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

static inline void delayUs(uint32_t us) {
    // TODO: Find more accurate version
    vTaskDelay(us / portTICK_PERIOD_MS);
}

static inline uint32_t getMillis() {
    return (xTaskGetTickCount() * portTICK_PERIOD_MS);
}

#endif // NRF24L01_CONFIG_H_
