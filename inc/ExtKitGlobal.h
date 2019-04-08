/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Global variables
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_GLOBAL_H
#define EXT_KIT_GLOBAL_H

#include "MicroBitConfig.h"
#include "ExtKit_Common.h"

class MicroBit;
class MicroBitAccelerometer;
class MicroBitButton;
class MicroBitCompass;
class MicroBitDisplay;
class MicroBitI2C;
class MicroBitMessageBus;
class MicroBitMultiButton;
class MicroBitPin;
class MicroBitRadio;
class MicroBitSerial;
class MicroBitThermometer;

/*
	uBit global variable.
*/

namespace microbit_dal_ext_kit {

/**	@page	ExtKit_Global	Global instance - the access to the instances of microbit-dal's MicroBit* classes
	`ExtKit::global()` provides the access to the instances of microbit-dal's `MicroBit*` classes owned by or registered to `MicroBitExtKit` or `PrimitiveExtKit`. <br>
	Here is an example for using `ExtKit::global()`.
	@code
		MicroBitDisplay& d = ExtKit::global().display();
		d.print("Hello");
	@endcode
*/

/// Global instance
struct ExtKit
{
public:
	/// Get global instance. Valid only after MicroBitExtKit::init() or PrimitiveExtKit::init() is completed.
	static ExtKit& global();

	/// Constructor
	ExtKit(
		const char*				owner,
		MicroBitButton&			buttonA,
		MicroBitButton&			buttonB,
		MicroBitMultiButton&	buttonAB,
		MicroBitDisplay&		display,
		MicroBitI2C&			i2c,
		MicroBitMessageBus&		messageBus,
		MicroBitPin&			p0,
		MicroBitPin&			p1,
		MicroBitPin&			p2,
		mbed::InterruptIn&		resetButton,
		MicroBitSerial&			serial,
		MicroBitAccelerometer*	accelerometer,	// may null
		MicroBitCompass*		compass,		// may null
		MicroBitRadio*			radio,			// may null
		MicroBitThermometer*	thermometer		// may null
	);

	/// Destructor
	~ExtKit();

	/// Initialize
	void init();

	inline const char* owner() {
		return mOwner;
	}

	inline MicroBitButton& buttonA() {
		return mButtonA;
	}

	inline MicroBitButton& buttonB() {
		return mButtonB;
	}

	inline MicroBitMultiButton& buttonAB() {
		return mButtonAB;
	}

	inline MicroBitDisplay& display() {
		return mDisplay;
	}

	inline MicroBitI2C& i2c() {
		return mI2c;
	}

	inline MicroBitMessageBus& messageBus() {
		return mMessageBus;
	}

	inline MicroBitPin& p0() {
		return mP0;
	}

	inline MicroBitPin& p1() {
		return mP1;
	}

	inline MicroBitPin& p2() {
		return mP2;
	}

	inline mbed::InterruptIn& resetButton() {
		return mResetButton;
	}

	inline MicroBitSerial& serial() {
		return mSerial;
	}

	inline MicroBitAccelerometer* accelerometer() {	// may null
		return mAccelerometer;
	}

	inline MicroBitCompass* compass() {	// may null
		return mCompass;
	}

	inline MicroBitRadio* radio() {	// may null
		return mRadio;
	}

	inline MicroBitThermometer* thermometer() {	// may null
		return mThermometer;
	}

	inline void registerAccelerometer(MicroBitAccelerometer& accelerometer) {
		mAccelerometer = &accelerometer;
	}

	inline void registerCompass(MicroBitCompass& compass) {
		mCompass = &compass;
	}

	inline void registerRadio(MicroBitRadio& radio) {
		mRadio = &radio;
	}

	inline void registerThermometer(MicroBitThermometer& thermometer) {
		mThermometer = &thermometer;
	}

private:
	static ExtKit*			sGlobal;

	const char*				mOwner;

	MicroBitButton&			mButtonA;
	MicroBitButton&			mButtonB;
	MicroBitMultiButton&	mButtonAB;
	MicroBitDisplay&		mDisplay;
	MicroBitI2C&			mI2c;
	MicroBitMessageBus&		mMessageBus;
	MicroBitPin&			mP0;
	MicroBitPin&			mP1;
	MicroBitPin&			mP2;
	mbed::InterruptIn&		mResetButton;
	MicroBitSerial&			mSerial;

	MicroBitAccelerometer*	mAccelerometer;	// may null
	MicroBitCompass*		mCompass;		// may null
	MicroBitRadio*			mRadio;			// may null
	MicroBitThermometer*	mThermometer;	// may null

};	// ExtKit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GLOBAL_H
