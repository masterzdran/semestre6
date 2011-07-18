################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../automato.c 

OBJS += \
./automato.o 

C_DEPS += \
./automato.d 


# Each subdirectory must supply rules for building sources it contributes
automato.o: /home/masterzdran/WorkingArea/Isel/semestre6/SE2/workplace/code/src/program/Automato/automato.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM devkitPro Linux GCC C Compiler'
	arm-eabi-gcc -I/home/masterzdran/WorkingArea/Isel/semestre6/SE2/workplace/code/src/eCos/include -I/home/masterzdran/WorkingArea/Isel/semestre6/SE2/workplace/code/src/include_eCos -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi-s -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


