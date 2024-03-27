################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MIDI_application.c \
../Core/Src/adc.c \
../Core/Src/audiostream.c \
../Core/Src/bsp_driver_sd.c \
../Core/Src/codec.c \
../Core/Src/debug.c \
../Core/Src/dma.c \
../Core/Src/fatfs.c \
../Core/Src/fatfs_platform.c \
../Core/Src/fmc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/rng.c \
../Core/Src/sai.c \
../Core/Src/sd_diskio.c \
../Core/Src/sdmmc.c \
../Core/Src/spi.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c \
../Core/Src/ui.c \
../Core/Src/usart.c \
../Core/Src/usb_host.c \
../Core/Src/usbh_MIDI.c \
../Core/Src/usbh_conf.c \
../Core/Src/usbh_platform.c 

OBJS += \
./Core/Src/MIDI_application.o \
./Core/Src/adc.o \
./Core/Src/audiostream.o \
./Core/Src/bsp_driver_sd.o \
./Core/Src/codec.o \
./Core/Src/debug.o \
./Core/Src/dma.o \
./Core/Src/fatfs.o \
./Core/Src/fatfs_platform.o \
./Core/Src/fmc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/rng.o \
./Core/Src/sai.o \
./Core/Src/sd_diskio.o \
./Core/Src/sdmmc.o \
./Core/Src/spi.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/ui.o \
./Core/Src/usart.o \
./Core/Src/usb_host.o \
./Core/Src/usbh_MIDI.o \
./Core/Src/usbh_conf.o \
./Core/Src/usbh_platform.o 

C_DEPS += \
./Core/Src/MIDI_application.d \
./Core/Src/adc.d \
./Core/Src/audiostream.d \
./Core/Src/bsp_driver_sd.d \
./Core/Src/codec.d \
./Core/Src/debug.d \
./Core/Src/dma.d \
./Core/Src/fatfs.d \
./Core/Src/fatfs_platform.d \
./Core/Src/fmc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/rng.d \
./Core/Src/sai.d \
./Core/Src/sd_diskio.d \
./Core/Src/sdmmc.d \
./Core/Src/spi.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d \
./Core/Src/ui.d \
./Core/Src/usart.d \
./Core/Src/usb_host.d \
./Core/Src/usbh_MIDI.d \
./Core/Src/usbh_conf.d \
./Core/Src/usbh_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf" -I"/Users/hanzhang/STM32CubeIDE/workspace_1.14.0/genera_brain_templt_re/Core/LEAF/leaf/Inc" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/MIDI_application.cyclo ./Core/Src/MIDI_application.d ./Core/Src/MIDI_application.o ./Core/Src/MIDI_application.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/audiostream.cyclo ./Core/Src/audiostream.d ./Core/Src/audiostream.o ./Core/Src/audiostream.su ./Core/Src/bsp_driver_sd.cyclo ./Core/Src/bsp_driver_sd.d ./Core/Src/bsp_driver_sd.o ./Core/Src/bsp_driver_sd.su ./Core/Src/codec.cyclo ./Core/Src/codec.d ./Core/Src/codec.o ./Core/Src/codec.su ./Core/Src/debug.cyclo ./Core/Src/debug.d ./Core/Src/debug.o ./Core/Src/debug.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fatfs.cyclo ./Core/Src/fatfs.d ./Core/Src/fatfs.o ./Core/Src/fatfs.su ./Core/Src/fatfs_platform.cyclo ./Core/Src/fatfs_platform.d ./Core/Src/fatfs_platform.o ./Core/Src/fatfs_platform.su ./Core/Src/fmc.cyclo ./Core/Src/fmc.d ./Core/Src/fmc.o ./Core/Src/fmc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rng.cyclo ./Core/Src/rng.d ./Core/Src/rng.o ./Core/Src/rng.su ./Core/Src/sai.cyclo ./Core/Src/sai.d ./Core/Src/sai.o ./Core/Src/sai.su ./Core/Src/sd_diskio.cyclo ./Core/Src/sd_diskio.d ./Core/Src/sd_diskio.o ./Core/Src/sd_diskio.su ./Core/Src/sdmmc.cyclo ./Core/Src/sdmmc.d ./Core/Src/sdmmc.o ./Core/Src/sdmmc.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/ui.cyclo ./Core/Src/ui.d ./Core/Src/ui.o ./Core/Src/ui.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/usb_host.cyclo ./Core/Src/usb_host.d ./Core/Src/usb_host.o ./Core/Src/usb_host.su ./Core/Src/usbh_MIDI.cyclo ./Core/Src/usbh_MIDI.d ./Core/Src/usbh_MIDI.o ./Core/Src/usbh_MIDI.su ./Core/Src/usbh_conf.cyclo ./Core/Src/usbh_conf.d ./Core/Src/usbh_conf.o ./Core/Src/usbh_conf.su ./Core/Src/usbh_platform.cyclo ./Core/Src/usbh_platform.d ./Core/Src/usbh_platform.o ./Core/Src/usbh_platform.su

.PHONY: clean-Core-2f-Src

