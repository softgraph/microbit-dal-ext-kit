/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// ExtKit Generic Header - a handy header file to include all microbit-dal-ext-kit interfaces
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_H
#define EXT_KIT_H

namespace microbit_dal_ext_kit {

/**	@page	ExtKit_Headers	Header File Structure of microbit-dal-ext-kit
	The interfaces of `microbit-dal-ext-kit` are provided by the following header files.

	# Device Class
		See also @ref	ExtKit_Device.
		- ExtKitDevice.h

	# Global Instance
		See also @ref	ExtKit_Global.
		- ExtKitGlobal.h

	# Components
		See also @ref	ExtKit_Components.
		- ExtKitBuzzer.h
		- ExtKitJoystickBit.h
		- ExtKitMotoBit.h
		- ExtKitNeoPixel.h
		- ExtKitPeriodicObserver.h
		- ExtKitRemoteState.h
		- ExtKitSerialDebugger.h
		- ExtKitSonar.h
		- ExtKitTouchPiano.h
		- ExtKitZipHalo.h

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
		- ExtKitRequest.h
		- ExtKitSerial.h
		- ExtKitState.h
		- ExtKitStatistics.h
		- ExtKitString.h
		- ExtKitTime.h

	# Others
		- ExtKit_Common.h
		- ExtKit_Config.h
		- ExtKit.h
		- ExtKitComponent.h
*/

}	// microbit_dal_ext_kit

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
#include "ExtKitRequest.h"
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
