#include "Arduino.h"
#include "LimitedStepperMotor.h"

//
const int EEPROMCell = 0;
const int number_of_Steps = 4800;
const int Pins_StepperMotor[] = {8,9,10,11};
const bool invertiereMotor = false;

const int Pin_Endschalter = 0;
const int Pin_ManuelleKonfigurationTrigger = 1;
const int Pin_HochfahrTrigger=2;
const int Pin_RunterfahrTrigger=3;


LimitedStepperMotor motor(EEPROMCell,number_of_Steps,Pins_StepperMotor[0],Pins_StepperMotor[1],Pins_StepperMotor[2],Pins_StepperMotor[3]);

//The setup function is called once at startup of the sketch
void setup()
{

	pinMode(Pin_Endschalter,INPUT);
	pinMode(Pin_ManuelleKonfigurationTrigger,INPUT);
	pinMode(Pin_HochfahrTrigger,INPUT);
	pinMode(Pin_RunterfahrTrigger,INPUT);

	motor.setDeactivationPin(Pin_Endschalter);
	motor.setInverted(invertiereMotor);

	motor.calibrateTop();
}

// The loop function is called in an endless loop
void loop()
{
	if(digitalRead(Pin_ManuelleKonfigurationTrigger) == 1)
	{
		delay(1000);
		motor.calibrateManually(Pin_ManuelleKonfigurationTrigger);
	}
	else if(digitalRead(Pin_HochfahrTrigger) == 1)
	{
		motor.goUp();
	}
	else if(digitalRead(Pin_RunterfahrTrigger) == 1)
	{
		motor.goDown();
	}
}
