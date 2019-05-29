/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// RingBitCar component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_MOTO_BIT_H
#define EXT_KIT_MOTO_BIT_H

#include "ExtKitMotorsLR.h"

class MicroBitPin;

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for ElecFreaks' ring:bit car (v2) board
/**
	@reference	ElecFreaks ring:bit car (v2) for micro:bit
		- https://www.elecfreaks.com/estore/elecfreaks-ring-bit-car-v2-for-micro-bit-without-micro-bit.html
*/
class RingBitCar : public MotorsLR
{
public:
	/// Constructor
	RingBitCar(const char* name, MicroBitPin& servoLeft, MicroBitPin& servoRight);

	/// Inherited
	/* MotorsLR */ void setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR);

protected:
	/// Inherited
	/* MotorsLR */ void doHandleComponentAction(Action action);

private:
	/// Motor Side
	enum Motor {
		kLeft,
		kRight
	};

	/// Set Motor Speed
	void setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent);

	/// Servo Left
	MicroBitPin&	mServoL;

	/// Servo Right
	MicroBitPin&	mServoR;

};	// MotoBit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTO_BIT_H
