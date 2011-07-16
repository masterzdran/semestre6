################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tacografo/Menu/Menu.c \
../Tacografo/Menu/MenuFunctions.c 

OBJS += \
./Tacografo/Menu/Menu.o \
./Tacografo/Menu/MenuFunctions.o 

C_DEPS += \
./Tacografo/Menu/Menu.d \
./Tacografo/Menu/MenuFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Tacografo/Menu/%.o: ../Tacografo/Menu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux GCC C Compiler'
	arm-elf-gcc -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


