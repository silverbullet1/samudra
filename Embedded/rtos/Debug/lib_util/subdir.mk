################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../lib_util/xatoi.s 

C_SRCS += \
../lib_util/crc.c \
../lib_util/g711.c \
../lib_util/swap.c 

OBJS += \
./lib_util/crc.o \
./lib_util/g711.o \
./lib_util/swap.o \
./lib_util/xatoi.o 

S_DEPS += \
./lib_util/xatoi.d 

C_DEPS += \
./lib_util/crc.d \
./lib_util/g711.d \
./lib_util/swap.d 


# Each subdirectory must supply rules for building sources it contributes
lib_util/%.o: ../lib_util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

lib_util/%.o: ../lib_util/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


