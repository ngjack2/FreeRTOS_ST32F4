################################################################################
# Standalone Makefile for STM32F4CPP (NUCLEO-F411RE, FreeRTOS)
#
# Mirrors the Eclipse / Ac6 System Workbench "Debug" configuration
# (.cproject + Debug/*.mk): same MCU flags, defines, include paths (and order),
# optimisation/debug level, warnings, C++ options, linker script and
# post-build steps. Paths are relative so it builds from any checkout.
#
# Output goes to build/Debug so the Eclipse generated Debug/ folder is untouched.
#
# Usage:
#   make                 - build build/Debug/STM32F4CPP.elf/.bin/.map
#   make clean           - remove build/Debug
#   make -j8             - parallel build (Eclipse: parallelBuildOn="true")
#   make TOOLCHAIN_PATH= - use arm-none-eabi-* found on PATH
#   make V=1             - show full command lines
################################################################################

PROJECT   := STM32F4CPP
BUILD_DIR ?= build/Debug

#
# Toolchain (override TOOLCHAIN_PATH on the command line or via environment)
#
TOOLCHAIN_PATH ?= C:/WesternDigital_Tools/arm-none-eabi-gcc/12.3.1/bin
ifeq ($(strip $(TOOLCHAIN_PATH)),)
PREFIX := arm-none-eabi-
else
PREFIX := $(TOOLCHAIN_PATH)/arm-none-eabi-
endif

CC      := $(PREFIX)gcc
CXX     := $(PREFIX)g++
AS      := $(PREFIX)as
OBJCOPY := $(PREFIX)objcopy
SIZE    := $(PREFIX)size

ifeq ($(V),1)
Q :=
else
Q := @
endif

#
# Sources (same set Eclipse compiles: src, startup, StdPeriph_Driver, ThirdParty)
#
C_SRCS := \
	$(wildcard src/*.c) \
	$(wildcard StdPeriph_Driver/src/*.c) \
	$(wildcard ThirdParty/FreeRTOS/org/Source/*.c) \
	$(wildcard ThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/*.c) \
	$(wildcard ThirdParty/FreeRTOS/org/Source/portable/MemMang/*.c) \
	$(wildcard ThirdParty/Segger/Config/*.c) \
	$(wildcard ThirdParty/Segger/OS/*.c) \
	$(wildcard ThirdParty/Segger/Segger/*.c)

CPP_SRCS := $(wildcard src/*.cpp)

# .s = plain assembler (arm-none-eabi-as), .S = preprocessed assembler (gcc)
ASM_SRCS   := $(wildcard startup/*.s)
ASMPP_SRCS := $(wildcard ThirdParty/Segger/Segger/*.S)

LINKER_SCRIPT := LinkerScript.ld

#
# MCU options (Mcu=STM32F411RETx, FPU=fpv4-sp-d16, Float ABI=hard)
#
MCU_FLAGS := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

#
# Defined symbols (-D), identical for C and C++
#
DEFS := \
	-DSTM32 \
	-DSTM32F4 \
	-DSTM32F411RETx \
	-DNUCLEO_F411RE \
	-DDEBUG \
	-DSTM32F411xE \
	-DUSE_STDPERIPH_DRIVER

#
# Include paths (-I), kept in the same order as the Eclipse tool settings
#
C_INCLUDES := \
	-IStdPeriph_Driver/inc \
	-IThirdParty/FreeRTOS/org/Source/include \
	-IThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F \
	-IThirdParty/Segger/Config \
	-IThirdParty/Segger/OS \
	-IThirdParty/Segger/Segger \
	-Iinc \
	-ICMSIS/device \
	-ICMSIS/core \
	-IConfig

CXX_INCLUDES := \
	-IStdPeriph_Driver/inc \
	-Iinc \
	-ICMSIS/device \
	-ICMSIS/core \
	-IConfig \
	-IThirdParty/FreeRTOS/org/Source/include \
	-IThirdParty/FreeRTOS/org/Source/portable/GCC/ARM_CM4F \
	-IThirdParty/Segger/Config \
	-IThirdParty/Segger/OS \
	-IThirdParty/Segger/Segger

ASM_INCLUDES := \
	-IStdPeriph_Driver/inc \
	-Iinc \
	-ICMSIS/device \
	-ICMSIS/core

#
# Compiler / assembler / linker flags
# (Optimization Level = -O0, Debug Level = max (-g3))
#
COMMON_FLAGS := -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections
DEP_FLAGS     = -MMD -MP -MF$(@:%.o=%.d) -MT$@

CFLAGS   := $(MCU_FLAGS) $(DEFS) $(C_INCLUDES) $(COMMON_FLAGS)
CXXFLAGS := $(MCU_FLAGS) $(DEFS) $(CXX_INCLUDES) $(COMMON_FLAGS) -fno-exceptions -fno-rtti
ASFLAGS  := $(MCU_FLAGS) $(ASM_INCLUDES) -g
LDFLAGS  := $(MCU_FLAGS) -T$(LINKER_SCRIPT) -Wl,-Map=$(BUILD_DIR)/output.map -Wl,--gc-sections -fno-exceptions -fno-rtti
LIBS     := -lm

#
# Objects: <BUILD_DIR>/<source path>.o (the source extension is kept so that
# .s/.S never collide on case-insensitive Windows file systems)
#
OBJS := \
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(C_SRCS))) \
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(CPP_SRCS))) \
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(ASM_SRCS))) \
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(ASMPP_SRCS)))

DEPS := $(OBJS:.o=.d)

ELF := $(BUILD_DIR)/$(PROJECT).elf
BIN := $(BUILD_DIR)/$(PROJECT).bin

################################################################################
# Targets
################################################################################
.PHONY: all clean size

all: $(BIN)

# Link (MCU G++ Linker)
$(ELF): $(OBJS) $(LINKER_SCRIPT)
	@echo 'Building target: $@'
	$(Q)$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'

# Post-build: generate binary and print size information
$(BIN): $(ELF)
	@echo 'Generating binary and Printing size information:'
	$(Q)$(OBJCOPY) -O binary $< $@
	$(Q)$(SIZE) $<

size: $(ELF)
	$(Q)$(SIZE) $<

# MCU GCC Compiler
$(BUILD_DIR)/%.c.o: %.c
	@echo 'CC   $<'
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(CFLAGS) -c $(DEP_FLAGS) -o $@ $<

# MCU G++ Compiler
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo 'CXX  $<'
	@mkdir -p $(dir $@)
	$(Q)$(CXX) $(CXXFLAGS) -c $(DEP_FLAGS) -o $@ $<

# MCU GCC Assembler
$(BUILD_DIR)/%.s.o: %.s
	@echo 'AS   $<'
	@mkdir -p $(dir $@)
	$(Q)$(AS) $(ASFLAGS) -o $@ $<

# Preprocessed assembler (built by the MCU GCC Compiler in Eclipse)
$(BUILD_DIR)/%.S.o: %.S
	@echo 'AS   $<'
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(CFLAGS) -c $(DEP_FLAGS) -o $@ $<

clean:
	-rm -rf $(BUILD_DIR)

-include $(DEPS)
