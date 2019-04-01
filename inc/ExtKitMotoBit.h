/// Yotta module microbit-dal-ext-kit
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

#include "ExtKitComponent.h"

namespace microbit_dal_ext_kit {

/// MotoBit Component
/**
	Support for SparkFun's moto:bit board.
	@reference	SparkFun moto:bit
		- https://www.sparkfun.com/products/14213
		- https://learn.sparkfun.com/tutorials/microbot-kit-experiment-guide/about-the-motobit-board
*/
class MotoBit : public Component
{
public:
	enum MotorDirection {
		kForward,
		kBackward
	};

	/// Inherited
	static /* Component */ Features avaiableFeatures();

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	MotoBit();

	/// Set motor speed
	void setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR);

protected:
	/// Inherited
	/* Component */ void doStart();

	/// Inherited
	/* Component */ void doStop();

private:
	enum Motor {
		kLeft,
		kRight
	};

	static int setMotorPower(bool power);	// returns MICROBIT_I2C_ERROR or MICROBIT_OK

	int setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent);	// returns MICROBIT_I2C_ERROR or MICROBIT_OK
	int setMotorPolarity(Motor motor, bool invert);	// returns MICROBIT_I2C_ERROR or MICROBIT_OK

	bool mInverted;

};	// MotoBit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTO_BIT_H
