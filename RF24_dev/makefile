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

INCLUDE_DIRS += $(LIBS)
INCLUDE_DIRS += $(LIBS)/SEGGER_RTT/RTT

INCLUDE_DIRS += Drivers/CMSIS/Device/ST/STM32F3xx/Include
INCLUDE_DIRS += Drivers/CMSIS/Include
INCLUDE_DIRS += Drivers/STM32F3xx_HAL_Driver/Inc
INCLUDE_DIRS += Inc
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/include
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F

INCLUDE_DIRS += ./Config

SOURCE_FILES += $(LIBS)/SEGGER_RTT/RTT/SEGGER_RTT.c
SOURCE_FILES += $(wildcard $(LIBS)/xXx/components/wireless/rf24/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/support/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/utils/*.cpp)

SOURCE_FILES += $(shell find . -iregex ".*\.\(c\|cpp\|s\)")

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
