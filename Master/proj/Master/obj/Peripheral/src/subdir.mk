################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_adc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_bkp.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_can.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_crc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dac.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dbgmcu.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dma.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dvp.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_eth.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_exti.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_flash.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_fsmc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_gpio.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_i2c.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_iwdg.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_misc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_opa.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_pwr.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rcc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rng.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rtc.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_sdio.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_spi.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_tim.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_usart.c \
x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_wwdg.c 

C_DEPS += \
./Peripheral/src/ch32v30x_adc.d \
./Peripheral/src/ch32v30x_bkp.d \
./Peripheral/src/ch32v30x_can.d \
./Peripheral/src/ch32v30x_crc.d \
./Peripheral/src/ch32v30x_dac.d \
./Peripheral/src/ch32v30x_dbgmcu.d \
./Peripheral/src/ch32v30x_dma.d \
./Peripheral/src/ch32v30x_dvp.d \
./Peripheral/src/ch32v30x_eth.d \
./Peripheral/src/ch32v30x_exti.d \
./Peripheral/src/ch32v30x_flash.d \
./Peripheral/src/ch32v30x_fsmc.d \
./Peripheral/src/ch32v30x_gpio.d \
./Peripheral/src/ch32v30x_i2c.d \
./Peripheral/src/ch32v30x_iwdg.d \
./Peripheral/src/ch32v30x_misc.d \
./Peripheral/src/ch32v30x_opa.d \
./Peripheral/src/ch32v30x_pwr.d \
./Peripheral/src/ch32v30x_rcc.d \
./Peripheral/src/ch32v30x_rng.d \
./Peripheral/src/ch32v30x_rtc.d \
./Peripheral/src/ch32v30x_sdio.d \
./Peripheral/src/ch32v30x_spi.d \
./Peripheral/src/ch32v30x_tim.d \
./Peripheral/src/ch32v30x_usart.d \
./Peripheral/src/ch32v30x_wwdg.d 

OBJS += \
./Peripheral/src/ch32v30x_adc.o \
./Peripheral/src/ch32v30x_bkp.o \
./Peripheral/src/ch32v30x_can.o \
./Peripheral/src/ch32v30x_crc.o \
./Peripheral/src/ch32v30x_dac.o \
./Peripheral/src/ch32v30x_dbgmcu.o \
./Peripheral/src/ch32v30x_dma.o \
./Peripheral/src/ch32v30x_dvp.o \
./Peripheral/src/ch32v30x_eth.o \
./Peripheral/src/ch32v30x_exti.o \
./Peripheral/src/ch32v30x_flash.o \
./Peripheral/src/ch32v30x_fsmc.o \
./Peripheral/src/ch32v30x_gpio.o \
./Peripheral/src/ch32v30x_i2c.o \
./Peripheral/src/ch32v30x_iwdg.o \
./Peripheral/src/ch32v30x_misc.o \
./Peripheral/src/ch32v30x_opa.o \
./Peripheral/src/ch32v30x_pwr.o \
./Peripheral/src/ch32v30x_rcc.o \
./Peripheral/src/ch32v30x_rng.o \
./Peripheral/src/ch32v30x_rtc.o \
./Peripheral/src/ch32v30x_sdio.o \
./Peripheral/src/ch32v30x_spi.o \
./Peripheral/src/ch32v30x_tim.o \
./Peripheral/src/ch32v30x_usart.o \
./Peripheral/src/ch32v30x_wwdg.o 



# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32v30x_adc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_adc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_bkp.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_bkp.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_can.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_can.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_crc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_crc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_dac.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dac.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_dbgmcu.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dbgmcu.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_dma.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dma.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_dvp.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_dvp.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_eth.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_eth.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_exti.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_exti.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_flash.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_flash.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_fsmc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_fsmc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_gpio.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_gpio.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_i2c.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_i2c.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_iwdg.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_iwdg.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_misc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_misc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_opa.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_opa.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_pwr.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_pwr.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_rcc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rcc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_rng.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rng.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_rtc.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_rtc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_sdio.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_sdio.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_spi.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_spi.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_tim.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_tim.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_usart.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_usart.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32v30x_wwdg.o: x:/project/PipeClean/代码/Master/SRC/Peripheral/src/ch32v30x_wwdg.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"x:/project/PipeClean/代码/Master/SRC/Debug" -I"x:/project/PipeClean/代码/Master/SRC/Core" -I"x:/project/PipeClean/代码/Master/proj/Master/User" -I"x:/project/PipeClean/代码/Master/SRC/Peripheral/inc" -I"x:/project/PipeClean/代码/Master/proj/Master/Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

