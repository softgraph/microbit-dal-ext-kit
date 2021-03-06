/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Global variables
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitGlobal.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

ExtKit* ExtKit::sGlobal = 0;

ExtKit& ExtKit::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

ExtKit::ExtKit(
	const char*				owner,
	MicroBitButton&			buttonA,
	MicroBitButton&			buttonB,
	MicroBitMultiButton&	buttonAB,
	MicroBitDisplay&		display,
	MicroBitI2C&			i2c,
	MicroBitMessageBus&		messageBus,
	MicroBitIO&				io,
	mbed::InterruptIn&		resetButton,
	MicroBitSerial&			serial,
	MicroBitAccelerometer*	accelerometer,	// may null
	MicroBitCompass*		compass,		// may null
	MicroBitRadio*			radio,			// may null
	MicroBitThermometer*	thermometer		// may null
)
	: mOwner(owner)
	, mButtonA(buttonA)
	, mButtonB(buttonB)
	, mButtonAB(buttonAB)
	, mDisplay(display)
	, mI2c(i2c)
	, mMessageBus(messageBus)
	, mIO(io)
	, mResetButton(resetButton)
	, mSerial(serial)
	, mAccelerometer(accelerometer)
	, mCompass(compass)
	, mRadio(radio)
	, mThermometer(thermometer)
{
	EXT_KIT_ASSERT(owner);
}

ExtKit::~ExtKit()
{
	if(sGlobal == this) {
		sGlobal = 0;
	}
}

void ExtKit::init()
{
	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

}	// microbit_dal_ext_kit
