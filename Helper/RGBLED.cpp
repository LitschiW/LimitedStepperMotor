/*
 * RGBLED.cpp
 *
 *  Created on: 13.03.2018
 *      Author: Lion
 */

#include "RGBLED.h"
#include "Arduino.h"

RGBLED::RGBLED(int red,int green,int blue) {
	m_red = red;
	m_green = green;
	m_blue = blue;
	pinMode(m_red,OUTPUT);
	pinMode(m_green,OUTPUT);
	pinMode(m_blue,OUTPUT);
}

void RGBLED::setColor(int red, int green,int blue)
{
	analogWrite(m_red,255-red);
	analogWrite(m_green,255-green);
	analogWrite(m_blue,255-blue);
}

