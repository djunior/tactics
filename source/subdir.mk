################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/animation.cpp \
../source/board.cpp \
../source/drawFunctions.cpp \
../source/fps.cpp \
../source/gameManager.cpp \
../source/gameConfig.cpp \
../source/main.cpp \
../source/menu.cpp \
../source/mouse.cpp \
../source/spell.cpp \
../source/unit.cpp 

OBJS += \
./source/animation.o \
./source/board.o \
./source/drawFunctions.o \
./source/fps.o \
./source/gameManager.o \
./source/gameConfig.o \
./source/main.o \
./source/menu.o \
./source/mouse.o \
./source/spell.o \
./source/unit.o 

CPP_DEPS += \
./source/animation.d \
./source/board.d \
./source/drawFunctions.d \
./source/fps.d \
./source/gameManager.d \
./source/gameConfig.d \
./source/main.d \
./source/menu.d \
./source/mouse.d \
./source/spell.d \
./source/unit.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\include" -I"C:\MinGW\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


