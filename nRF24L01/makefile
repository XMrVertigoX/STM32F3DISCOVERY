# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = nRF24L01

# ----- Directories and files -------------------------------------------------

# Directories
LIBS_DIR    = ../libs

DEVICE   = Drivers/CMSIS/Device/ST/STM32F3xx
DRIVER   = Drivers/STM32F3xx_HAL_Driver
FREERTOS = Middlewares/Third_Party/FreeRTOS/Source

#  Files
LINKER_SCRIPT = TrueSTUDIO/$(PROJECT_NAME)/STM32F303VC_FLASH.ld

# ----- Symbols ---------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLS += ARM_MATH_CM4

# ----- Include directories ---------------------------------------------------

INCLUDE_DIRS += $(LIBS_DIR)

# CMSIS
INCLUDE_DIRS += $(LIBS_DIR)/CMSIS/CMSIS/Include
LIBRARY_DIRS += $(LIBS_DIR)/CMSIS/CMSIS/Lib/GCC

# CMSIS device
INCLUDE_DIRS += $(DEVICE)/Include

# HAL driver
INCLUDE_DIRS += $(DRIVER)/Inc

# Middlewares
INCLUDE_DIRS += $(FREERTOS)/CMSIS_RTOS
INCLUDE_DIRS += $(FREERTOS)/include
INCLUDE_DIRS += $(FREERTOS)/portable/GCC/ARM_CM4F


# STM32CubeMX auto generated code
INCLUDE_DIRS += Inc

# Project/Application
INCLUDE_DIRS += App

# ----- Source files ----------------------------------------------------------

# xXx library
SOURCE_FILES += $(wildcard $(LIBS_DIR)/xXx/components/wireless/RF24/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS_DIR)/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS_DIR)/xXx/support/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS_DIR)/xXx/utils/*.cpp)

# Add all supported source files in project folder
SOURCE_FILES += $(shell find . -iregex ".*\.\(c\|cpp\|s\)")

# ----- Libraries -------------------------------------------------------------

LIBRARIES += arm_cortexM4lf_math

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

include ../libs/xXx/utils/rules.mk

download: $(EXECUTABLE)
	$(TOOLCHAIN_PREFIX)gdb -q -x download.gdb $<
