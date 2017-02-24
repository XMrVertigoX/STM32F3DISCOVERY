# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = nRF24L01

# ----- Directories and files -------------------------------------------------

# Directories
LIBS = ../libs

#  Files
LINKER_SCRIPT = TrueSTUDIO/$(PROJECT_NAME)/STM32F303VC_FLASH.ld

# ----- Symbols ---------------------------------------------------------------

# SYMBOLS += NDEBUG
SYMBOLS += STM32F303xC

# ----- Include directories ---------------------------------------------------

# CMSIS
INCLUDE_DIRS += Drivers/CMSIS/Include
INCLUDE_DIRS += Drivers/CMSIS/Device/ST/STM32F3xx/Include

# HAL driver
INCLUDE_DIRS += Drivers/STM32F3xx_HAL_Driver/Inc

# Middlewares
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/include
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F

# STM32CubeMX auto generated code
INCLUDE_DIRS += Inc

# Libs root
INCLUDE_DIRS += $(LIBS)

# SEGGER RTT
INCLUDE_DIRS += $(LIBS)/SEGGER_RTT_V612d/RTT

# Project/Application
INCLUDE_DIRS += Config

# ----- Source files ----------------------------------------------------------

# SEGGER RTT
SOURCE_FILES += $(LIBS)/SEGGER_RTT_V612d/RTT/SEGGER_RTT.c

# xXx
SOURCE_FILES += $(wildcard $(LIBS)/xXx/components/wireless/nrf24l01p/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/support/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/utils/*.cpp)

# Add all supported source files in project folder
SOURCE_FILES += $(shell find -iregex ".*\.\(c\|cpp\|s\)")

# ----- Libraries -------------------------------------------------------------

# LIBRARIES +=

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
