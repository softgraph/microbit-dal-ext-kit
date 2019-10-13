/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotorsLR component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_MOTORS_LR_H
#define EXT_KIT_MOTORS_LR_H

#include "ExtKitComponent.h"

namespace microbit_dal_ext_kit {

/// An abstract ext-kit Component which provides left and right motors
/* abstract */ class MotorsLR : public Component
{
public:
	/// Motor Direction
	enum MotorDirection {
		kBrake,		// `speedInPercent` shold be 0
		kForward,	// `speedInPercent` shold be between 0 and 100
		kBackward	// `speedInPercent` shold be between 0 and 100
	};

	/// Constructor
	MotorsLR(const char* name);

	/// Set Motor Speed
	virtual /* MotorsLR */ void setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR);

protected:
	/// Motor
	enum Motor {
		kLeft,
		kRight
	};

	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

	/// Set Motor Speed
	virtual /* MotorsLR */ int /* ErrorCode */ setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent) = 0;

};	// MotorsLR

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTORS_LR_H
