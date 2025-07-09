################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
x:/project/PipeClean/ДњТы/Master/SRC/Startup/startup_ch32v30x_D8.S 

S_UPPER_DEPS += \
./Startup/startup_ch32v30x_D8.d 

OBJS += \
./Startup/startup_ch32v30x_D8.o 



# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v30x_D8.o: x:/project/PipeClean/ДњТы/Master/SRC/Startup/startup_ch32v30x_D8.S
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -x assembler-with-cpp -I"x:/project/PipeClean/ДњТы/Master/SRC/Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

