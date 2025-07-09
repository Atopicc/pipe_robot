################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AHT/AHT20.c \
../AHT/AHTD.c \
../AHT/MYI2C.c 

C_DEPS += \
./AHT/AHT20.d \
./AHT/AHTD.d \
./AHT/MYI2C.d 

OBJS += \
./AHT/AHT20.o \
./AHT/AHTD.o \
./AHT/MYI2C.o 



# Each subdirectory must supply rules for building sources it contributes
AHT/%.o: ../AHT/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Extern/SRC/Debug" -I"x:/project/PipeClean/代码/Extern/SRC/Core" -I"x:/project/PipeClean/代码/Extern/proj/extern/User" -I"x:/project/PipeClean/代码/Extern/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Extern/proj/extern/PS2" -I"x:/project/PipeClean/代码/Extern/proj/extern/AHT" -I"x:/project/PipeClean/代码/Extern/proj/extern/cor" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
