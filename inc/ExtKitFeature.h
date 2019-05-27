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

/// Class `remoteState::Transmitter` is required.
const Features kRemoteStateTx	= (1 << 3);

/// Class `remoteState::Receiver` is required.
const Features kRemoteStateRx	= (1 << 4);

/// The device is mounted upside down. micro:bit's button A is on the right.
const Features kInverted		= (1 << 5);

/// Class `NeoPixel` is required.
const Features kNeoPixel		= (1 << 6);

/// Class `Buzzer` is required.
const Features kBuzzer			= (1 << 7);

/// Class `Sonar` is required.
const Features kSonar			= (1 << 8);

/// Auto detection for the extension board is not available
const Features kNoAutoDetection	= (1 << 9);

/// No extension board is connected to the device
const Features kMicroBitOnly	= (1 << 10);

/// Class `JoystickBit`
const Features kJoystickBit		= (1 << 11);

/// Class `MotoBit` is required.
const Features kMotoBit			= (1 << 12);

/// Class `TouchPiano` is required.
const Features kTouchPiano		= (1 << 13);

/// Class `ZipHalo` is required.
const Features kZipHalo			= (1 << 14);

/// Class `RingBitCar` is required.
const Features kRingBitCar		= (1 << 15);

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
