# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = blink2

# ----- Directories and files -------------------------------------------------

# Directories
LIBS  = ../libs
CMSIS = $(LIBS)/CMSIS/CMSIS
XXX   = $(LIBS)/xXx

DEVICE   = Drivers/CMSIS/Device/ST/STM32F3xx
DRIVER   = Drivers/STM32F3xx_HAL_Driver
FREERTOS = Middlewares/Third_Party/FreeRTOS/Source

#  Files
LINKER_SCRIPT = TrueSTUDIO/blink2/STM32F303VC_FLASH.ld

# ----- Symbols ---------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLS += ARM_MATH_CM4

# ----- Sources files ---------------------------------------------------------

INCLUDE_DIRS += $(LIBS)

# xXx
SOURCE_FILES += $(wildcard $(XXX)/os/*.cpp)
SOURCE_FILES += $(wildcard $(XXX)/support/*.cpp)

# CMSIS
INCLUDE_DIRS += $(CMSIS)/Include
LIBRARY_DIRS += $(CMSIS)/Lib/GCC

# CMSIS device
INCLUDE_DIRS += $(DEVICE)/Include
SOURCE_FILES += $(shell find $(DEVICE) -regextype sed -iregex ".*/*\.[cs]")

# HAL driver
INCLUDE_DIRS += $(DRIVER)/Inc
SOURCE_FILES += $(shell find $(DRIVER) -regextype sed -iregex ".*/*\.[cs]")

# FreeRTOS
INCLUDE_DIRS += $(FREERTOS)/CMSIS_RTOS
INCLUDE_DIRS += $(FREERTOS)/include
INCLUDE_DIRS += $(FREERTOS)/portable/GCC/ARM_CM4F
SOURCE_FILES += $(shell find $(FREERTOS) -regextype sed -iregex ".*/*\.[cs]")

# STM32CubeMX auto generated code
INCLUDE_DIRS += Inc
SOURCE_FILES += $(shell find ./Src -regextype sed -iregex ".*/*\.[cs]")

# Project/Application
INCLUDE_DIRS += App
SOURCE_FILES += $(shell find ./App -regextype sed -iregex ".*/*\.cpp")

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
