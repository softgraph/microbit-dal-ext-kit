/// Yotta module microbit-dal-ext-kit
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

/// Features
typedef uint32_t	Features;

/// Feature utility
namespace feature {

/// Radio
const Features kRadio			= (1 << 0);

/// Remote Event Tx (Transmitter) using radio
const Features kRemoteEventTx	= (1 << 1) | kRadio;

/// Remote Event Rx (Receiver) using radio
const Features kRemoteEventRx	= (1 << 2) | kRadio;

/// Remote State Tx (Transmitter) using radio
const Features kRemoteStateTx	= (1 << 3) | kRadio;

/// Remote State Rx (Receiver) using radio
const Features kRemoteStateRx	= (1 << 4) | kRadio;

/// Remote Tx (Transmitter) using radio
const Features kRemoteTx			= kRemoteEventTx | kRemoteStateTx;

/// Remote Rx (Receiver) using radio
const Features kRemoteRX			= kRemoteEventRx | kRemoteStateRx;

/// The device is mounted upside down. micro:bit's button A is on the right.
const Features kInverted			= (1 << 5);

/// NexPixel modules are connected to the device
const Features kNeoPixel			= (1 << 6);

/// Buzzer module is connected to the device
const Features kBuzzer			= (1 << 7);

/// Sonar module is connected to the device
const Features kSonar			= (1 << 8);

/// Auto detection for the extension board is not available
const Features kNoAutoDetection	= (1 << 9);

/// No extension board is connected to the device
const Features kMicroBitOnly		= (1 << 10);

/// ElecFreaks' Joystick:bit board is connected to the device.
const Features kJoystickBit		= (1 << 11);

/// SparkFun's moto:bit board is connected to the device.
const Features kMotoBit			= (1 << 12);

/// Waveshare's Mini Piano Module is connected to the device.
const Features kTouchPiano		= (1 << 13);

/// Kitronik's Zip Halo board is connected to the device.
const Features kZipHalo			= (1 << 14);

/// Set the feature as configured
void setConfigured(Features features);

/// Check whether the feature is configured
bool isConfigured(Features features);

/// Configured features
Features configured();

}	// features
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_FEATURE_H
