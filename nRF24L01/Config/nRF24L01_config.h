#ifndef NRF24L01_CONFIG_H_
#define NRF24L01_CONFIG_H_

#include <stdint.h>

#include <stm32f3xx_hal.h>

#include <FreeRTOS.h>
#include <task.h>

#include <xXx/utils/logging.hpp>

volatile uint32_t *DWT_CYCCNT;
volatile uint32_t *DWT_CONTROL;
volatile uint32_t *SCB_DEMCR;

static inline void resetTimer() {
    DWT_CYCCNT   = (uint32_t *)0xE0001004;
    DWT_CONTROL  = (uint32_t *)0xE0001000;
    SCB_DEMCR    = (uint32_t *)0xE000EDFC;
    *SCB_DEMCR   = (*SCB_DEMCR) | 0x01000000;
    *DWT_CYCCNT  = 0;
    *DWT_CONTROL = 0;
}

static inline void startTimer() {
    *DWT_CONTROL = (*DWT_CONTROL) | 1;
}

static inline void stopTimer() {
    *DWT_CONTROL = (*DWT_CONTROL) | 0;
}

static inline uint32_t getCycles() {
    return (*DWT_CYCCNT);
}

static inline void delayMs(uint32_t ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

// TODO: Find more practical version
static inline void delayUs(uint32_t us) {
    resetTimer();
    startTimer();

    portENTER_CRITICAL();

    while (getCycles() / (HAL_RCC_GetSysClockFreq() / 1000000) < us) {
        __NOP();
    }

    portEXIT_CRITICAL();

    stopTimer();
}

#endif // NRF24L01_CONFIG_H_
