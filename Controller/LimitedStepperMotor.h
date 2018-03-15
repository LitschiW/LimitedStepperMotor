/*
 LimitedStepperMotor.h

 Created on: 14.03.2018
 Author: Lion
 */

#ifndef CONTROLLER_LIMITEDSTEPPERMOTOR_H_
#define CONTROLLER_LIMITEDSTEPPERMOTOR_H_

#include <Stepper.h>
#include "Arduino.h"
#include "EEPROM.h"

class LimitedStepperMotor: public Stepper {
public:
	unsigned int Limit = 1;

	LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1,
			int motor_pin_2);

	LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1,
			int motor_pin_2, int motor_pin_3, int motor_pin_4);

	/*Legt fest auf welchem Pin der Endschalter liegt*/
	void setDeactivationPin(int pin) {
		deactivationPin = pin;
		pinMode(pin, INPUT);
	}
	;

	bool calibrateZeroing();

	/*fociert ein Maximum ohne eine manuelle Kalibierung*/
	void setMaxStepNumber(unsigned int steps) {
		Limit = steps;
	}
	;

	/*startet die manuelle calibierung*/
	bool calibrateLimitManually(int activationPin);

	bool moveToLimit();

	bool moveToZero();

	void step(int steps);

	/*Lässt den Motor folgende Bewegung ausführen:
	 * 	- Nullstellung (mit Kalibierung)
	 * 	- Endstellung
	 * 	- Nullstellung
	 */
	void test();

	/* Bietet die Moeglichkeit von den Motor während der Bewegung zu stoppen.
	 * Es ist zu beachten, dass die Bewegung eines Motors ein blockierender Aufruf ist.
	 * D.h. es macht nur Sinn diese Methode von einem parallen task o.ä. aufzurufen.
	 */
	void stopMovement(){stop = true;};

	/*Kann genutzt werden um den Schrittmotor zu invertieren.*/
	void setInverted(bool inverted) {
		if (inverted) {
			singleDownStep = -1;
			singleUpStep = 1;
		} else {
			singleDownStep = 1;
			singleUpStep = -1;
		}
	}

private:
	int deactivationPin = 0; // Pinnummer des Endschalter-Signals
	unsigned int currentLocation = 0; //die aktuelle Schritt Position
	int EEPROMIndex; //EEPROM Addresse an der das limit gespeichert werden soll

	//Diese Variablen werden beim invertieren umgedreht
	int singleDownStep = 1; //Beschreibt die Anzahl an Schritten die einem Schritt nach unten entsprechen soll
	int singleUpStep = -1; //Beschreibt die Anzahl an Schritten die einem Schritt nach oben entsprechen soll

	bool stop = false;

	void saveLimit() {
		EEPROM.write(EEPROMIndex, Limit);
	}

	void loadLimit() {
		int newLimit = EEPROM.read(EEPROMIndex);
		if (newLimit <= 0)
			newLimit = 0; //stellt sicher, dass das limit mindestens 0 ist.
		Limit = newLimit;
	}

	bool fixStop() {
		if (stop) {
			stop = false;
			return false;
		}
		return true;
	}
};
#endif /* CONTROLLER_LIMITEDSTEPPERMOTOR_H_ */
