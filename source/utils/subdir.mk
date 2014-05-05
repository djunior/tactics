################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/utils/sprite.cpp 

OBJS += \
./source/utils/sprite.o 

CPP_DEPS += \
./source/utils/sprite.d 


# Each subdirectory must supply rules for building sources it contributes
source/utils/%.o: ../source/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\include" -I"C:\MinGW\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


