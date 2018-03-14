/*
 * TorStepper.cpp
 *
 *  Created on: 14.03.2018
 *      Author: Lion
 */

#include "LimitedStepperMotor.h"

#include "EEPROM.h"


LimitedStepperMotor::LimitedStepperMotor(int EEPROMIndex,int number_of_steps, int motor_pin_1, int motor_pin_2) : Stepper(number_of_steps, motor_pin_1, motor_pin_2){
	this->EEPROMIndex = EEPROMIndex;
}

LimitedStepperMotor::LimitedStepperMotor(int EEPROMIndex,int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4)
	 : Stepper(number_of_steps, motor_pin_1, motor_pin_2,  motor_pin_3,  motor_pin_4){
	this->EEPROMIndex = EEPROMIndex;
}


void LimitedStepperMotor::step(int numberOfSteps)
{
	int direction = numberOfSteps > 0;
	numberOfSteps = abs(numberOfSteps);

	for (int i = 0; i < numberOfSteps ; ++i) {
		if(currentLocation==limit||currentLocation == 0) break;

		if(direction == 1){//Tor bewegt sich nach unten
			Stepper::step(singleDownStep);
			currentLocation++;
		}
		if(direction == 0){//Tor bewegt sich nach oben
			Stepper::step(singleUpStep);
			currentLocation--;
		}
	}
}

/**/
void LimitedStepperMotor::calibrateTop()
{
	while(digitalRead(deactivationPin)!=0)
	{
		Stepper::step(singleUpStep);
	}
	currentLocation = 0;
}

void LimitedStepperMotor::calibrateManually(int stoppingPin)
{
	int limitcopy = limit;
	limit = 0;
	calibrateTop();
	pinMode(stoppingPin,INPUT);

	while(digitalRead(stoppingPin)!=1)
	{
		Stepper::step(singleDownStep);
		limit++;
	}
	saveLimit();
	goUp();
}

void LimitedStepperMotor::goUp()
{
	while(currentLocation != 0)
	{
		Stepper::step(singleUpStep);
		currentLocation--;
	}
}


void LimitedStepperMotor::goDown()
{
	while(currentLocation != limit)
	{
		Stepper::step(singleDownStep);
		currentLocation++;
	}
}


