/*
 * MultiLimtedStepperController.cpp
 *
 *  Created on: 15.03.2018
 *      Author: Lion
 */

#include "MultiLimtedStepperController.h"

MultiLimtedStepperController::MultiLimtedStepperController() {

}

void MultiLimtedStepperController::AddMotor(LimitedStepperMotor motor) {
	motors.push_back(motor);
}

void MultiLimtedStepperController::Clear() {
	motors.clear();
}

void MultiLimtedStepperController::StopMovement() {
	for (int i = 0; i < motors.size(); i++) {
		motors.at(i).stopMovement();
	}
}

void MultiLimtedStepperController::MoveTo0(int index) {
	motors.at(index).moveToZero();
}

void MultiLimtedStepperController::MoveToLimit(int index) {
	motors.at(index).moveToLimit();
}

void MultiLimtedStepperController::MoveAllTo0Serial() {
	for (int i = 0; i < motors.size(); ++i) {
		if (!motors.at(i).moveToZero())
			break;
	}
}

void MultiLimtedStepperController::MoveAllToLimitSerial() {
	for (int i = 0; i < motors.size(); ++i) {
		if (!motors.at(i).moveToLimit())
			break;
	}
}

void MultiLimtedStepperController::MoveAllTo0Parallel(bool timed) {
	if (timed) {
		for (double i = 1000; i <= 0; i--) {
			for (int j = 0; j < motors.size(); j++) {
				LimitedStepperMotor motor = motors.at(j);

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
			for (int j = 0; j < motors.size(); j++) {
				LimitedStepperMotor motor = motors.at(j);
				if (!motor.step(-1))
					return;
				needsChange |= motor.CurrentSteps != 0;
			}
		} while (needsChange);
	}
}

void MultiLimtedStepperController::MoveAllToLimitParallel(bool timed) {

	if (timed) {
		for (double i = 0; i <= 1000; i++) {
			for (int j = 0; j < motors.size(); j++) {
				LimitedStepperMotor motor = motors.at(j);

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
			for (int j = 0; j < motors.size(); j++) {
				LimitedStepperMotor motor = motors.at(j);
				if (!motor.step(1))
					return;
				needsChange |= motor.CurrentSteps != motor.Limit;
			}
		} while (needsChange);
	}
}
