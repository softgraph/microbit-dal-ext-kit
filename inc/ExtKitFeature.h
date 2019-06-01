/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Feature utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_FEATURE_H
#define EXT_KIT_FEATURE_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Features. The constants for type `#Features` are defined in namespace `microbit_dal_ext_kit.feature`.
typedef uint32_t	Features;

/// Feature utility
namespace feature {

/// Auto detection for the extension board is not available.
const Features kNoAutoDetection	= (1 << 0);

/// The device is mounted upside down. micro:bit's button A is on the right.
const Features kInverted		= (1 << 1);

//								= (1 << 2);

/// Remote State Transmitter is supported.
const Features kRemoteStateTx	= (1 << 3);

/// Remote State Receiver is supported.
const Features kRemoteStateRx	= (1 << 4);

//								= (1 << 5);

/// Generic NeoPixel strip module is equipped optionally.
const Features kNeoPixel		= (1 << 6);

/// Generic buzzer module is equipped optionally.
const Features kBuzzer			= (1 << 7);

/// Generic sonar module is equipped optionally.
const Features kSonar			= (1 << 8);

/// Generic Servo Motors for L and R are equipped optionally.
const Features kServoMotorsLR	= (1 << 9);

//								= (1 << 10);

/// ElecFreaks' Joystick:bit board is connected.
const Features kJoystickBit		= (1 << 11);

/// SparkFun's moto:bit board is connected.
const Features kMotoBit			= (1 << 12);

/// Waveshare's Mini Piano Module for micro:bit also known as TouchPiano board is connected.
const Features kTouchPiano		= (1 << 13);

/// Kitronik's Zip Halo board is connected.
const Features kZipHalo			= (1 << 14);

//								= (1 << 15);
//								= (1 << 16);
//								= (1 << 17);
//								= (1 << 18);
//								= (1 << 19);
//								= (1 << 20);
//								= (1 << 21);
//								= (1 << 22);
//								= (1 << 23);

/// Reserved for App #7.
const Features kReservedForApp7	= (1 << 24);

/// Reserved for App #6.
const Features kReservedForApp6	= (1 << 25);

/// Reserved for App #5.
const Features kReservedForApp5	= (1 << 26);

/// Reserved for App #4.
const Features kReservedForApp4	= (1 << 27);

/// Reserved for App #3.
const Features kReservedForApp3	= (1 << 28);

/// Reserved for App #2.
const Features kReservedForApp2	= (1 << 29);

/// Reserved for App #1.
const Features kReservedForApp1	= (1 << 30);

/// Reserved for App #0.
const Features kReservedForApp0	= (1 << 31);

/// Reset configured features
void resetConfigured();

/// Set the feature as configured
void setConfigured(Features features);

/// Check whether the feature is configured
bool isConfigured(Features features);

/// Configured features
Features configured();

}	// features
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_FEATURE_H
