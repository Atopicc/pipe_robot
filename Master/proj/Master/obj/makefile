################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Driver/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
PWM_Output.hex \

SECONDARY_LIST += \
PWM_Output.lst \

SECONDARY_SIZE += \
PWM_Output.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: PWM_Output.elf secondary-outputs

# Tool invocations
PWM_Output.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "x:/project/PipeClean/����/Master/SRC/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"PWM_Output.map" --specs=nano.specs --specs=nosys.specs -o "PWM_Output.elf" $(OBJS) $(USER_OBJS) $(LIBS)
PWM_Output.hex: PWM_Output.elf
	@	riscv-none-embed-objcopy -O ihex "PWM_Output.elf" "PWM_Output.hex"
PWM_Output.lst: PWM_Output.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "PWM_Output.elf" > "PWM_Output.lst"
PWM_Output.siz: PWM_Output.elf
	riscv-none-embed-size --format=berkeley "PWM_Output.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) PWM_Output.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets