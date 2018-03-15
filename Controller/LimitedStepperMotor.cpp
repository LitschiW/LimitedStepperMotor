/*
 LimitedStepperMotor.cpp

 Created on: 14.03.2018
 Author: Lion
 */

#include "Controller/LimitedStepperMotor.h"

#include "EEPROM.h"
#include "Arduino.h"

LimitedStepperMotor::LimitedStepperMotor(int EEPROMIndex, int number_of_steps,
		int motor_pin_1, int motor_pin_2) :
		Stepper(number_of_steps, motor_pin_1, motor_pin_2) {
	this->EEPROMIndex = EEPROMIndex;
}

LimitedStepperMotor::LimitedStepperMotor(int EEPROMIndex, int number_of_steps,
		int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) :
		Stepper(number_of_steps, motor_pin_1, motor_pin_2, motor_pin_3,
				motor_pin_4) {
	this->EEPROMIndex = EEPROMIndex;
}

/*L�sst den Motor die angegebene Zahl an Schritten ausf�hren.
 Eine negative Anzahl von Schritten l�sst den Motor r�ckw�rts laufen.
 Die gesetzten einschr�nkungen werden eingehalten.*/
void LimitedStepperMotor::step(int numberOfSteps) {
	int direction = numberOfSteps > 0;
	numberOfSteps = abs(numberOfSteps);

	for (int i = 0; i < numberOfSteps; ++i) {
		if (currentLocation == limit || currentLocation == 0)
			break;

		if (direction == 1) { //Tor bewegt sich nach unten
			Stepper::step(singleDownStep);
			currentLocation++;
		}
		if (direction == 0) { //Tor bewegt sich nach oben
			Stepper::step(singleUpStep);
			currentLocation--;
		}
	}
}

/*
 * Setzt die Position des Motors wieder auf 0.
 * Nutzt den angegebenen Endschalter zur Erkennung.
 */
void LimitedStepperMotor::calibrateZeroing() {
	while (digitalRead(deactivationPin) != 0) {
		Stepper::step(singleUpStep);
	}
	currentLocation = 0;
}

/*
 Startet das manuelle kalibrieren.
 Wenn nach einer halben Sekunde der Knopf noch gedr�ckt ist, wird abgebrochen.
 Ansonsten bewegt sich der Motor solange nach unten bis der Knopf erneut gedr�ckt wird.
 Die Position wird im EEPROM gespeichert und beim n�chsten starten neu ausgelesen.
 */
void LimitedStepperMotor::calibrateLimitManually(int stoppingPin) {
	pinMode(stoppingPin, INPUT); //Eingangangsmodus f�r Pin sicherstellen.

	delay(500);
	if (digitalRead(stoppingPin) == 1)
		return;

	limit = 0;
	calibrateZeroing(); //zur�ckstellen auf die oberste Position.

	while (digitalRead(stoppingPin) != 1) {
		Stepper::step(singleDownStep);
		limit++;
	}
	saveLimit();
	moveToZero(); //Wieder ganz nach oben stellen.
}

/*Stellt den Motor an die oberste Position*/
void LimitedStepperMotor::moveToZero() {
	while (currentLocation != 0) {
		Stepper::step(singleUpStep);
		currentLocation--;
	}
}

/*Stellt den Motor an die unterste Position*/
void LimitedStepperMotor::moveToLimit() {
	while (currentLocation != limit) {
		Stepper::step(singleDownStep);
		currentLocation++;
	}
}

