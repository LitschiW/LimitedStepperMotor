/*
 * MultiLimtedStepperController.h
 *
 *  Created on: 15.03.2018
 *      Author: Lion
 */

#ifndef CONTROLLER_MULTILIMTEDSTEPPERCONTROLLER_H_
#define CONTROLLER_MULTILIMTEDSTEPPERCONTROLLER_H_

#include "LimitedStepperMotor.h"
#include <libraries/StandardCplusplus/vector>
using namespace std;

class MultiLimtedStepperController {
public:
	MultiLimtedStepperController();

	/*
	 * Registriert den Motor für die Steuerung.
	 */
	void AddMotor(LimitedStepperMotor motor);

	/*Deregistiert alle vorhanden motoren*/
	void Clear();

	/*Bewegt den Motor am angegeben Index in die Nullstellung*/
	void MoveTo0(int index);
	/*Bewegt den Motor am angegeben Index in die Endstellung*/
	void MoveToLimit(int index);

	/*Ist timedEqually = true,  wird versucht das Bewegen prozentual geshen synchron zu halten.
	 *Ist timedEqually = false, gehen alle Motorn ihre Schritte gleichzeitig,
	 * 							bis sie nicht mehr koennen.*/
	void MoveAllTo0Parallel(bool timedEqualy);
	/*Ist timedEqually = true,  wird versucht das Bewegen prozentual geshen synchron zu halten.
	 *Ist timedEqually = false, gehen alle Motorn ihre Schritte gleichzeitig,
	 * 							bis sie nicht mehr koennen.*/
	void MoveAllToLimitParallel(bool timedEqualy);

	/*Bewegt alle Motoren nacheinander zur Nullstellung. Der Einfuegeindex bestimmt dabei die Reihenfolge.*/
	void MoveAllTo0Serial();
	/*Bewegt alle Motoren nacheinander zut Endstellung. Der Einfuegeindex bestimmt dabei die Reihenfolge.*/
	void MoveAllToLimitSerial();

	/*Stopps all Movement.*/
	void StopMovement();

private:
	vector<LimitedStepperMotor> motors;
	int motorCount=0;
	int arraySize =2;
};

#endif /* CONTROLLER_MULTILIMTEDSTEPPERCONTROLLER_H_ */
