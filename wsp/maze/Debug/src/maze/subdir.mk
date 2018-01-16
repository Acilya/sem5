################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/maze/Colors.cpp \
../src/maze/maze.cpp 

OBJS += \
./src/maze/Colors.o \
./src/maze/maze.o 

CPP_DEPS += \
./src/maze/Colors.d \
./src/maze/maze.d 


# Each subdirectory must supply rules for building sources it contributes
src/maze/%.o: ../src/maze/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


