/*
 * LED.h
 *
 *  Created on: 13.03.2018
 *      Author: Lion
 */

#ifndef HELPER_LED_H_
#define HELPER_LED_H_

class LED {
private:
	int m_pin;

public:
	LED(int pin);

	void test();

	void On();
	void Off();
	void An() {On();};
	void Aus() {Off();};
};

#endif /* HELPER_LED_H_ */
