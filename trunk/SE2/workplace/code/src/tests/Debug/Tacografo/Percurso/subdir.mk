################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tacografo/Percurso/Percurso.c 

OBJS += \
./Tacografo/Percurso/Percurso.o 

C_DEPS += \
./Tacografo/Percurso/Percurso.d 


# Each subdirectory must supply rules for building sources it contributes
Tacografo/Percurso/%.o: ../Tacografo/Percurso/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux GCC C Compiler'
	arm-elf-gcc -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


