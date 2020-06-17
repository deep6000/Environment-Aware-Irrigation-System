################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/comm_txrx.c \
../src/common.c \
../src/controlNodeFunctions.c \
../src/gpio_interrupt.c \
../src/heartbeat.c \
../src/logger.c \
../src/main.c \
../src/main_task.c \
../src/posixtimers.c \
../src/printtime.c \
../src/signalhandler.c \
../src/uart_driver.c 

OBJS += \
./src/comm_txrx.o \
./src/common.o \
./src/controlNodeFunctions.o \
./src/gpio_interrupt.o \
./src/heartbeat.o \
./src/logger.o \
./src/main.o \
./src/main_task.o \
./src/posixtimers.o \
./src/printtime.o \
./src/signalhandler.o \
./src/uart_driver.o 

C_DEPS += \
./src/comm_txrx.d \
./src/common.d \
./src/controlNodeFunctions.d \
./src/gpio_interrupt.d \
./src/heartbeat.d \
./src/logger.d \
./src/main.d \
./src/main_task.d \
./src/posixtimers.d \
./src/printtime.d \
./src/signalhandler.d \
./src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"E:\Software\gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_win32" -I"C:\Users\Madhumitha\eclipse-workspace\ControlNode\inc" -O0 -g3 -Wall -c -fmessage-length=0 -lpthread -lm -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


