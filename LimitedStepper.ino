#include "Arduino.h"
#include "LimitedStepperMotor.h"

/*Einstellungen Motor*/

//Speicherort im EEPROM
const int EEPROMCell = 0;
//Schritte des Schrittmotors (sollte irgendow drauf bzw. in der Beschreibung stehen)
const int number_of_Steps = 4800;
//Pins mit den der Motor/Driver/die Steuereinheit verbunden ist (ggf. auf 2 verringern)
const int Pins_StepperMotor[] = {8, 9, 10, 11};
//invertiert Hoch und Runter f�r den Motor
const bool invertiereMotor = false;
//Grundgeschwindigkeit des Motors in Umdrehungen pro Minute.
const int speed = 120;

/*Einstellungen Eing�nge*/

//eingang des Endschalters
const int Pin_Endschalter = 2;
//Eingang der das manuelle Kalibrieren starten soll.
const int Pin_ManuelleKalibrierungTrigger = 3;
//Eingang der das Hochfahren ausl�sen soll
const int Pin_HochfahrTrigger = 4;
//Eingang der das Runterfahren ausl�sen soll
const int Pin_RunterfahrTrigger = 5;


//Motor anlegen, evtl muss hier ebenfalls auf 2 Pins umgestellt werden.
LimitedStepperMotor motor(EEPROMCell, number_of_Steps, Pins_StepperMotor[0], Pins_StepperMotor[1], Pins_StepperMotor[2], Pins_StepperMotor[3]);

//The setup function is called once at startup of the sketch
void setup()
{
  //Eing�nge auf INPUT schalten
  pinMode(Pin_Endschalter, INPUT);
  pinMode(Pin_ManuelleKalibrierungTrigger, INPUT);
  pinMode(Pin_HochfahrTrigger, INPUT);
  pinMode(Pin_RunterfahrTrigger, INPUT);

  //motor Konfiguration von oben �bernehmen
  motor.setDeactivationPin(Pin_Endschalter);
  motor.setInverted(invertiereMotor);
  motor.setSpeed(speed);

  //startet die Kalibrierung des oberen Anschlags (s. in der Klasse LimitedStepperMotor.cpp)
  motor.calibrateTop();
}

// The loop function is called in an endless loop
void loop()
{
  //Eing�nge verarbeiten
  if (digitalRead(Pin_ManuelleKalibrierungTrigger) == 1)
  {
    delay(1000);
    motor.calibrateManually(Pin_ManuelleKalibrierungTrigger);
  }
  else if (digitalRead(Pin_HochfahrTrigger) == 1)
  {
    motor.goUp();
  }
  else if (digitalRead(Pin_RunterfahrTrigger) == 1)
  {
    motor.goDown();
  }
}
