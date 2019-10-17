/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotorsLR component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitMotorsLR.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	MotorsLR
*/

MotorsLR::MotorsLR(const char* name)
	: Motors(name, kMotorCount)
{
}

/* Motors */ void MotorsLR::configureMotors()
{
	configureSpeedMotor(kLeft);
	configureSpeedMotor(kRight);
}

/* MotorsLR */ void MotorsLR::setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR)
{
	updateMotorSpeed(kLeft, directionL, speedInPercentL);
	updateMotorSpeed(kRight, directionR, speedInPercentR);
}

}	// microbit_dal_ext_kit
