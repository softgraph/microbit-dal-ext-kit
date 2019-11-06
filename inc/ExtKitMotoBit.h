/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotoBit component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_MOTO_BIT_H
#define EXT_KIT_MOTO_BIT_H

#include "ExtKitMotorsLR.h"

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for SparkFun's moto:bit board
/**
	@reference	SparkFun moto:bit
		- https://www.sparkfun.com/products/14213
		- https://learn.sparkfun.com/tutorials/microbot-kit-experiment-guide/about-the-motobit-board
*/
class MotoBit : public MotorsLR
{
public:
	/// Check that the required hardware is avaialable.
	static bool isAvaiable();

	/// Constructor
	MotoBit(bool inverted);

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

	/// Inherited
	/* Motors */ int /* ErrorCode */ setMotorPower(bool power);

	/// Inherited
	/* Motors */ int /* ErrorCode */ setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent);

	/// Check Motor Power
	static int /* ErrorCode */ checkMotorPower(bool power);

	/// Set Motor Polarity
	int /* ErrorCode */ setMotorPolarity(Motor motor, bool invert);

	/// Inverted
	bool mInverted;

};	// MotoBit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTO_BIT_H
