################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
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
HelloWorld.hex \

SECONDARY_LIST += \
HelloWorld.lst \

SECONDARY_SIZE += \
HelloWorld.siz \


# All Target
all: HelloWorld.elf secondary-outputs

# Tool invocations
HelloWorld.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linux GCC C Linker'
	arm-elf-gcc -nostartfiles -Wl,-Map,HelloWorld.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"HelloWorld.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HelloWorld.hex: HelloWorld.elf
	@echo 'Invoking: ARM Linux GNU Create Flash Image'
	arm-elf-objcopy -O ihex HelloWorld.elf "HelloWorld.hex"
	@echo 'Finished building: $@'
	@echo ' '

HelloWorld.lst: HelloWorld.elf
	@echo 'Invoking: ARM Linux GNU Create Listing'
	arm-elf-objdump -h -S HelloWorld.elf >"HelloWorld.lst"
	@echo 'Finished building: $@'
	@echo ' '

HelloWorld.siz: HelloWorld.elf
	@echo 'Invoking: ARM Linux GNU Print Size'
	arm-elf-size  --format=berkeley HelloWorld.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) HelloWorld.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
