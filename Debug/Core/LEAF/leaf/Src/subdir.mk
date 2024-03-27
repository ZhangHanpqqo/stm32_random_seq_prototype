################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LEAF/leaf/Src/leaf-analysis.c \
../Core/LEAF/leaf/Src/leaf-delay.c \
../Core/LEAF/leaf/Src/leaf-distortion.c \
../Core/LEAF/leaf/Src/leaf-dynamics.c \
../Core/LEAF/leaf/Src/leaf-effects.c \
../Core/LEAF/leaf/Src/leaf-electrical.c \
../Core/LEAF/leaf/Src/leaf-envelopes.c \
../Core/LEAF/leaf/Src/leaf-filters.c \
../Core/LEAF/leaf/Src/leaf-instruments.c \
../Core/LEAF/leaf/Src/leaf-math.c \
../Core/LEAF/leaf/Src/leaf-mempool.c \
../Core/LEAF/leaf/Src/leaf-midi.c \
../Core/LEAF/leaf/Src/leaf-oscillators.c \
../Core/LEAF/leaf/Src/leaf-physical.c \
../Core/LEAF/leaf/Src/leaf-reverb.c \
../Core/LEAF/leaf/Src/leaf-sampling.c \
../Core/LEAF/leaf/Src/leaf-tables.c \
../Core/LEAF/leaf/Src/leaf-vocal.c \
../Core/LEAF/leaf/Src/leaf.c 

OBJS += \
./Core/LEAF/leaf/Src/leaf-analysis.o \
./Core/LEAF/leaf/Src/leaf-delay.o \
./Core/LEAF/leaf/Src/leaf-distortion.o \
./Core/LEAF/leaf/Src/leaf-dynamics.o \
./Core/LEAF/leaf/Src/leaf-effects.o \
./Core/LEAF/leaf/Src/leaf-electrical.o \
./Core/LEAF/leaf/Src/leaf-envelopes.o \
./Core/LEAF/leaf/Src/leaf-filters.o \
./Core/LEAF/leaf/Src/leaf-instruments.o \
./Core/LEAF/leaf/Src/leaf-math.o \
./Core/LEAF/leaf/Src/leaf-mempool.o \
./Core/LEAF/leaf/Src/leaf-midi.o \
./Core/LEAF/leaf/Src/leaf-oscillators.o \
./Core/LEAF/leaf/Src/leaf-physical.o \
./Core/LEAF/leaf/Src/leaf-reverb.o \
./Core/LEAF/leaf/Src/leaf-sampling.o \
./Core/LEAF/leaf/Src/leaf-tables.o \
./Core/LEAF/leaf/Src/leaf-vocal.o \
./Core/LEAF/leaf/Src/leaf.o 

C_DEPS += \
./Core/LEAF/leaf/Src/leaf-analysis.d \
./Core/LEAF/leaf/Src/leaf-delay.d \
./Core/LEAF/leaf/Src/leaf-distortion.d \
./Core/LEAF/leaf/Src/leaf-dynamics.d \
./Core/LEAF/leaf/Src/leaf-effects.d \
./Core/LEAF/leaf/Src/leaf-electrical.d \
./Core/LEAF/leaf/Src/leaf-envelopes.d \
./Core/LEAF/leaf/Src/leaf-filters.d \
./Core/LEAF/leaf/Src/leaf-instruments.d \
./Core/LEAF/leaf/Src/leaf-math.d \
./Core/LEAF/leaf/Src/leaf-mempool.d \
./Core/LEAF/leaf/Src/leaf-midi.d \
./Core/LEAF/leaf/Src/leaf-oscillators.d \
./Core/LEAF/leaf/Src/leaf-physical.d \
./Core/LEAF/leaf/Src/leaf-reverb.d \
./Core/LEAF/leaf/Src/leaf-sampling.d \
./Core/LEAF/leaf/Src/leaf-tables.d \
./Core/LEAF/leaf/Src/leaf-vocal.d \
./Core/LEAF/leaf/Src/leaf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LEAF/leaf/Src/%.o Core/LEAF/leaf/Src/%.su Core/LEAF/leaf/Src/%.cyclo: ../Core/LEAF/leaf/Src/%.c Core/LEAF/leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf" -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf/Inc" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LEAF-2f-leaf-2f-Src

