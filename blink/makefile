# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = blink

# ----- Directories and files -------------------------------------------------

# Directories
LIBS  = ../libs
CMSIS = $(LIBS)/CMSIS/CMSIS
XXX   = $(LIBS)/xXx

DEVICE   = Drivers/CMSIS/Device/ST/STM32F3xx
DRIVER   = Drivers/STM32F3xx_HAL_Driver
FREERTOS = Middlewares/Third_Party/FreeRTOS/Source

#  Files
LINKER_SCRIPT = TrueSTUDIO/blink/STM32F303VC_FLASH.ld

# ----- Symbols ---------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLS += ARM_MATH_CM4

# ----- Submodules ------------------------------------------------------------

INCLUDE_DIRS += $(LIBS)

# CMSIS
INCLUDE_DIRS += $(CMSIS)/Include
LIBRARY_DIRS += $(CMSIS)/Lib/GCC

# xXx
SOURCE_FILES += $(wildcard $(XXX)/os/*.cpp)
SOURCE_FILES += $(wildcard $(XXX)/support/*.cpp)

# ----- Project ---------------------------------------------------------------

# STM32CubeMX auto generated code
INCLUDE_DIRS += Inc
SOURCE_FILES += $(wildcard Src/*.c)

# CMSIS device
INCLUDE_DIRS += $(DEVICE)/Include
SOURCE_FILES += $(DEVICE)/Source/Templates/gcc/startup_stm32f303xc.s

# HAL driver
INCLUDE_DIRS += $(DRIVER)/Inc
SOURCE_FILES += $(wildcard $(DRIVER)/Src/*.c)

# FreeRTOS
INCLUDE_DIRS += $(FREERTOS)/include
SOURCE_FILES += $(wildcard $(FREERTOS)/*.c)

# FreeRTOS (portable)
INCLUDE_DIRS += $(FREERTOS)/portable/GCC/ARM_CM4F
SOURCE_FILES += $(FREERTOS)/portable/GCC/ARM_CM4F/port.c
SOURCE_FILES += $(FREERTOS)/portable/MemMang/heap_4.c

# FreeRTOS (CMSOS RTOS)
INCLUDE_DIRS += $(FREERTOS)/CMSIS_RTOS
SOURCE_FILES += $(FREERTOS)/CMSIS_RTOS/cmsis_os.c

# Application
INCLUDE_DIRS += App
SOURCE_FILES += $(wildcard App/*.cpp)

# ----- Libraries -------------------------------------------------------------

LIBRARIES += arm_cortexM4lf_math

# ----- Flags -----------------------------------------------------------------

GCCFLAGS += -mcpu=cortex-m4
GCCFLAGS += -mthumb
GCCFLAGS += -mfloat-abi=hard
GCCFLAGS += -mfpu=fpv4-sp-d16

COMMON_CFLAGS += -g
COMMON_CFLAGS += -Og

CFLAGS += -std=gnu11

CXXFLAGS += -std=gnu++14

ASMFLAGS +=

CPPFLAGS +=

LDFLAGS += -T $(LINKER_SCRIPT)

# ----- Rules -----------------------------------------------------------------

TOOLCHAIN_PREFIX = arm-none-eabi-

include ../libs/xXx/utils/rules.mk

download: $(EXECUTABLE)
	arm-none-eabi-gdb -q -x download.gdb $<
