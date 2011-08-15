################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EncoderCore.cpp \
../EncoderDecorator.cpp \
../EncoderInterface.cpp \
../EncoderLengthDecorator.cpp \
../EncoderTypeDecorator.cpp 

OBJS += \
./EncoderCore.o \
./EncoderDecorator.o \
./EncoderInterface.o \
./EncoderLengthDecorator.o \
./EncoderTypeDecorator.o 

CPP_DEPS += \
./EncoderCore.d \
./EncoderDecorator.d \
./EncoderInterface.d \
./EncoderLengthDecorator.d \
./EncoderTypeDecorator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega168p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


