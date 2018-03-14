/*
 * TorStepper.h
 *
 *  Created on: 14.03.2018
 *      Author: Lion
 */

#ifndef LIMITEDSTEPPERMOTOR_H_
#define LIMITEDSTEPPERMOTOR_H_

#include <Stepper.h>
#include "Arduino.h"
#include "EEPROM.h"

class LimitedStepperMotor : public Stepper {
public:

	LimitedStepperMotor(int EEPROMIndex,int number_of_steps, int motor_pin_1, int motor_pin_2) : Stepper(number_of_steps, motor_pin_1, motor_pin_2){
		this->EEPROMIndex = EEPROMIndex;
	}

	LimitedStepperMotor(int EEPROMIndex,int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4)
		 : Stepper(number_of_steps, motor_pin_1, motor_pin_2,  motor_pin_3,  motor_pin_4){
		this->EEPROMIndex = EEPROMIndex;
	}

	void setDeactivationPin(int pin){deactivationPin = pin; pinMode(pin,INPUT); };

	void calibrateTop();

	void setMaxStepNumber(int steps) {limit = steps;};

	void calibrateManually(int pinToWatch);

	void goDown();

	void goUp();

	void step(int numberOfSteps);

	void setInverted(bool inverted) {
		if(inverted) {
			singleDownStep = -1;
			singleUpStep = 1;
		}
		else {
			singleDownStep = 1;
			singleUpStep = -1;
		}
	}

private:
	int inverted = 1;
	int deactivationPin=0;
	int currentLocation = 0;
	int limit = 0;
	int EEPROMIndex;
	int singleDownStep = 1;
	int singleUpStep = -1;

	void LimitedStepperMotor::saveLimit()
	{
		EEPROM.write(EEPROMIndex, limit);
	}

	void LimitedStepperMotor::loadLimit()
	{
		int newLimit = EEPROM.read(EEPROMIndex);
		if(newLimit<=0) newLimit = 0;
		limit = newLimit;
	}
};
#endif /* LIMITEDSTEPPERMOTOR_H_ */
