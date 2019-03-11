/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Global variables.
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

#if EXT_KIT_CONFIG_ENABLED(GLOBAL_UBIT)

extern MicroBit					uBit;

#endif	// GLOBAL_UBIT

namespace microbit_dal_ext_kit {

/*
	Global aliases.
*/

extern MicroBitButton&			gButtonA;
extern MicroBitButton&			gButtonB;
extern MicroBitDisplay&			gDisplay;
extern MicroBitI2C&				gI2c;
extern MicroBitMessageBus&		gMessageBus;
extern MicroBitPin&				gP0;
extern MicroBitPin&				gP1;
extern MicroBitPin&				gP2;
extern MicroBitRadio&			gRadio;
extern MicroBitSerial&			gSerial;

extern MicroBitAccelerometer*	gAccelerometer;	// may null
extern MicroBitMultiButton*		gButtonAB;		// may null
extern MicroBitCompass*			gCompass;		// may null
extern MicroBitThermometer*		gThermometer;	// may null

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GLOBAL_H
