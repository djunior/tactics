################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/unit_class/knight.cpp \
../source/unit_class/wizard.cpp 

OBJS += \
./source/unit_class/knight.o \
./source/unit_class/wizard.o 

CPP_DEPS += \
./source/unit_class/knight.d \
./source/unit_class/wizard.d 


# Each subdirectory must supply rules for building sources it contributes
source/unit_class/%.o: ../source/unit_class/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\include" -I"C:\MinGW\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


