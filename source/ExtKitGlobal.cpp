/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Global variables.
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitGlobal.h"	// self
#include "ExtKit_System.h"

#if EXT_KIT_CONFIG_ENABLED(GLOBAL_UBIT)

/*
	Global variable for MicroBit class.
*/

MicroBit	uBit;

#endif	// GLOBAL_UBIT

/*
	Global aliases.
*/

namespace microbit_dal_ext_kit {

#if EXT_KIT_CONFIG_ENABLED(GLOBAL_UBIT)

MicroBitButton&			gButtonA		= uBit.buttonA;
MicroBitButton&			gButtonB		= uBit.buttonB;
MicroBitDisplay&		gDisplay		= uBit.display;
MicroBitI2C&			gI2c			= uBit.i2c;
MicroBitMessageBus&		gMessageBus		= uBit.messageBus;
MicroBitPin&			gP0				= uBit.io.P0;
MicroBitPin&			gP1				= uBit.io.P1;
MicroBitPin&			gP2				= uBit.io.P2;
MicroBitRadio&			gRadio			= uBit.radio;
MicroBitSerial&			gSerial			= uBit.serial;

MicroBitAccelerometer*	gAccelerometer	= &uBit.accelerometer;
MicroBitMultiButton*	gButtonAB		= &uBit.buttonAB;
MicroBitCompass*		gCompass		= &uBit.compass;
MicroBitThermometer*	gThermometer	= &uBit.thermometer;

#else	// GLOBAL_UBIT

static MicroBitButton		sButtonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
static MicroBitButton		sButtonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);
static MicroBitDisplay		sDisplay;
static MicroBitI2C			sI2c(I2C_SDA0, I2C_SCL0);
static MicroBitMessageBus	sMessageBus;
static MicroBitPin			sP0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
static MicroBitPin			sP1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL);
static MicroBitPin			sP2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL);
static MicroBitRadio		sRadio;
static MicroBitSerial		sSerial(USBTX, USBRX);

MicroBitButton&			gButtonA		= sButtonA;
MicroBitButton&			gButtonB		= sButtonB;
MicroBitDisplay&		gDisplay		= sDisplay;
MicroBitI2C&			gI2c			= sI2c;
MicroBitMessageBus&		gMessageBus		= sMessageBus;
MicroBitPin&			gP0				= sP0;
MicroBitPin&			gP1				= sP1;
MicroBitPin&			gP2				= sP2;
MicroBitRadio&			gRadio			= sRadio;
MicroBitSerial&			gSerial			= sSerial;

MicroBitAccelerometer*	gAccelerometer	= 0;	// updated by device::prepareFor()
MicroBitMultiButton*	gButtonAB		= 0;	// updated by device::prepareFor()
MicroBitCompass*		gCompass		= 0;	// updated by device::prepareFor()
MicroBitThermometer*	gThermometer	= 0;	// updated by device::prepareFor()

#endif	// GLOBAL_UBIT

}	// microbit_dal_ext_kit
