################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_eefs/eefs_avrspi.c \
../lib_eefs/eefs_fileapi.c \
../lib_eefs/eefs_filesys.c 

OBJS += \
./lib_eefs/eefs_avrspi.o \
./lib_eefs/eefs_fileapi.o \
./lib_eefs/eefs_filesys.o 

C_DEPS += \
./lib_eefs/eefs_avrspi.d \
./lib_eefs/eefs_fileapi.d \
./lib_eefs/eefs_filesys.d 


# Each subdirectory must supply rules for building sources it contributes
lib_eefs/%.o: ../lib_eefs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


