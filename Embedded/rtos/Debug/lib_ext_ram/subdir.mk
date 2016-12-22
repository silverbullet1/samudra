################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_ext_ram/ext_ram.c \
../lib_ext_ram/ramfs.c 

OBJS += \
./lib_ext_ram/ext_ram.o \
./lib_ext_ram/ramfs.o 

C_DEPS += \
./lib_ext_ram/ext_ram.d \
./lib_ext_ram/ramfs.d 


# Each subdirectory must supply rules for building sources it contributes
lib_ext_ram/%.o: ../lib_ext_ram/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


