################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib-uIP/lib/list.c \
../lib-uIP/lib/memb.c \
../lib-uIP/lib/random.c 

OBJS += \
./lib-uIP/lib/list.o \
./lib-uIP/lib/memb.o \
./lib-uIP/lib/random.o 

C_DEPS += \
./lib-uIP/lib/list.d \
./lib-uIP/lib/memb.d \
./lib-uIP/lib/random.d 


# Each subdirectory must supply rules for building sources it contributes
lib-uIP/lib/%.o: ../lib-uIP/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


