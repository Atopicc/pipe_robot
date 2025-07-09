################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
x:/project/PipeClean/代码/Extern/SRC/Core/core_riscv.c 

C_DEPS += \
./Core/core_riscv.d 

OBJS += \
./Core/core_riscv.o 



# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: x:/project/PipeClean/代码/Extern/SRC/Core/core_riscv.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Extern/SRC/Debug" -I"x:/project/PipeClean/代码/Extern/SRC/Core" -I"x:/project/PipeClean/代码/Extern/proj/extern/User" -I"x:/project/PipeClean/代码/Extern/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Extern/proj/extern/PS2" -I"x:/project/PipeClean/代码/Extern/proj/extern/AHT" -I"x:/project/PipeClean/代码/Extern/proj/extern/cor" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

