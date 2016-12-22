################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include portable/subdir.mk
-include lib_xbee/subdir.mk
-include lib_wave/subdir.mk
-include lib_util/subdir.mk
-include lib_time/subdir.mk
-include lib_io/lib_rtc/subdir.mk
-include lib_io/subdir.mk
-include lib_inet/subdir.mk
-include lib_iinchip/subdir.mk
-include lib_hd44780/subdir.mk
-include lib_ft800/subdir.mk
-include lib_fatf/subdir.mk
-include lib_ext_ram/subdir.mk
-include lib_eefs/subdir.mk
-include lib-uIP/sys/subdir.mk
-include lib-uIP/lib/subdir.mk
-include lib-uIP/apps/subdir.mk
-include lib-uIP/subdir.mk
-include MemMang/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
libfreertos1.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libfreertos1.a secondary-outputs

# Tool invocations
libfreertos1.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libfreertos1.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libfreertos1.lss: libfreertos1.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libfreertos1.a  >"libfreertos1.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libfreertos1.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 libfreertos1.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) libfreertos1.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
