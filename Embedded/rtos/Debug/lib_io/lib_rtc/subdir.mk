################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_io/lib_rtc/rtc.c 

OBJS += \
./lib_io/lib_rtc/rtc.o 

C_DEPS += \
./lib_io/lib_rtc/rtc.d 


# Each subdirectory must supply rules for building sources it contributes
lib_io/lib_rtc/%.o: ../lib_io/lib_rtc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


