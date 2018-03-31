/*
  LimitedStepperMotor.h

  Created on: 14.03.2018
  Author: Lion
*/

#ifndef LIMITEDSTEPPERMOTOR_H_
#define LIMITEDSTEPPERMOTOR_H_

#include "Stepper.h"
#include "Arduino.h"
#include "EEPROM.h"

class LimitedStepperMotor: public Stepper {
  public:
    unsigned int Limit = 1;
    unsigned int CurrentSteps = 0; //die aktuelle Schritt Position

    LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1,
                        int motor_pin_2);

    LimitedStepperMotor(int EEPROMIndex, int number_of_steps, int motor_pin_1,
                        int motor_pin_2, int motor_pin_3, int motor_pin_4);

    /*Legt fest auf welchem Pin der Endschalter liegt*/
    void setDeactivationPin(int pin) {
      deactivationPin = pin;
      pinMode(pin, INPUT);
    }

    bool calibrateZeroing();

    /*fociert ein Maximum ohne eine manuelle Kalibierung*/
    void setMaxStepNumber(unsigned int steps) {
      Limit = steps;
    }

    /*startet die manuelle Kalibierung*/
    bool calibrateLimitManually(int activationPin);

    void moveToLimit();

    void moveToZero();

    bool moveToPosition(unsigned int position);

    bool moveToPositionPercentage(double percentage);
    
    bool step(int steps);

    /*Laesst den Motor folgende Bewegung ausfuehren:
      	- Nullstellung (mit Kalibierung)
      	- Endstellung
      	- Nullstellung
    */
    void test();

    /* Bietet die Moeglichkeit von den Motor waehrend der Bewegung zu stoppen.
       Es ist zu beachten, dass die Bewegung eines Motors ein blockierender Aufruf ist.
       D.h. es macht nur Sinn diese Methode von einem parallen task o.�. aufzurufen.
    */
    void stopMovement() {
      stop = true;
    };

    /*Kann genutzt werden um den Schrittmotor zu invertieren.*/
    void setInverted(bool inverted) {
      if (inverted) {
        singleToLimitStep = -1;
        singleTo0Step = 1;
      } else {
        singleToLimitStep = 1;
        singleTo0Step = -1;
      }
    }

  private:
    int deactivationPin = 0; // Pinnummer des Endschalter-Signals
    int EEPROMIndex; //EEPROM Addresse an der das limit gespeichert werden soll

    //Diese Variablen werden beim invertieren umgedreht
    int singleToLimitStep = 1; //Beschreibt die Anzahl an Schritten die einem Schritt nach unten entsprechen soll
    int singleTo0Step = -1; //Beschreibt die Anzahl an Schritten die einem Schritt nach oben entsprechen soll

    bool stop = false;

    void saveLimit() {
      if (Serial) {
        Serial.print("---savingLimit ");
        Serial.println(Limit);
      }

      for (int i = EEPROMIndex; i < EEPROMIndex + 4; i++)
      {
        int next = Limit >> 8 * (3 - i);
        EEPROM.write(i, next);
        if (Serial) {
          Serial.print("-Wrote ");
          Serial.print(EEPROM.read(i));
          Serial.print(" to address ");
          Serial.println(i);
        }
      }
    }

    void loadLimit() {
      if (Serial) Serial.println("---Laden...");
      unsigned int newLimit = 0;
      for (int i = EEPROMIndex; i < EEPROMIndex + 4; i++)
      {
        byte next = EEPROM.read(i);
        newLimit = (newLimit << 8) | next;
        if (Serial)
        {
          Serial.print("-Read ");
          Serial.print(next);
          Serial.print(" from Addres ");
          Serial.println(i);
          if (i < EEPROMIndex + 2) {
            Serial.print("-Current read limit: ");
            Serial.println(newLimit);
          }
        }
      }
      if (newLimit == 0)
      {
        newLimit = 1;
        EEPROM.write(EEPROMIndex + 3, 1);
      }
      if (Serial) {
        Serial.print("Limit geladen: ");
        Serial.println(newLimit);
      }
      Limit = newLimit;
    }

    bool step(int steps, bool forced);

    bool fixStop() {
      if (stop) {
        stop = false;
        return false;
      }
      return true;
    }
};
#endif /* CONTROLLER_LIMITEDSTEPPERMOTOR_H_ */
