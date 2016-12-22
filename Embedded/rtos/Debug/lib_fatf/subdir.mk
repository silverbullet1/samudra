################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_fatf/ccsbcs.c \
../lib_fatf/diskio.c \
../lib_fatf/ff.c \
../lib_fatf/xmodem.c 

OBJS += \
./lib_fatf/ccsbcs.o \
./lib_fatf/diskio.o \
./lib_fatf/ff.o \
./lib_fatf/xmodem.o 

C_DEPS += \
./lib_fatf/ccsbcs.d \
./lib_fatf/diskio.d \
./lib_fatf/ff.d \
./lib_fatf/xmodem.d 


# Each subdirectory must supply rules for building sources it contributes
lib_fatf/%.o: ../lib_fatf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


