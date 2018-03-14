/*
   LimitedStepperMotor.h

    Created on: 14.03.2018
        Author: Lion
*/

#ifndef LIMITEDSTEPPERMOTOR_H_
#define LIMITEDSTEPPERMOTOR_H_

#include <Stepper.h>
#include "Arduino.h"
#include "EEPROM.h"

class LimitedStepperMotor : public Stepper {
  public:
    LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1, int motor_pin_2);

    LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void setDeactivationPin(int pin) {
      deactivationPin = pin;
      pinMode(pin, INPUT);
    };

    void calibrateTop();

    void setMaxStepNumber(unsigned int steps) {
      limit = steps;
    };

    void calibrateManually(int pinToWatch);

    void goDown();

    void goUp();

    void step(int numberOfSteps);

    void setInverted(bool inverted) {
      if (inverted) {
        singleDownStep = -1;
        singleUpStep = 1;
      }
      else {
        singleDownStep = 1;
        singleUpStep = -1;
      }
    }

  private:
    int deactivationPin = 0; // Pinnummer des Endschalter-Signals
    unsigned int currentLocation = 0; //enthält die aktuelle Position
    unsigned int limit = 1;
    int EEPROMIndex;

    //Diese Variablen werden beim invertieren umgedreht
    int singleDownStep = 1; //Beschreibt die Anzahl an Schritten die einem Schritt nach unten entsprechen soll
    int singleUpStep = -1;//Beschreibt die Anzahl an Schritten die einem Schritt nach oben entsprechen soll

    void saveLimit()
    {
      EEPROM.write(EEPROMIndex, limit);
    }

    void loadLimit()
    {
      int newLimit = EEPROM.read(EEPROMIndex);
      if (newLimit <= 0) newLimit = 0; //stellt sicher dass das limit mid. 0 ist
      limit = newLimit;
    }
};
#endif /* LIMITEDSTEPPERMOTOR_H_ */
