################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_time/asc_store.c \
../lib_time/asctime.c \
../lib_time/asctime_r.c \
../lib_time/ctime.c \
../lib_time/ctime_r.c \
../lib_time/daylight_seconds.c \
../lib_time/difftime.c \
../lib_time/dst_pointer.c \
../lib_time/equation_of_time.c \
../lib_time/fatfs_time.c \
../lib_time/geo_location.c \
../lib_time/gm_sidereal.c \
../lib_time/gmtime.c \
../lib_time/gmtime_r.c \
../lib_time/isLeap.c \
../lib_time/iso_week_date.c \
../lib_time/iso_week_date_r.c \
../lib_time/isotime.c \
../lib_time/isotime_r.c \
../lib_time/lm_sidereal.c \
../lib_time/localtime.c \
../lib_time/localtime_r.c \
../lib_time/mk_gmtime.c \
../lib_time/mktime.c \
../lib_time/month_length.c \
../lib_time/moon_phase.c \
../lib_time/print_lz.c \
../lib_time/set_dst.c \
../lib_time/set_position.c \
../lib_time/set_system_time.c \
../lib_time/set_zone.c \
../lib_time/solar_declination.c \
../lib_time/solar_noon.c \
../lib_time/strftime.c \
../lib_time/sun_rise.c \
../lib_time/sun_set.c \
../lib_time/system_time.c \
../lib_time/time.c \
../lib_time/tm_store.c \
../lib_time/utc_offset.c \
../lib_time/week_of_month.c \
../lib_time/week_of_year.c 

S_UPPER_SRCS += \
../lib_time/system_tick.S 

OBJS += \
./lib_time/asc_store.o \
./lib_time/asctime.o \
./lib_time/asctime_r.o \
./lib_time/ctime.o \
./lib_time/ctime_r.o \
./lib_time/daylight_seconds.o \
./lib_time/difftime.o \
./lib_time/dst_pointer.o \
./lib_time/equation_of_time.o \
./lib_time/fatfs_time.o \
./lib_time/geo_location.o \
./lib_time/gm_sidereal.o \
./lib_time/gmtime.o \
./lib_time/gmtime_r.o \
./lib_time/isLeap.o \
./lib_time/iso_week_date.o \
./lib_time/iso_week_date_r.o \
./lib_time/isotime.o \
./lib_time/isotime_r.o \
./lib_time/lm_sidereal.o \
./lib_time/localtime.o \
./lib_time/localtime_r.o \
./lib_time/mk_gmtime.o \
./lib_time/mktime.o \
./lib_time/month_length.o \
./lib_time/moon_phase.o \
./lib_time/print_lz.o \
./lib_time/set_dst.o \
./lib_time/set_position.o \
./lib_time/set_system_time.o \
./lib_time/set_zone.o \
./lib_time/solar_declination.o \
./lib_time/solar_noon.o \
./lib_time/strftime.o \
./lib_time/sun_rise.o \
./lib_time/sun_set.o \
./lib_time/system_tick.o \
./lib_time/system_time.o \
./lib_time/time.o \
./lib_time/tm_store.o \
./lib_time/utc_offset.o \
./lib_time/week_of_month.o \
./lib_time/week_of_year.o 

S_UPPER_DEPS += \
./lib_time/system_tick.d 

C_DEPS += \
./lib_time/asc_store.d \
./lib_time/asctime.d \
./lib_time/asctime_r.d \
./lib_time/ctime.d \
./lib_time/ctime_r.d \
./lib_time/daylight_seconds.d \
./lib_time/difftime.d \
./lib_time/dst_pointer.d \
./lib_time/equation_of_time.d \
./lib_time/fatfs_time.d \
./lib_time/geo_location.d \
./lib_time/gm_sidereal.d \
./lib_time/gmtime.d \
./lib_time/gmtime_r.d \
./lib_time/isLeap.d \
./lib_time/iso_week_date.d \
./lib_time/iso_week_date_r.d \
./lib_time/isotime.d \
./lib_time/isotime_r.d \
./lib_time/lm_sidereal.d \
./lib_time/localtime.d \
./lib_time/localtime_r.d \
./lib_time/mk_gmtime.d \
./lib_time/mktime.d \
./lib_time/month_length.d \
./lib_time/moon_phase.d \
./lib_time/print_lz.d \
./lib_time/set_dst.d \
./lib_time/set_position.d \
./lib_time/set_system_time.d \
./lib_time/set_zone.d \
./lib_time/solar_declination.d \
./lib_time/solar_noon.d \
./lib_time/strftime.d \
./lib_time/sun_rise.d \
./lib_time/sun_set.d \
./lib_time/system_time.d \
./lib_time/time.d \
./lib_time/tm_store.d \
./lib_time/utc_offset.d \
./lib_time/week_of_month.d \
./lib_time/week_of_year.d 


# Each subdirectory must supply rules for building sources it contributes
lib_time/%.o: ../lib_time/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

lib_time/%.o: ../lib_time/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


