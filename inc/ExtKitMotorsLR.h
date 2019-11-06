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

#include "ExtKitMotors.h"

namespace microbit_dal_ext_kit {

/// an abstract ext-kit Component which provides two speed motors for left and right
/* abstract */ class MotorsLR : public Motors
{
public:
	/// left motor
	static const Motor kLeft = 0;

	/// right motor
	static const Motor kRight = 1;

	/// motor count
	static const int kMotorCount = 2;

	/// <obsoleted> set motor speed
	/** remained for backward compatibility before v1.2 */
	virtual /* MotorsLR */ void setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR);

protected:
	/// constructor
	MotorsLR(const char* name, int scaleInPercent = 100);

	/// inherited
	/* Motors */ void configureMotors();

	/// scale in percent
	int mScaleInPercent;

};	// MotorsLR

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTORS_LR_H
