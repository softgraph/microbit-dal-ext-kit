/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// ExtKit Generic Header - A handy header file to include all microbit-dal-ext-kit interfaces
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

/**	@page	ExtKit_Headers	Header files of microbit-dal-ext-kit
	The interfaces of `microbit-dal-ext-kit` are provided by the following header files.

	# Device class
		- ExtKitDevice.h
		.
	# Global variables
		- ExtKitGlobal.h
		.
	# Components
		- Components dedicated to extensiton boards or hardware modules
			- ExtKitBuzzer.h <br>
				Generic Buzzer
			- ExtKitJoystickBit.h <br>
				ElecFreaks' Joystick:bit
			- ExtKitMotoBit.h <br>
				SparkFun's moto:bit
			- ExtKitNeoPixel.h <br>
				Generic NeoPixel (WS2812B) LED strip
			- ExtKitSonar.h <br>
				Generic Sonar module (HC-SR04)
			- ExtKitTouchPiano.h <br>
				Waveshare's Mini Piano Module
			- ExtKitZipHalo.h <br>
				Kitronik's Zip Halo
			.
		- Generic components
			- ExtKitComponent.h <br>
				the base class
			- ExtKitPeriodicObserver.h
			- ExtKitRemoteState.h <br>
				Transmitter and Receiver
			- ExtKitSerialDebugger.h
			.
		.
	# Utilities
		- ExtKitAppMode.h
		- ExtKitAssert.h
		- ExtKitButton.h
		- ExtKitColor.h
		- ExtKitDebug.h
		- ExtKitDirection.h
		- ExtKitDisplay.h
		- ExtKitError.h
		- ExtKitFeature.h
		- ExtKitGesture.h
		- ExtKitImage.h
		- ExtKitNode.h
		- ExtKitNumeric.h
		- ExtKitOctave.h
		- ExtKitPianoKey.h
		- ExtKitRadio.h
		- ExtKitSerial.h
		- ExtKitState.h
		- ExtKitStatistics.h
		- ExtKitString.h
		- ExtKitTime.h
		.
	# Others
		- ExtKit_Common.h
		- ExtKit_Config.h
		- ExtKit.h
		.
*/

#ifndef EXT_KIT_H
#define EXT_KIT_H

// MicroBit and other classes

#include "MicroBit.h"

// Include this first

#include "ExtKit_Common.h"

// Include these as you like

#include "ExtKitAppMode.h"
#include "ExtKitAssert.h"
#include "ExtKitButton.h"
#include "ExtKitBuzzer.h"
#include "ExtKitColor.h"
#include "ExtKitComponent.h"
#include "ExtKitDebug.h"
#include "ExtKitDevice.h"
#include "ExtKitDirection.h"
#include "ExtKitDisplay.h"
#include "ExtKitError.h"
#include "ExtKitFeature.h"
#include "ExtKitGesture.h"
#include "ExtKitGlobal.h"
#include "ExtKitImage.h"
#include "ExtKitJoystickBit.h"
#include "ExtKitMotoBit.h"
#include "ExtKitNeoPixel.h"
#include "ExtKitNode.h"
#include "ExtKitNumeric.h"
#include "ExtKitOctave.h"
#include "ExtKitPeriodicObserver.h"
#include "ExtKitPianoKey.h"
#include "ExtKitRadio.h"
#include "ExtKitSerial.h"
#include "ExtKitSerialDebugger.h"
#include "ExtKitSonar.h"
#include "ExtKitState.h"
#include "ExtKitStatistics.h"
#include "ExtKitString.h"
#include "ExtKitTime.h"
#include "ExtKitTouchPiano.h"
#include "ExtKitZipHalo.h"

#endif	// EXT_KIT_H
