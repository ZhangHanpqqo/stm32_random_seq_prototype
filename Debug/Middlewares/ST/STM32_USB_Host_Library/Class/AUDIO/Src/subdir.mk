################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/%.o Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/%.su Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/%.cyclo: ../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/%.c Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf" -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf/Inc" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-AUDIO-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-AUDIO-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.d ./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.o ./Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Src/usbh_audio.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-AUDIO-2f-Src

