################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_io/digitalAnalog.c \
../lib_io/i2cMultiMaster.c \
../lib_io/serial.c \
../lib_io/servoPWM.c \
../lib_io/spi.c 

OBJS += \
./lib_io/digitalAnalog.o \
./lib_io/i2cMultiMaster.o \
./lib_io/serial.o \
./lib_io/servoPWM.o \
./lib_io/spi.o 

C_DEPS += \
./lib_io/digitalAnalog.d \
./lib_io/i2cMultiMaster.d \
./lib_io/serial.d \
./lib_io/servoPWM.d \
./lib_io/spi.d 


# Each subdirectory must supply rules for building sources it contributes
lib_io/%.o: ../lib_io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


