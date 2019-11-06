/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotorsPT component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_MOTORS_PT_H
#define EXT_KIT_MOTORS_PT_H

#include "ExtKitMotors.h"

namespace microbit_dal_ext_kit {

/// an abstract ext-kit Component which provides two angle motors for pan and tilt
/* abstract */ class MotorsPT : public Motors
{
public:
	/// pan motor
	static const Motor kPan = 0;

	/// tilt motor
	static const Motor kTilt = 1;

	/// motor count
	static const int kMotorCount = 2;

protected:
	/// constructor
	MotorsPT(const char* name);

	/// inherited
	/* Motors */ void configureMotors();

};	// MotorsPT

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTORS_PT_H
