################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib-uIP/network.c \
../lib-uIP/psock.c \
../lib-uIP/slipdev.c \
../lib-uIP/uip-arp.c \
../lib-uIP/uip-ds6-route.c \
../lib-uIP/uip-ds6.c \
../lib-uIP/uip-fw.c \
../lib-uIP/uip-icmp6.c \
../lib-uIP/uip-nd6.c \
../lib-uIP/uip-neighbor.c \
../lib-uIP/uip-split.c \
../lib-uIP/uip.c \
../lib-uIP/uip6.c \
../lib-uIP/uiplib.c 

OBJS += \
./lib-uIP/network.o \
./lib-uIP/psock.o \
./lib-uIP/slipdev.o \
./lib-uIP/uip-arp.o \
./lib-uIP/uip-ds6-route.o \
./lib-uIP/uip-ds6.o \
./lib-uIP/uip-fw.o \
./lib-uIP/uip-icmp6.o \
./lib-uIP/uip-nd6.o \
./lib-uIP/uip-neighbor.o \
./lib-uIP/uip-split.o \
./lib-uIP/uip.o \
./lib-uIP/uip6.o \
./lib-uIP/uiplib.o 

C_DEPS += \
./lib-uIP/network.d \
./lib-uIP/psock.d \
./lib-uIP/slipdev.d \
./lib-uIP/uip-arp.d \
./lib-uIP/uip-ds6-route.d \
./lib-uIP/uip-ds6.d \
./lib-uIP/uip-fw.d \
./lib-uIP/uip-icmp6.d \
./lib-uIP/uip-nd6.d \
./lib-uIP/uip-neighbor.d \
./lib-uIP/uip-split.d \
./lib-uIP/uip.d \
./lib-uIP/uip6.d \
./lib-uIP/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
lib-uIP/%.o: ../lib-uIP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


