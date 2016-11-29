# ----- Configuration ---------------------------------------------------------

PROJECT_NAME = blink

# ----- Source code------------------------------------------------------------

SYMBOLS += STM32F303xC
SYMBOLD += __FPU_PRESENT=1
SYMBOLD += ARM_MATH_CM4

# CMSIS
INCLUDE_DIRS += Drivers/CMSIS/Include
INCLUDE_DIRS += Drivers/CMSIS/Device/ST/STM32F3xx/Include
SOURCE_FILES += Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/system_stm32f3xx.c
SOURCE_FILES += Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/gcc/startup_stm32f303xc.s

# Driver
INCLUDE_DIRS += Drivers/STM32F3xx_HAL_Driver/Inc
SOURCE_FILES += $(wildcard Drivers/STM32F3xx_HAL_Driver/Src/*.c)

# FreeRTOS
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/include
SOURCE_FILES += $(wildcard Middlewares/Third_Party/FreeRTOS/Source/*.c)

# FreeRTOS (Portable)
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c

# FreeRTOS (CMSIS RTOS)
INCLUDE_DIRS += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
SOURCE_FILES += Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c

# Libraries
INCLUDE_DIRS += ../libs
SOURCE_FILES += $(wildcard ../libs/xXx/os/*.cpp)
SOURCE_FILES += $(wildcard ../libs/xXx/support/*.cpp)

# STM32CubeMX
INCLUDE_DIRS += Inc
SOURCE_FILES += $(wildcard Src/*.c)

# Application
INCLUDE_DIRS += App
SOURCE_FILES += $(wildcard App/*.cpp)

# ----- Libraries -------------------------------------------------------------

# LIBRARY_DIRS +=

# LIBRARIES +=

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
