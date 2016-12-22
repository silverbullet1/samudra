################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_ft800/FT_API.c \
../lib_ft800/FT_CoPro_Cmds.c \
../lib_ft800/FT_Gpu_Hal.c \
../lib_ft800/FT_X11_RGB.c 

OBJS += \
./lib_ft800/FT_API.o \
./lib_ft800/FT_CoPro_Cmds.o \
./lib_ft800/FT_Gpu_Hal.o \
./lib_ft800/FT_X11_RGB.o 

C_DEPS += \
./lib_ft800/FT_API.d \
./lib_ft800/FT_CoPro_Cmds.d \
./lib_ft800/FT_Gpu_Hal.d \
./lib_ft800/FT_X11_RGB.d 


# Each subdirectory must supply rules for building sources it contributes
lib_ft800/%.o: ../lib_ft800/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


