################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/org/Source/croutine.c \
../ThirdParty/FreeRTOS/org/Source/event_groups.c \
../ThirdParty/FreeRTOS/org/Source/list.c \
../ThirdParty/FreeRTOS/org/Source/queue.c \
../ThirdParty/FreeRTOS/org/Source/stream_buffer.c \
../ThirdParty/FreeRTOS/org/Source/tasks.c \
../ThirdParty/FreeRTOS/org/Source/timers.c 

OBJS += \
./ThirdParty/FreeRTOS/org/Source/croutine.o \
./ThirdParty/FreeRTOS/org/Source/event_groups.o \
./ThirdParty/FreeRTOS/org/Source/list.o \
./ThirdParty/FreeRTOS/org/Source/queue.o \
./ThirdParty/FreeRTOS/org/Source/stream_buffer.o \
./ThirdParty/FreeRTOS/org/Source/tasks.o \
./ThirdParty/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./ThirdParty/FreeRTOS/org/Source/croutine.d \
./ThirdParty/FreeRTOS/org/Source/event_groups.d \
./ThirdParty/FreeRTOS/org/Source/list.d \
./ThirdParty/FreeRTOS/org/Source/queue.d \
./ThirdParty/FreeRTOS/org/Source/stream_buffer.d \
./ThirdParty/FreeRTOS/org/Source/tasks.d \
./ThirdParty/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/org/Source/%.o: ../ThirdParty/FreeRTOS/org/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F411xE -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/CMSIS/core" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/ThirdParty/Segger/Config" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/ThirdParty/Segger/OS" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/ThirdParty/Segger/Segger" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/Config" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/ThirdParty/FreeRTOS/org/Source/include" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/ThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/CMSIS/device" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/inc" -I"D:/work/STM32/STM32F4FreeRTOS/FreeRTOS_ST32F4/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


