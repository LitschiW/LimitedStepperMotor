################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
..\libraries\StandardCplusplus\examples\string_vector\string_vector.ino 

INO_DEPS += \
.\StandardCplusplus\examples\string_vector\string_vector.ino.d 


# Each subdirectory must supply rules for building sources it contributes
StandardCplusplus\examples\string_vector\string_vector.o: D:\GitHub\Privat\LimitedStepper\libraries\StandardCplusplus\examples\string_vector\string_vector.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\Programme(ext)\Eclipse\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"D:\Programme(ext)\Eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.19\cores\arduino" -I"D:\Programme(ext)\Eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.19\variants\standard" -I"D:\Programme(ext)\Eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.19\libraries\EEPROM" -I"D:\Programme(ext)\Eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.19\libraries\EEPROM\src" -I"D:\Programme(ext)\Eclipse\arduinoPlugin\libraries\Stepper\1.1.2" -I"D:\Programme(ext)\Eclipse\arduinoPlugin\libraries\Stepper\1.1.2\src" -I"D:\GitHub\Privat\LimitedStepper\libraries\StandardCplusplus" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


