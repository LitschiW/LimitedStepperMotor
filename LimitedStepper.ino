#include "Arduino.h"
#include "LimitedStepperMotor.h"
#include "StandardCplusplus.h"
#include <vector>

using namespace std;

/*Einstellungen Motor*/

//Speicherort im EEPROM
const int EEPROMCell = 0;
//Schritte des Schrittmotors (sollte irgendwo drauf bzw. in der Beschreibung stehen)
const int number_of_Steps = 4800;
//Pins mit den der Motor/Driver/die Steuereinheit verbunden ist (ggf. auf 2 verringern)
const int Pins_StepperMotor[] = {8, 9, 10, 11};
//invertiert die Motorrichtung
const bool invertiereMotor = false;
//Grundgeschwindigkeit des Motors in Umdrehungen pro Minute.
const int geschwindigkeit = 120;

/*Einstellungen Eingaenge*/

//eingang des Endschalters
const int Pin_Endschalter = 2;
//Eingang der das manuelle Kalibrieren starten und beenden soll.
const int Pin_ManuelleKalibrierungTrigger = 3;
//Eingang der das Fahren zur Nullstellung ausloesen soll
const int Pin_HochfahrTrigger = 4;
//Eingang der das Fahren zur Endstellung ausloesen soll
const int Pin_RunterfahrTrigger = 5;


//Motor anlegen, evtl muss hier ebenfalls auf 2 Pins umgestellt werden.
LimitedStepperMotor motor(EEPROMCell, number_of_Steps, Pins_StepperMotor[0], Pins_StepperMotor[1], Pins_StepperMotor[2], Pins_StepperMotor[3]);

void setup()
{
	vector<int> vec;
  //Eingaenge auf INPUT schalten
  pinMode(Pin_Endschalter, INPUT);
  pinMode(Pin_ManuelleKalibrierungTrigger, INPUT);
  pinMode(Pin_HochfahrTrigger, INPUT);
  pinMode(Pin_RunterfahrTrigger, INPUT);

  //Motor Konfiguration uebernehmen
  motor.setDeactivationPin(Pin_Endschalter);
  motor.setInverted(invertiereMotor);
  motor.setSpeed(geschwindigkeit);

  //startet die Kalibrierung des oberen Anschlags (s. in der Klasse LimitedStepperMotor.cpp)
  motor.calibrateZeroing();
}

void loop()
{
  //Eingaenge verarbeiten
  if (digitalRead(Pin_ManuelleKalibrierungTrigger) == 1)
  {
    motor.calibrateLimitManually(Pin_ManuelleKalibrierungTrigger);
  }
  else if (digitalRead(Pin_HochfahrTrigger) == 1)
  {
    motor.moveToZero();
  }
  else if (digitalRead(Pin_RunterfahrTrigger) == 1)
  {
    motor.moveToLimit();
  }
}
