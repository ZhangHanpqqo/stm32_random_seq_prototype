################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LEAF/leaf/Externals/d_fft_mayer.c 

OBJS += \
./Core/LEAF/leaf/Externals/d_fft_mayer.o 

C_DEPS += \
./Core/LEAF/leaf/Externals/d_fft_mayer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LEAF/leaf/Externals/%.o Core/LEAF/leaf/Externals/%.su Core/LEAF/leaf/Externals/%.cyclo: ../Core/LEAF/leaf/Externals/%.c Core/LEAF/leaf/Externals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf" -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf/Inc" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LEAF-2f-leaf-2f-Externals

clean-Core-2f-LEAF-2f-leaf-2f-Externals:
	-$(RM) ./Core/LEAF/leaf/Externals/d_fft_mayer.cyclo ./Core/LEAF/leaf/Externals/d_fft_mayer.d ./Core/LEAF/leaf/Externals/d_fft_mayer.o ./Core/LEAF/leaf/Externals/d_fft_mayer.su

.PHONY: clean-Core-2f-LEAF-2f-leaf-2f-Externals

