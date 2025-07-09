################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include cor/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include PS2/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include AHT/subdir.mk
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
SPI_DMA.hex \

SECONDARY_LIST += \
SPI_DMA.lst \

SECONDARY_SIZE += \
SPI_DMA.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: SPI_DMA.elf secondary-outputs

# Tool invocations
SPI_DMA.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "x:/project/PipeClean/ДњТы/Extern/SRC/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SPI_DMA.map" --specs=nano.specs --specs=nosys.specs -o "SPI_DMA.elf" $(OBJS) $(USER_OBJS) $(LIBS)
SPI_DMA.hex: SPI_DMA.elf
	@	riscv-none-embed-objcopy -O ihex "SPI_DMA.elf" "SPI_DMA.hex"
SPI_DMA.lst: SPI_DMA.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SPI_DMA.elf" > "SPI_DMA.lst"
SPI_DMA.siz: SPI_DMA.elf
	riscv-none-embed-size --format=berkeley "SPI_DMA.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) SPI_DMA.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets