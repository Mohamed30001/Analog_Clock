################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/Timer2/Source/subdir.mk
-include MCAL/Timer1/Source/subdir.mk
-include MCAL/Timer0/Source/subdir.mk
-include MCAL/TWI/Source/subdir.mk
-include MCAL/GIE/Source/subdir.mk
-include MCAL/EXTI/Source/subdir.mk
-include MCAL/DIO/Source/subdir.mk
-include HAL/LCD4/Source/subdir.mk
-include HAL/IR/Source/subdir.mk
-include HAL/Clock/Source/subdir.mk
-include Application/subdir.mk
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
Analog_Clock.lss \

FLASH_IMAGE += \
Analog_Clock.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Analog_Clock.elf secondary-outputs

# Tool invocations
Analog_Clock.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Analog_Clock.map -mmcu=atmega32 -o "Analog_Clock.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Analog_Clock.lss: Analog_Clock.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Analog_Clock.elf  >"Analog_Clock.lss"
	@echo 'Finished building: $@'
	@echo ' '

Analog_Clock.hex: Analog_Clock.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Analog_Clock.elf  "Analog_Clock.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Analog_Clock.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Analog_Clock.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Analog_Clock.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
