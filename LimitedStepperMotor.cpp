/*
 LimitedStepperMotor.cpp

 Created on: 14.03.2018
 Author: Lion
 */


#include "EEPROM.h"
#include "Arduino.h"
#include "LimitedStepperMotor.h"

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

/*Laesst den Motor die angegebene Zahl an Schritten ausfuehren.
 Eine negative Anzahl von Schritten laesst den Motor rueckwaerts laufen.
 Die gesetzten Einschraenkungen von Null- und Grenzsetllung werden eingehalten.*/
bool LimitedStepperMotor::step(int steps) {
	int direction = steps > 0; //Richtung bestimmen
	int numberOfSteps = abs(steps); // Anzahl der Schritte bestimmen

	for (int i = 0; i < numberOfSteps && !stop; ++i) {
		if ((CurrentSteps == Limit && direction == 1)
				|| (CurrentSteps == 0 && direction == 0))
			break;

		if (direction == 1) {
			Stepper::step(singleToLimitStep);
			CurrentSteps++;
		}
		if (direction == 0) {
			Stepper::step(singleTo0Step);
			CurrentSteps--;
		}
	}
	return fixStop();
}

/*
 * Setzt die Position des Motors wieder auf 0.
 * Nutzt den angegebenen Endschalter zur Erkennung.
 */
bool LimitedStepperMotor::calibrateZeroing() {
	while (digitalRead(deactivationPin) != 0 && !stop) {
		Stepper::step(singleTo0Step);
	}
	if (!stop)
		CurrentSteps = 0;
	return fixStop();
}

/*
 Startet das manuelle kalibrieren.
 Wenn der Knopf l�nger als eine halbe Sekunde gedr�ckt wird, wird abgebrochen.
 Ansonsten bewegt sich der Motor solange nach unten bis der Knopf erneut gedrueckt wird.
 Die Position wird im EEPROM gespeichert und beim naechsten starten neu ausgelesen.

 Rueckgabe: true im Normalfall - false falls in irgend einer Form abgebrochen wurde
 */
bool LimitedStepperMotor::calibrateLimitManually(int stoppingPin) {
	pinMode(stoppingPin, INPUT); //Eingangangsmodus fuer Pin sicherstellen.
	long callTime = millis();

	/*Abbrechen behandeln*/
	do {
		if (digitalRead(stoppingPin) == 0) {
			break;
		}
	} while (millis() - callTime <= 500);

	while (digitalRead(stoppingPin) == 1) {
		callTime = -1;
	}
	if (callTime == -1)
		return false;

	//backup machen falls abgebrochen wird
	int oldLimit = Limit;
	Limit = 0;
	if (!calibrateZeroing()) {
		Limit = oldLimit;
		return false;
	}; //zurueckstellen auf die Nullstellung

	while (digitalRead(stoppingPin) != 1 && !stop) {
		Stepper::step(singleToLimitStep);
		Limit++;
	}
	if (stop) { //falls von au�en abgebrochen werden sollte wird das limit zurueckgesetzt
		Limit = oldLimit;
		return fixStop();
	}
	saveLimit();
	moveToZero(); //wieder auf die Nullstellung gehen
	return true;
}

/*Stellt den Motor an die oberste Position*/
bool LimitedStepperMotor::moveToZero() {
	while (CurrentSteps != 0 && !stop) {
		Stepper::step(singleTo0Step);
		CurrentSteps--;
	}
	return fixStop();
}

/*Stellt den Motor an die unterste Position*/
bool LimitedStepperMotor::moveToLimit() {
	while (CurrentSteps != Limit && !stop) {
		Stepper::step(singleToLimitStep);
		CurrentSteps++;
	}
	return fixStop();
}

bool LimitedStepperMotor::moveToPosition(unsigned int position) {
	if (position == CurrentSteps)
		return true;

	while (position > CurrentSteps && !stop) {
		step(-1);
	}
	while (position < CurrentSteps && !stop) {
		step(1);
	}
	return fixStop();
}

void LimitedStepperMotor::test() {
	calibrateZeroing();
	moveToLimit();
	moveToZero();
}