clean-Core-2f-LEAF-2f-leaf-2f-Src:
	-$(RM) ./Core/LEAF/leaf/Src/leaf-analysis.cyclo ./Core/LEAF/leaf/Src/leaf-analysis.d ./Core/LEAF/leaf/Src/leaf-analysis.o ./Core/LEAF/leaf/Src/leaf-analysis.su ./Core/LEAF/leaf/Src/leaf-delay.cyclo ./Core/LEAF/leaf/Src/leaf-delay.d ./Core/LEAF/leaf/Src/leaf-delay.o ./Core/LEAF/leaf/Src/leaf-delay.su ./Core/LEAF/leaf/Src/leaf-distortion.cyclo ./Core/LEAF/leaf/Src/leaf-distortion.d ./Core/LEAF/leaf/Src/leaf-distortion.o ./Core/LEAF/leaf/Src/leaf-distortion.su ./Core/LEAF/leaf/Src/leaf-dynamics.cyclo ./Core/LEAF/leaf/Src/leaf-dynamics.d ./Core/LEAF/leaf/Src/leaf-dynamics.o ./Core/LEAF/leaf/Src/leaf-dynamics.su ./Core/LEAF/leaf/Src/leaf-effects.cyclo ./Core/LEAF/leaf/Src/leaf-effects.d ./Core/LEAF/leaf/Src/leaf-effects.o ./Core/LEAF/leaf/Src/leaf-effects.su ./Core/LEAF/leaf/Src/leaf-electrical.cyclo ./Core/LEAF/leaf/Src/leaf-electrical.d ./Core/LEAF/leaf/Src/leaf-electrical.o ./Core/LEAF/leaf/Src/leaf-electrical.su ./Core/LEAF/leaf/Src/leaf-envelopes.cyclo ./Core/LEAF/leaf/Src/leaf-envelopes.d ./Core/LEAF/leaf/Src/leaf-envelopes.o ./Core/LEAF/leaf/Src/leaf-envelopes.su ./Core/LEAF/leaf/Src/leaf-filters.cyclo ./Core/LEAF/leaf/Src/leaf-filters.d ./Core/LEAF/leaf/Src/leaf-filters.o ./Core/LEAF/leaf/Src/leaf-filters.su ./Core/LEAF/leaf/Src/leaf-instruments.cyclo ./Core/LEAF/leaf/Src/leaf-instruments.d ./Core/LEAF/leaf/Src/leaf-instruments.o ./Core/LEAF/leaf/Src/leaf-instruments.su ./Core/LEAF/leaf/Src/leaf-math.cyclo ./Core/LEAF/leaf/Src/leaf-math.d ./Core/LEAF/leaf/Src/leaf-math.o ./Core/LEAF/leaf/Src/leaf-math.su ./Core/LEAF/leaf/Src/leaf-mempool.cyclo ./Core/LEAF/leaf/Src/leaf-mempool.d ./Core/LEAF/leaf/Src/leaf-mempool.o ./Core/LEAF/leaf/Src/leaf-mempool.su ./Core/LEAF/leaf/Src/leaf-midi.cyclo ./Core/LEAF/leaf/Src/leaf-midi.d ./Core/LEAF/leaf/Src/leaf-midi.o ./Core/LEAF/leaf/Src/leaf-midi.su ./Core/LEAF/leaf/Src/leaf-oscillators.cyclo ./Core/LEAF/leaf/Src/leaf-oscillators.d ./Core/LEAF/leaf/Src/leaf-oscillators.o ./Core/LEAF/leaf/Src/leaf-oscillators.su ./Core/LEAF/leaf/Src/leaf-physical.cyclo ./Core/LEAF/leaf/Src/leaf-physical.d ./Core/LEAF/leaf/Src/leaf-physical.o ./Core/LEAF/leaf/Src/leaf-physical.su ./Core/LEAF/leaf/Src/leaf-reverb.cyclo ./Core/LEAF/leaf/Src/leaf-reverb.d ./Core/LEAF/leaf/Src/leaf-reverb.o ./Core/LEAF/leaf/Src/leaf-reverb.su ./Core/LEAF/leaf/Src/leaf-sampling.cyclo ./Core/LEAF/leaf/Src/leaf-sampling.d ./Core/LEAF/leaf/Src/leaf-sampling.o ./Core/LEAF/leaf/Src/leaf-sampling.su ./Core/LEAF/leaf/Src/leaf-tables.cyclo ./Core/LEAF/leaf/Src/leaf-tables.d ./Core/LEAF/leaf/Src/leaf-tables.o ./Core/LEAF/leaf/Src/leaf-tables.su ./Core/LEAF/leaf/Src/leaf-vocal.cyclo ./Core/LEAF/leaf/Src/leaf-vocal.d ./Core/LEAF/leaf/Src/leaf-vocal.o ./Core/LEAF/leaf/Src/leaf-vocal.su ./Core/LEAF/leaf/Src/leaf.cyclo ./Core/LEAF/leaf/Src/leaf.d ./Core/LEAF/leaf/Src/leaf.o ./Core/LEAF/leaf/Src/leaf.su

.PHONY: clean-Core-2f-LEAF-2f-leaf-2f-Src

