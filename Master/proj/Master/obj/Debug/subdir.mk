################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
x:/project/PipeClean/����/Master/SRC/Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 



# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: x:/project/PipeClean/����/Master/SRC/Debug/debug.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/����/Master/SRC/Debug" -I"x:/project/PipeClean/����/Master/SRC/Core" -I"x:/project/PipeClean/����/Master/proj/Master/User" -I"x:/project/PipeClean/����/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/����/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

