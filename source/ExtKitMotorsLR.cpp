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
	: Component(name)
{
}

/* MotorsLR */ void MotorsLR::setMotorSpeed(MotorsLR::MotorDirection directionL, MotorsLR::MotorDirection directionR, int speedInPercentL, int speedInPercentR)
{
	/* virtual */ setMotorSpeed(kLeft, directionL, speedInPercentL);
	/* virtual */ setMotorSpeed(kRight, directionR, speedInPercentR);
}

/* Component */ void MotorsLR::doHandleComponentAction(Action action)
{
	if(action == kStart)
	{
		/* virtual */ setMotorSpeed(kBrake, kBrake, 0, 0);
	}
	else if(action == kStop)
	{
		/* virtual */ setMotorSpeed(kBrake, kBrake, 0, 0);
	}

	/* super */ Component::doHandleComponentAction(action);
}

}	// microbit_dal_ext_kit
