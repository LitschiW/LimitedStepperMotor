/*
 * LED.cpp
 *
 *  Created on: 13.03.2018
 *      Author: Lion
 */

#include "LED.h"
#include "Arduino.h"

LED::LED(int pin)
{
	m_pin = pin;
	pinMode(pin,OUTPUT);
}

void LED::On()
{
	digitalWrite(m_pin,HIGH);
}

void LED::Off()
{
	digitalWrite(m_pin,LOW);
}

/**/
void LED::test()
{
	int bigInterval = 3000;
	int littleInterval = 500;
	On();
	delay(bigInterval);
	for (int var = 0; var < m_pin+1; ++var) {
		delay(littleInterval);
		Off();
		delay(littleInterval);
		On();
	}

	delay(bigInterval);Off();
}
