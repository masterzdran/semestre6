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
xpto.hex \

SECONDARY_LIST += \
xpto.lst \

SECONDARY_SIZE += \
xpto.siz \


# All Target
all: xpto.elf secondary-outputs

# Tool invocations
xpto.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM devkitPro Linux GCC C Linker'
	arm-eabi-gcc -T"target.ld" -nostdlib -L/home/masterzdran/WorkingArea/Isel/semestre6/SE2/workplace/code/src/eCos/lib -Wl,-Map,xpto.map -mcpu=arm7tdmi-s -g3 -gdwarf-2 -o"xpto.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

xpto.hex: xpto.elf
	@echo 'Invoking: ARM devkitPro Linux GNU Create Flash Image'
	arm-eabi-objcopy -O ihex xpto.elf "xpto.hex"
	@echo 'Finished building: $@'
	@echo ' '

xpto.lst: xpto.elf
	@echo 'Invoking: ARM devkitPro Linux GNU Create Listing'
	arm-eabi-objdump -h -S xpto.elf >"xpto.lst"
	@echo 'Finished building: $@'
	@echo ' '

xpto.siz: xpto.elf
	@echo 'Invoking: ARM devkitPro Linux GNU Print Size'
	arm-eabi-size  --format=berkeley xpto.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) xpto.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
