/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Device utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DEVICE_H
#define EXT_KIT_DEVICE_H

#include "MicroBit.h"
#include "ExtKit_Common.h"
#include "ExtKitGlobal.h"

namespace microbit_dal_ext_kit {

class MicroBitExtKit : public MicroBit
{
public:
	/// Constructor
	MicroBitExtKit();

	/// Inherited
	/* MicroBit */ void init();

protected:
	ExtKit	mExtKit;

};	// MicroBitExtKit

class PrimitiveExtKitIO
{
public:
	/// Constructor
	PrimitiveExtKitIO(const int id[3], const PinName name[3], const PinCapability capability[3]);

	/// The same as class `MicroBit`
	MicroBitPin		pin[0];

	/// The same as class `MicroBit`
	MicroBitPin		P0;

	/// The same as class `MicroBit`
	MicroBitPin		P1;

	/// The same as class `MicroBit`
	MicroBitPin		P2;

};	// PrimitiveExtKitIO

class PrimitiveExtKit
{
public:
	/// Constructor
	PrimitiveExtKit();

	/// Initialize
	void init();

	/// The same as class `MicroBit`
	MicroBitSerial			serial;

	/// The same as class `MicroBit`
	mbed::InterruptIn		resetButton;

	/// The same as class `MicroBit`
	MicroBitI2C				i2c;

	/// The same as class `MicroBit`
	MicroBitMessageBus		messageBus;

	/// The same as class `MicroBit`
	MicroBitDisplay			display;

	/// The same as class `MicroBit`
	MicroBitButton			buttonA;

	/// The same as class `MicroBit`
	MicroBitButton			buttonB;

	/// The same as class `MicroBit`
	MicroBitMultiButton		buttonAB;

	/// I/O
	PrimitiveExtKitIO		io;

protected:
	ExtKit	mExtKit;

	/// The same as class `MicroBit`
	uint8_t	status;

private:
	void handleMessageBusListenerAdded(MicroBitEvent evt);

};	// PrimitiveExtKit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DEVICE_H
