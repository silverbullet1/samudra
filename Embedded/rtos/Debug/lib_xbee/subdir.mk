################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_xbee/jslong.c \
../lib_xbee/wpan_types.c \
../lib_xbee/xbee_atcmd.c \
../lib_xbee/xbee_device.c \
../lib_xbee/xbee_hexdump.c \
../lib_xbee/xbee_platform_avr.c \
../lib_xbee/xbee_serial_avr.c \
../lib_xbee/xbee_wpan.c \
../lib_xbee/xbee_xmodem.c 

OBJS += \
./lib_xbee/jslong.o \
./lib_xbee/wpan_types.o \
./lib_xbee/xbee_atcmd.o \
./lib_xbee/xbee_device.o \
./lib_xbee/xbee_hexdump.o \
./lib_xbee/xbee_platform_avr.o \
./lib_xbee/xbee_serial_avr.o \
./lib_xbee/xbee_wpan.o \
./lib_xbee/xbee_xmodem.o 

C_DEPS += \
./lib_xbee/jslong.d \
./lib_xbee/wpan_types.d \
./lib_xbee/xbee_atcmd.d \
./lib_xbee/xbee_device.d \
./lib_xbee/xbee_hexdump.d \
./lib_xbee/xbee_platform_avr.d \
./lib_xbee/xbee_serial_avr.d \
./lib_xbee/xbee_wpan.d \
./lib_xbee/xbee_xmodem.d 


# Each subdirectory must supply rules for building sources it contributes
lib_xbee/%.o: ../lib_xbee/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


