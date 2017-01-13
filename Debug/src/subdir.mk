################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lcd.c \
../src/main.c \
../src/rozne.c 

OBJS += \
./src/lcd.o \
./src/main.o \
./src/rozne.o 

C_DEPS += \
./src/lcd.d \
./src/main.d \
./src/rozne.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DNUCLEO_F401RE -DSTM32F4 -DSTM32F401RETx -DSTM32 -DDEBUG -I"C:/Users/ja/workspace_stm/lcd_mieszane/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


