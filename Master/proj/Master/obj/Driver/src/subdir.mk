################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/adc.c \
../Driver/src/comm_protocol.c \
../Driver/src/led.c \
../Driver/src/motor.c \
../Driver/src/pwm.c \
../Driver/src/usart.c 

C_DEPS += \
./Driver/src/adc.d \
./Driver/src/comm_protocol.d \
./Driver/src/led.d \
./Driver/src/motor.d \
./Driver/src/pwm.d \
./Driver/src/usart.d 

OBJS += \
./Driver/src/adc.o \
./Driver/src/comm_protocol.o \
./Driver/src/led.o \
./Driver/src/motor.o \
./Driver/src/pwm.o \
./Driver/src/usart.o 



# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o: ../Driver/src/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
