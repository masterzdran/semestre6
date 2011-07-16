################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include test/subdir.mk
-include lcd-test/subdir.mk
-include ecos/led/subdir.mk
-include ecos/lcd/subdir.mk
-include ecos/hello/subdir.mk
-include Tacografo/subdir.mk
-include Tacografo/Percurso/subdir.mk
-include Tacografo/Menu/subdir.mk
-include Tacografo/Clock/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Blinky.hex \

SECONDARY_LIST += \
Blinky.lst \

SECONDARY_SIZE += \
Blinky.siz \


# All Target
all: Blinky.elf secondary-outputs

# Tool invocations
Blinky.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linux GCC C Linker'
	arm-elf-gcc -nostartfiles -Wl,-Map,Blinky.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"Blinky.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Blinky.hex: Blinky.elf
	@echo 'Invoking: ARM Linux GNU Create Flash Image'
	arm-elf-objcopy -O ihex Blinky.elf "Blinky.hex"
	@echo 'Finished building: $@'
	@echo ' '

Blinky.lst: Blinky.elf
	@echo 'Invoking: ARM Linux GNU Create Listing'
	arm-elf-objdump -h -S Blinky.elf >"Blinky.lst"
	@echo 'Finished building: $@'
	@echo ' '

Blinky.siz: Blinky.elf
	@echo 'Invoking: ARM Linux GNU Print Size'
	arm-elf-size  --format=berkeley Blinky.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Blinky.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
