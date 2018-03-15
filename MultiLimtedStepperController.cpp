#include "libraries/StandardCplusplus/StandardCplusplus.h"

/*
 * MultiLimtedStepperController.cpp
 *
 *  Created on: 15.03.2018
 *      Author: Lion
 */

#include "MultiLimtedStepperController.h"

MultiLimtedStepperController::MultiLimtedStepperController() {
  
}

void MultiLimtedStepperController::AddMotor(int index,
		LimitedStepperMotor motor) {
	if (index < 0 || index >= arraySize)
		return;

	
	//Einf�gen
	motors[index] = motor;
	motorCount++;
}

void MultiLimtedStepperController::RemoveMotor(int index) {
	
	motorCount--;
}

void MultiLimtedStepperController::StopMovement() {
	for (int i = 0; i < motorCount; i++) {
		motors[i].stopMovement();
	}
}

void MultiLimtedStepperController::MoveTo0(int index) {
	if (index < 0 || index >= motorCount)
		return;
	motors[index].moveToZero();
}

void MultiLimtedStepperController::MoveToLimit(int index) {
	if (index < 0 || index >= motorCount)
		return;
	motors[index].moveToLimit();
}

void MultiLimtedStepperController::MoveAllTo0Serial() {
	for (int i = 0; i < motorCount; ++i) {
		if (!motors[i].moveToZero())
			break;
	}
}

void MultiLimtedStepperController::MoveAllToLimitSerial() {
	for (int i = 0; i < motorCount; ++i) {
		if (!motors[i].moveToLimit())
			break;
	}
}

void MultiLimtedStepperController::MoveAllTo0Parallel(bool timed) {
	if (timed) {
		for (double i = 1000; i <= 0; i--) {
			for (int j = 0; j < motorCount; j++) {
				LimitedStepperMotor motor = motors[j];

				unsigned int targetSteps = motor.Limit * i / 1000;
				if (targetSteps < motor.CurrentSteps
						&& !motor.moveToPosition(targetSteps)) {
					return;
				}

			}
		}
	} else {
		bool needsChange = false;
		do {
			for (int j = 0; j < motorCount; j++) {
				LimitedStepperMotor motor = motors[j];
				if (!motors[j].step(-1))
					return;
				needsChange |= motor.CurrentSteps != 0;
			}
		} while (needsChange);
	}
}

void MultiLimtedStepperController::MoveAllToLimitParallel(bool timed) {

	if (timed) {
		for (double i = 0; i <= 1000; i++) {
			for (int j = 0; j < motorCount; j++) {
				LimitedStepperMotor motor = motors[j];

				unsigned int targetSteps = motor.Limit * i / 1000;
				if (targetSteps > motor.CurrentSteps
						&& !motor.moveToPosition(targetSteps)) {
					return;
				}

			}
		}
	} else {
		bool needsChange = false;
		do {
			for (int j = 0; j < motorCount; j++) {
				LimitedStepperMotor motor = motors[j];
				if (!motors[j].step(1))
					return;
				needsChange |= motor.CurrentSteps != motor.Limit;
			}
		} while (needsChange);
	}
}
