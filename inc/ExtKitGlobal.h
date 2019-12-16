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
#include "MicroBitIO.h"
#include "ExtKit_Common.h"

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
	ExtKit::global() provides the access to the instances of microbit-dal's MicroBit* classes owned by or registered to MicroBitExtKit or PrimitiveExtKit. <br>
	Here is an example for using ExtKit::global().
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
		const char*				owner,			// owner name
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
	);

	/// Destructor
	~ExtKit();

	/// Initialize
	void init();

	/// Get Owner Name
	inline const char* owner() {
		return mOwner;
	}

	/// Get Button A Object
	inline MicroBitButton& buttonA() {
		return mButtonA;
	}

	/// Get Button B Object
	inline MicroBitButton& buttonB() {
		return mButtonB;
	}

	/// Get Multi Button A + B Object
	inline MicroBitMultiButton& buttonAB() {
		return mButtonAB;
	}

	/// Get Display Object
	inline MicroBitDisplay& display() {
		return mDisplay;
	}

	/// Get I2C Object
	inline MicroBitI2C& i2c() {
		return mI2c;
	}

	/// Get Message Bus Object
	inline MicroBitMessageBus& messageBus() {
		return mMessageBus;
	}

	/// Get IO Object
	inline MicroBitIO& io() {
		return mIO;
	}

	/// Get Port P0 Object
	inline MicroBitPin& p0() {
		return mIO.P0;
	}

	/// Get Port P1 Object
	inline MicroBitPin& p1() {
		return mIO.P1;
	}

	/// Get Port P2 Object
	inline MicroBitPin& p2() {
		return mIO.P2;
	}

	/// Get Reset Button Object
	inline mbed::InterruptIn& resetButton() {
		return mResetButton;
	}

	/// Get Serial Object
	inline MicroBitSerial& serial() {
		return mSerial;
	}

	/// Get Accelerometer Object (may null)
	inline MicroBitAccelerometer* accelerometer() {
		return mAccelerometer;
	}

	/// Get Compass Object (may null)
	inline MicroBitCompass* compass() {
		return mCompass;
	}

	/// Get Radio Object (may null)
	inline MicroBitRadio* radio() {
		return mRadio;
	}

	/// Get Thermometer Object (may null)
	inline MicroBitThermometer* thermometer() {
		return mThermometer;
	}

	/// Register Accelerometer Object
	inline void registerAccelerometer(MicroBitAccelerometer& accelerometer) {
		mAccelerometer = &accelerometer;
	}

	/// Register Compass Object
	inline void registerCompass(MicroBitCompass& compass) {
		mCompass = &compass;
	}

	/// Register Radio Object
	inline void registerRadio(MicroBitRadio& radio) {
		mRadio = &radio;
	}

	/// Register Thermometer Object
	inline void registerThermometer(MicroBitThermometer& thermometer) {
		mThermometer = &thermometer;
	}

private:
	/// Global instance
	static ExtKit*			sGlobal;

	/// Owner Name
	const char*				mOwner;

	MicroBitButton&			mButtonA;
	MicroBitButton&			mButtonB;
	MicroBitMultiButton&	mButtonAB;
	MicroBitDisplay&		mDisplay;
	MicroBitI2C&			mI2c;
	MicroBitMessageBus&		mMessageBus;
	MicroBitIO&				mIO;
	mbed::InterruptIn&		mResetButton;
	MicroBitSerial&			mSerial;

	MicroBitAccelerometer*	mAccelerometer;	// may null
	MicroBitCompass*		mCompass;		// may null
	MicroBitRadio*			mRadio;			// may null
	MicroBitThermometer*	mThermometer;	// may null

};	// ExtKit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GLOBAL_H
