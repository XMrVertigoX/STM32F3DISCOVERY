# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = blink

# ----- Symbols ---------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLS += ARM_MATH_CM4

# ----- Submodules ------------------------------------------------------------

LIBS = ../libs

INCLUDE_DIRS += $(LIBS)

# CMSIS
INCLUDE_DIRS += $(LIBS)/CMSIS/CMSIS/Include
LIBRARY_DIRS += $(LIBS)/CMSIS/CMSIS/Lib/GCC

# xXx
SOURCE_FILES += $(wildcard $(LIBS)/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard $(LIBS)/xXx/support/*.cpp)

# ----- Project ---------------------------------------------------------------

# STM32CubeMX
INCLUDE_DIRS += Inc
SOURCE_FILES += $(wildcard Src/*.c)

# STM32CubeMX (Device)
INCLUDE_DIRS += Drivers/CMSIS/Device/ST/STM32F3xx/Include
SOURCE_FILES += Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/system_stm32f3xx.c
SOURCE_FILES += Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/gcc/startup_stm32f303xc.s

# STM32CubeMX (Driver)
INCLUDE_DIRS += Drivers/STM32F3xx_HAL_Driver/Inc
SOURCE_FILES += $(wildcard Drivers/STM32F3xx_HAL_Driver/Src/*.c)

# STM32CubeMX (FreeRTOS)
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/include
SOURCE_FILES += $(wildcard Middlewares/Third_Party/FreeRTOS/Source/*.c)

INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c

INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c

# Application
INCLUDE_DIRS += App
SOURCE_FILES += $(wildcard App/*.cpp)

# ----- Libraries -------------------------------------------------------------

LIBRARIES += arm_cortexM4lf_math

# ----- Flags -----------------------------------------------------------------

GCCFLAGS += -march=armv7e-m
GCCFLAGS += -mtune=cortex-m4
GCCFLAGS += -mthumb
GCCFLAGS += -mfloat-abi=hard
GCCFLAGS += -mfpu=fpv4-sp-d16

COMMON_CFLAGS += -g
COMMON_CFLAGS += -Og

CFLAGS += -std=gnu11

CXXFLAGS += -std=gnu++14

# CPPFLAGS +=

LDFLAGS += -T STM32F303VC_FLASH.ld

# ----- Rules -----------------------------------------------------------------

TOOLCHAIN_PREFIX = arm-none-eabi-

include ../libs/xXx/utils/rules.mk

download: $(EXECUTABLE)
	arm-none-eabi-gdb -q -x download.gdb $<
