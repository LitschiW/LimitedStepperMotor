/*
 * RGBLED.h
 *
 *  Created on: 13.03.2018
 *      Author: Lion
 */

#ifndef HELPER_RGBLED_H_
#define HELPER_RGBLED_H_

class RGBLED {
private:
	int m_red;
	int m_green;
	int m_blue;

public:
	RGBLED(int REDPin,int GREENPin,int BLUEPin);

	void setColor(int red,int green,int blue);
};

#endif /* HELPER_RGBLED_H_ */
