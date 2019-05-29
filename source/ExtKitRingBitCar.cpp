/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// RingBitCar component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitRingBitCar.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	RingBitCar
	@reference	Tinkertanker pxt-ringbitcar ringbitcar.ts (MIT license)
		- https://makecode.microbit.org/pkg/tinkertanker/pxt-ringbitcar
		- https://github.com/Tinkertanker/pxt-ringbitcar
		- https://github.com/Tinkertanker/pxt-ringbitcar/blob/master/ringbitcar.ts
*/

// range: 600 ... 1400, 1500, 1600 ... 2400
static const int kCenter = 1500;	// microseconds
static const int kOffset = 100;		// microseconds
static const int kRatio = 8;		// microseconds

RingBitCar::RingBitCar(const char* name, MicroBitPin& servoL, MicroBitPin& servoR)
	: MotorsLR(name)
	, mServoL(servoL)
	, mServoR(servoR)
{
}

/* MotorsLR */ void RingBitCar::doHandleComponentAction(Action action)
{
	if(action == kStart)
	{
		setMotorSpeed(kForward, kForward, 0, 0);
	}
	else if(action == kStop)
	{
		setMotorSpeed(kForward, kForward, 0, 0);
	}

	MotorsLR::doHandleComponentAction(action);
}

/* MotorsLR */ void RingBitCar::setMotorSpeed(RingBitCar::MotorDirection directionL, RingBitCar::MotorDirection directionR, int speedInPercentL, int speedInPercentR)
{
	setMotorSpeed(kLeft, directionL, speedInPercentL);
	setMotorSpeed(kRight, directionR, speedInPercentR);
}

void RingBitCar::setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent)
{
	int speed = kOffset + kRatio * speedInPercent;
	if(motor == kLeft) {
		mServoL.setServoPulseUs(kCenter + (direction == kForward) ? speed : - speed);
	}
	else {
		mServoR.setServoPulseUs(kCenter + (direction == kForward) ? - speed : speed);
	}
}

}	// microbit_dal_ext_kit
