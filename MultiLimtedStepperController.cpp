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

	//Stellt sicher, dass das array groß genug ist
	if (motorCount + 1 > arraySize) {
		LimitedStepperMotor newArray[arraySize * 2];
		for (int i = 0; i < arraySize; i++) {
			newArray[i] = motors[i];
		}
		arraySize *= 2;
		motors = newArray;
	}

	//Macht Platz zum Einfügen.
	for (int i = arraySize - 1; i > index; i--) {
		motors[i] = motors[i - 1];
	}

	//Einfügen
	motors[index] = motor;
	motorCount++;
}

void MultiLimtedStepperController::RemoveMotor(int index) {
	for (int i = index; i < arraySize - 1; i++) {
		motors[i] = motors[i + 1];
	}
	motors[motorCount - 1] = null;
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
