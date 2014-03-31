################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/spells/fireball.cpp 

OBJS += \
./source/spells/fireball.o 

CPP_DEPS += \
./source/spells/fireball.d 


# Each subdirectory must supply rules for building sources it contributes
source/spells/%.o: ../source/spells/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\include" -I"C:\MinGW\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


