/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotoBit component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitMotoBit.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	MotoBit
	@reference	sparkfun pxt-moto-bit motobit.ts (MIT license)
		- https://makecode.microbit.org/pkg/sparkfun/pxt-moto-bit
		- https://github.com/sparkfun/pxt-moto-bit
		- https://github.com/sparkfun/pxt-moto-bit/blob/master/motobit.ts
*/

// I2C Address: 0x59 (89)
static const int	kI2cAddress						= 0x59 << 1;

// I2C Command & Parameter for Motor Power: 0x7000 (28672) + 0/1
static const char	kI2cCmdSetMotorPower			= 0x70;
static const char	kI2cDataMotorPowerOff			= 0x00;
static const char	kI2cDataMotorPowerOn			= 0x01;

// I2C Command & Parameter for Motor Speed L: 0x2100 (8448) +/- N
// I2C Command & Parameter for Motor Speed R: 0x2000 (8192) +/- N
static const char	kI2cCmdSetMotorSpeedL			= 0x21;
static const char	kI2cCmdSetMotorSpeedR			= 0x20;

// I2C Command & Parameter for Motor Polarity L: 0x1300 (4864) + 0/1
// I2C Command & Parameter for Motor Polarity R: 0x1200 (4608) + 0/1
static const char	kI2cCmdSetMotorPolarityL		= 0x13;
static const char	kI2cCmdSetMotorPolarityR		= 0x12;
static const char	kI2cDataMotorPolarityNormal		= 0x00;
static const char	kI2cDataMotorPolarityInvert		= 0x01;

#define COUNT_OF(x)		((int) (sizeof(x) / sizeof(x[0])))	///< Count of table elements

bool MotoBit::isAvaiable()
{
	return (setMotorPower(false) == MICROBIT_OK);
}

MotoBit::MotoBit()
	: MotorsLR("MotoBit")
	, mInverted(false)
{
	mInverted = !feature::isConfigured(feature::kInverted);
}

/* Component */ void MotoBit::doHandleComponentAction(Action action)
{
	if(action == kStart)
	{
		setMotorPolarity(kLeft, mInverted);
		setMotorPolarity(kRight, mInverted);
	}

	/* super */ MotorsLR::doHandleComponentAction(action);
}

/* MotorsLR */ void MotoBit::setMotorSpeed(MotorDirection directionL, MotorDirection directionR, int speedInPercentL, int speedInPercentR)
{
	/* super */ MotorsLR::setMotorSpeed(directionL, directionR, speedInPercentL, speedInPercentR);

	bool power = (speedInPercentL || speedInPercentR);
	setMotorPower(power);
}

int MotoBit::setMotorPower(bool power)	// returns MICROBIT_I2C_ERROR or MICROBIT_OK
{
	char i2cData[2];
	i2cData[0] = kI2cCmdSetMotorPower;
	i2cData[1] = power ? kI2cDataMotorPowerOn : kI2cDataMotorPowerOff;
	return ExtKit::global().i2c().write(kI2cAddress, i2cData, COUNT_OF(i2cData));
}

/* MotorsLR */ int MotoBit::setMotorSpeed(MotoBit::Motor motor, MotoBit::MotorDirection direction, int speedInPercent)	// returns MICROBIT_I2C_ERROR or MICROBIT_OK
{
	speedInPercent = numeric::clamp(0, 100, speedInPercent);
	int speed = speedInPercent * 127 / 100;	// range: 0 - 127

	char i2cData[2];
	i2cData[0] = ((motor == kLeft) != mInverted) ? kI2cCmdSetMotorSpeedL: kI2cCmdSetMotorSpeedR;
	i2cData[1] = (direction == kForward) ?
		128 + speed /* range: 128 - 255 */ :
		127 - speed /* range: 127 - 0 */ ;
	return ExtKit::global().i2c().write(kI2cAddress, i2cData, COUNT_OF(i2cData));
}

int MotoBit::setMotorPolarity(MotoBit::Motor motor, bool invert)	// returns MICROBIT_I2C_ERROR or MICROBIT_OK
{
	char i2cData[2];
	i2cData[0] = ((motor == kLeft) != mInverted) ? kI2cCmdSetMotorPolarityL: kI2cCmdSetMotorPolarityR;
	i2cData[1] = invert ? kI2cDataMotorPolarityInvert : kI2cDataMotorPolarityNormal;
	return ExtKit::global().i2c().write(kI2cAddress, i2cData, COUNT_OF(i2cData));
}

}	// microbit_dal_ext_kit
