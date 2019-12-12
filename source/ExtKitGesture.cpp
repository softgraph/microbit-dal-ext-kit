/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Gesture utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitGesture.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace gesture {

/// @cond static

/// Indices and count for events
enum EventIndex
{
	kEventN,	///< N for MICROBIT_DISPLAY_ROTATION_0
	kEventW,	///< W for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_90)
	kEventS,	///< S for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_180)
	kEventE,	///< E for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_270)
	kEventCount	///< Count

};	// EventIndex

/// @endcond static

static int sMicroBitGestureEvents[kEventCount] = {
	MICROBIT_ACCELEROMETER_EVT_TILT_DOWN,	// [kEventN]
	MICROBIT_ACCELEROMETER_EVT_TILT_LEFT, 	// [kEventW]
	MICROBIT_ACCELEROMETER_EVT_TILT_UP,		// [kEventS]
	MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT	// [kEventE]
};

int microBitGestureEventTilt(Direction tiltDdirection)
{
	if(display::isBackToFront()) {
		switch(tiltDdirection) {
			case direction::kN: { tiltDdirection = direction::kS; break; }
			case direction::kE: { tiltDdirection = direction::kW; break; }
			case direction::kW: { tiltDdirection = direction::kE; break; }
			case direction::kS: { tiltDdirection = direction::kN; break; }
			default: { break; }
		}
	}

	int /* EventIndex */ eventIndex = -1;
	switch(tiltDdirection) {
		case direction::kN: { eventIndex = kEventN; break; }
		case direction::kE: { eventIndex = kEventE; break; }
		case direction::kW: { eventIndex = kEventW; break; }
		case direction::kS: { eventIndex = kEventS; break; }
		default: { break; }
	}

	if(0 <= eventIndex) {
		eventIndex += display::displayRotation();
		eventIndex %= kEventCount;
		return sMicroBitGestureEvents[eventIndex];
	}
	else {
		return MICROBIT_ACCELEROMETER_EVT_NONE;
	}
}

int microBitGestureEventTiltLeft()
{
	return microBitGestureEventTilt(direction::kW);
}

int microBitGestureEventTiltTop()
{
	return microBitGestureEventTilt(direction::kN);
}

int microBitGestureEventTiltRight()
{
	return microBitGestureEventTilt(direction::kE);
}
int microBitGestureEventTiltBottom()
{
	return microBitGestureEventTilt(direction::kS);
}

}	// gesture
}	// microbit_dal_ext_kit
