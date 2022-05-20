################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AnalogIn.c \
../Core/Src/AnalogOut.c \
../Core/Src/RCFilter.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/serial.c \
../Core/Src/shell.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l0xx.c \
../Core/Src/timebase.c 

OBJS += \
./Core/Src/AnalogIn.o \
./Core/Src/AnalogOut.o \
./Core/Src/RCFilter.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/serial.o \
./Core/Src/shell.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l0xx.o \
./Core/Src/timebase.o 

C_DEPS += \
./Core/Src/AnalogIn.d \
./Core/Src/AnalogOut.d \
./Core/Src/RCFilter.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/serial.d \
./Core/Src/shell.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l0xx.d \
./Core/Src/timebase.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32L021xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DMSI_VALUE=2097000 -DHSI_VALUE=16000000 -DLSI_VALUE=37000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AnalogIn.d ./Core/Src/AnalogIn.o ./Core/Src/AnalogOut.d ./Core/Src/AnalogOut.o ./Core/Src/RCFilter.d ./Core/Src/RCFilter.o ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/serial.d ./Core/Src/serial.o ./Core/Src/shell.d ./Core/Src/shell.o ./Core/Src/stm32l0xx_it.d ./Core/Src/stm32l0xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32l0xx.d ./Core/Src/system_stm32l0xx.o ./Core/Src/timebase.d ./Core/Src/timebase.o

.PHONY: clean-Core-2f-Src

