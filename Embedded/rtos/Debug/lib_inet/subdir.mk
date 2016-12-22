################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_inet/dhcp.c \
../lib_inet/http.c \
../lib_inet/ntp.c \
../lib_inet/ping.c 

OBJS += \
./lib_inet/dhcp.o \
./lib_inet/http.o \
./lib_inet/ntp.o \
./lib_inet/ping.o 

C_DEPS += \
./lib_inet/dhcp.d \
./lib_inet/http.d \
./lib_inet/ntp.d \
./lib_inet/ping.d 


# Each subdirectory must supply rules for building sources it contributes
lib_inet/%.o: ../lib_inet/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


