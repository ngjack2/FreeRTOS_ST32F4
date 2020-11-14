################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F411xE -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -I"D:/work/STM32/STM32HelloWord/CMSIS/core" -I"D:/work/STM32/STM32HelloWord/ThirdParty/Segger/Config" -I"D:/work/STM32/STM32HelloWord/ThirdParty/Segger/OS" -I"D:/work/STM32/STM32HelloWord/ThirdParty/Segger/Segger" -I"D:/work/STM32/STM32HelloWord/Config" -I"D:/work/STM32/STM32HelloWord/ThirdParty/FreeRTOS/org/Source/include" -I"D:/work/STM32/STM32HelloWord/ThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/work/STM32/STM32HelloWord/CMSIS/device" -I"D:/work/STM32/STM32HelloWord/inc" -I"D:/work/STM32/STM32HelloWord/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

