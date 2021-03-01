################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AppCommands.c \
../src/ErrorsDB.c \
../src/HostTask.c \
../src/Interrupt_Handlers.c \
../src/UartAPI.c \
../src/asic.c \
../src/haL_uart.c \
../src/hal_clock.c \
../src/hal_flash.c \
../src/hal_gpio.c \
../src/hal_interrupt.c \
../src/hal_timer.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

CPP_SRCS += \
../src/CMeasureDistance.cpp \
../src/CMotorControl.cpp 

OBJS += \
./src/AppCommands.o \
./src/CMeasureDistance.o \
./src/CMotorControl.o \
./src/ErrorsDB.o \
./src/HostTask.o \
./src/Interrupt_Handlers.o \
./src/UartAPI.o \
./src/asic.o \
./src/haL_uart.o \
./src/hal_clock.o \
./src/hal_flash.o \
./src/hal_gpio.o \
./src/hal_interrupt.o \
./src/hal_timer.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/AppCommands.d \
./src/ErrorsDB.d \
./src/HostTask.d \
./src/Interrupt_Handlers.d \
./src/UartAPI.d \
./src/asic.d \
./src/haL_uart.d \
./src/hal_clock.d \
./src/hal_flash.d \
./src/hal_gpio.d \
./src/hal_interrupt.d \
./src/hal_timer.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 

CPP_DEPS += \
./src/CMeasureDistance.d \
./src/CMotorControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -DSTM32F411xE -DUSE_STDPERIPH_DRIVER -I"D:/work/STM32/STM32F4CPP/StdPeriph_Driver/inc" -I"D:/work/STM32/STM32F4CPP/ThirdParty/FreeRTOS/org/Source/include" -I"D:/work/STM32/STM32F4CPP/ThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/Config" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/OS" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/Segger" -I"D:/work/STM32/STM32F4CPP/inc" -I"D:/work/STM32/STM32F4CPP/CMSIS/device" -I"D:/work/STM32/STM32F4CPP/CMSIS/core" -I"D:/work/STM32/STM32F4CPP/Config" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -DSTM32F411xE -DUSE_STDPERIPH_DRIVER -I"D:/work/STM32/STM32F4CPP/StdPeriph_Driver/inc" -I"D:/work/STM32/STM32F4CPP/inc" -I"D:/work/STM32/STM32F4CPP/CMSIS/device" -I"D:/work/STM32/STM32F4CPP/CMSIS/core" -I"D:/work/STM32/STM32F4CPP/Config" -I"D:/work/STM32/STM32F4CPP/ThirdParty/FreeRTOS/org/Source/include" -I"D:/work/STM32/STM32F4CPP/ThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/Config" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/OS" -I"D:/work/STM32/STM32F4CPP/ThirdParty/Segger/Segger" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


