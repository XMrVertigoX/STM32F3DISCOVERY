# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = nRF24L01

# ----- Directories and files -------------------------------------------------

# Directories
LIBS = ../libs

#  Files
LINKER_SCRIPT = TrueSTUDIO/STM32F303_nRF24L01/STM32F303VC_FLASH.ld

# ----- Symbols ---------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLS += ARM_MATH_CM4
# SYMBOLS += NDEBUG

# ----- Source files ----------------------------------------------------------

# CMSIS
INCLUDE_DIRS += Drivers/CMSIS/Include
INCLUDE_DIRS += Drivers/CMSIS/Device/ST/STM32F3xx/Include
SOURCE_FILES += TrueSTUDIO/startup_stm32f303xc.s

# HAL driver
INCLUDE_DIRS += Drivers/STM32F3xx_HAL_Driver/Inc
SOURCE_FILES += $(wildcard Drivers/STM32F3xx_HAL_Driver/Src/*.c)

# Middlewares
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/include
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
SOURCE_FILES += $(wildcard Middlewares/Third_Party/FreeRTOS/Source/*.c)
SOURCE_FILES += $(wildcard Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/*.c)
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c

# STM32CubeMX auto generated code
INCLUDE_DIRS += Inc
SOURCE_FILES += $(wildcard Src/*.c)
SOURCE_FILES += $(wildcard Src/*.cpp)

# Libs root
INCLUDE_DIRS += $(LIBS)

# SEGGER RTT
INCLUDE_DIRS += $(LIBS)/SEGGER_RTT_V612d/RTT

# Project/Application
INCLUDE_DIRS += Config

# SEGGER RTT
SOURCE_FILES += $(LIBS)/SEGGER_RTT_V612d/RTT/SEGGER_RTT.c

# xXx
SOURCE_FILES += $(wildcard $(LIBS)/xXx/components/wireless/nrf24l01p/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/support/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/utils/*.cpp)


SOURCE_FILES += $(wildcard App/*.cpp)

# ----- Libraries -------------------------------------------------------------

LIBRARIES +=

# ----- Flags -----------------------------------------------------------------

GCCFLAGS += -mcpu=cortex-m4
GCCFLAGS += -mthumb
GCCFLAGS += -mfloat-abi=hard
GCCFLAGS += -mfpu=fpv4-sp-d16

CPPFLAGS +=

COMMON_CFLAGS += -g
COMMON_CFLAGS += -Og

CFLAGS += -std=gnu11

CXXFLAGS += -std=gnu++14

LDFLAGS += -T $(realpath $(LINKER_SCRIPT))

# ----- Rules -----------------------------------------------------------------

TOOLCHAIN_PREFIX = arm-none-eabi-

include $(LIBS)/xXx/utils/rules.mk

download: $(EXECUTABLE)
	$(TOOLCHAIN_PREFIX)gdb -q -x download.gdb $<
