/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
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

/**	@page	ExtKit_Device	Device class - the first instance for using microbit-dal-ext-kit
	- An instance of either class MicroBitExtKit or PrimitiveExtKit must be created first for using microbit-dal-ext-kit.
	- The instance should not be created in stack memory (like local variables) - either in your main method or anywhere else. <br>
		This restriction is the same as the warning below for micro:bit runtime.
			<blockquote>
			<b>Warning</b> <br>
			micro:bit runtime components should <b>always</b> be brought up as global variables. They should <b>not</b> be created as local variables - either in your main method or anywhere else. The reason for this is the the runtime is a multi-threaded environment, and any variables created in stack memory (like local variables) may be paged out by the scheduler, and result in instability if they utilise interrupts or are accessed by other threads. So... don't do it!
			</blockquote>

		@reference
			- <a href="https://lancaster-university.github.io/microbit-docs/advanced/#using-components-directly"><b>Using Components Directly</b> (lancaster-university.github.io)</a>

	- Two or more instances are not allowed.
	- You can choose one of the following classes
		- MicroBitExtKit is derived from microbit-dal's class MicroBit. You can use all features of class MicroBit via the instance of MicroBitExtKit.
		- PrimitiveExtKit is a minimal version of MicroBitExtKit. You can choose this if you don't want to instanciate the class MicroBit. <br>
			Only the following instances are included in PrimitiveExtKit.
			- mbed::InterruptIn for the reset button
			- MicroBitSerial for the serial port over USB
			- MicroBitI2C
			- MicroBitMessageBus
			- MicroBitDisplay
			- MicroBitButton for button A and B
			- MicroBitMultiButton for button A+B
			- MicroBitPin for all pins supported by MicroBitIO
			.
			If you need another instance which depends on the instances listed here, inherit PrimitiveExtKit and add the required class as a member variable. This approach ensures that the initialization of the instances listed here are done by the constructor of PrimitiveExtKit before the initialization of your member variables.
*/

/// The common interface for any ext-kit Device
/**	Any class inherits this interface should also expose the following member variables.

		public:
			MicroBitSerial			serial;
			mbed::InterruptIn		resetButton;
			MicroBitI2C				i2c;
			MicroBitMessageBus		messageBus;
			MicroBitDisplay			display;
			MicroBitButton			buttonA;
			MicroBitButton			buttonB;
			MicroBitMultiButton		buttonAB;
			MicroBitIO				io;
*/
/* abstract */ class Device
{
	/// Initialize the device
	/* to be implemented */ void init();
};

/// An ext-kit Device derived from MicroBit
class MicroBitExtKit : public MicroBit, public Device
{
public:
	/// Constructor
	MicroBitExtKit();

	/// Inherited
	/* MicroBit and Device */ void init();

protected:
	/// Ext Kit global instance
	ExtKit	mExtKit;

};	// MicroBitExtKit

/// A minimal ext-kit Device
class PrimitiveExtKit : public Device
{
public:
	/// Constructor
	PrimitiveExtKit();

	/// Initialize
	void init();

	/// The same name as class MicroBit
	MicroBitSerial			serial;

	/// The same name as class MicroBit
	mbed::InterruptIn		resetButton;

	/// The same name as class MicroBit
	MicroBitI2C				i2c;

	/// The same name as class MicroBit
	MicroBitMessageBus		messageBus;

	/// The same name as class MicroBit
	MicroBitDisplay			display;

	/// The same name as class MicroBit
	MicroBitButton			buttonA;

	/// The same name as class MicroBit
	MicroBitButton			buttonB;

	/// The same name as class MicroBit
	MicroBitMultiButton		buttonAB;

	/// The same name as class MicroBit
	MicroBitIO				io;

protected:
	/// Ext Kit global instance
	ExtKit	mExtKit;

	/// The same name as class MicroBit
	uint8_t	status;

private:
	void handleMessageBusListenerAdded(MicroBitEvent evt);

};	// PrimitiveExtKit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DEVICE_H
