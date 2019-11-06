/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotorsPT component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitMotorsPT.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	MotorsPT
*/

MotorsPT::MotorsPT(const char* name)
	: Motors(name, kMotorCount)
{
}

/* Motors */ void MotorsPT::configureMotors()
{
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "MotorsPT::configureMotors");
	configureAngleMotor(kPan);
	configureAngleMotor(kTilt);
}

}	// microbit_dal_ext_kit
