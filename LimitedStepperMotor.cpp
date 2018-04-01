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
  loadLimit();
}

LimitedStepperMotor::LimitedStepperMotor(int EEPROMIndex, int number_of_steps,
    int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) :
  Stepper(number_of_steps, motor_pin_1, motor_pin_2, motor_pin_3,
          motor_pin_4) {
  this->EEPROMIndex = EEPROMIndex;
  loadLimit();
}

/*Laesst den Motor die angegebene Zahl an Schritten ausfuehren.
  Eine negative Anzahl von Schritten laesst den Motor rueckwaerts laufen.
  Die gesetzten Einschraenkungen von Null- und Grenzsetllung werden eingehalten.*/
bool LimitedStepperMotor::step(int steps) {
  return step(steps, false);
}

bool LimitedStepperMotor::step(int steps, bool forced) {
  int direction = steps > 0; //Richtung bestimmen
  int numberOfSteps = abs(steps); // Anzahl der Schritte bestimmen

  for (int i = 0; i < numberOfSteps && !stop; ++i) {
    if (!forced &&
        ((CurrentSteps == Limit && direction == 1) || ( digitalRead(deactivationPin) == 1 && direction == 0)))
      return false;

    if (direction == 1) {
      Stepper::step(singleToLimitStep);
      CurrentSteps++;
    }
    if (direction == 0) {
      Stepper::step(singleTo0Step);
      CurrentSteps--;
    }
  }
  if (Serial && CurrentSteps % 50  == 0) {
    Serial.print("Steps: ");
    Serial.println(CurrentSteps);
  }
  return true;
}

/*
   Setzt die Position des Motors wieder auf 0.
   Nutzt den angegebenen Endschalter zur Erkennung.
*/
bool LimitedStepperMotor::calibrateZeroing() {
  if (Serial)Serial.println("Kalibriere Nullstellung...");
  while (digitalRead(deactivationPin) == 0 && !stop) {
    step(-1, true);
  }
  if (!stop)
    CurrentSteps = 0;
  if (Serial)Serial.println("Nullstellung gefunden.");
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
  if (Serial) Serial.println("Manuelle Kalibrierung...");

  pinMode(stoppingPin, INPUT); //Eingangangsmodus fuer Pin sicherstellen.

  /*Abbrechen behandeln
    long callTime = millis();
    do {
    if (digitalRead(stoppingPin) == 0) {
      if (callTime == -1)
        return false;	break;
    }
    } while (millis() - callTime <= 500);*/

  while (digitalRead(stoppingPin) == 1) {
    ;//warten, dass der Knopf losgelassen wird
  }

  //backup machen falls abgebrochen wird
  int oldLimit = Limit;
  Limit = 0;

  if (!calibrateZeroing()) {
    Limit = oldLimit;
    return false;
  }; //zurueckstellen auf die Nullstellung

  while (digitalRead(stoppingPin) != 1 && !stop) {
    step(1, true);
    Limit++;
  }
  while (digitalRead(stoppingPin) == 1) {
    ;//warten, dass der Knopf wieder losgelassen wird
  }

  if (stop) { //falls von aussen abgebrochen werden sollte wird das limit zurueckgesetzt
    Limit = oldLimit;
    return fixStop();
  }
  saveLimit();
  moveToZero(); //wieder auf die Nullstellung gehen

  if (Serial)Serial.println("Fertig Kalibriert...");

  return true;
}

/*Stellt den Motor an die oberste Position. Bicht ab, wenn der Endschalter berührt wird.*/
void LimitedStepperMotor::moveToZero() {
  if (Serial)Serial.println("Bewegen zu Nullstellung...");

  bool continueStepping = true;
  do {
    continueStepping = step(-1);
  }
  while (continueStepping);
  if (Serial)Serial.println("Nullstellung erreicht...");
}

/*Stellt den Motor an die unterste Position*/
void LimitedStepperMotor::moveToLimit() {
  if (Serial)Serial.println("Bewegen zu Grenzstellung...");

  bool continueStepping = true;
  do {
    continueStepping = step(1);
  }
  while (continueStepping);
  if (Serial)Serial.println("Grenzstellung erreicht...");
}

bool LimitedStepperMotor::moveToPosition(unsigned int targetPosition) {

  if (Serial) {
    Serial.print("Bewegen zur Schrittanzahl ");
    Serial.println(targetPosition);
  }
  
  while (targetPosition > CurrentSteps && !stop) {
    step(1);
  }
  while (targetPosition < CurrentSteps && !stop) {
    step(-1);
  }
  
  if(Serial){Serial.print("Schrittanzahl erreicht!");}
  return fixStop();
}

bool LimitedStepperMotor::moveToPositionPercentage(double percentage)
{
  int steps = min(Limit, Limit * max(0, percentage));
  return  moveToPosition(steps);
}

void LimitedStepperMotor::test() {
  calibrateZeroing();
  moveToLimit();
  moveToZero();
}

