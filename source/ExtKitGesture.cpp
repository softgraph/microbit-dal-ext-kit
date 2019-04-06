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

int microBitGestureEventTiltLeft()
{
	switch(display::displayRotation()) {
		default:
		case MICROBIT_DISPLAY_ROTATION_0:	return MICROBIT_ACCELEROMETER_EVT_TILT_LEFT;
		case MICROBIT_DISPLAY_ROTATION_90:	return MICROBIT_ACCELEROMETER_EVT_TILT_DOWN;	// = TOP
		case MICROBIT_DISPLAY_ROTATION_180:	return MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT;
		case MICROBIT_DISPLAY_ROTATION_270:	return MICROBIT_ACCELEROMETER_EVT_TILT_UP;		// = BOTTOM
	}
}

int microBitGestureEventTiltTop()
{
	switch(display::displayRotation()) {
		case MICROBIT_DISPLAY_ROTATION_270:	return MICROBIT_ACCELEROMETER_EVT_TILT_LEFT;
		default:
		case MICROBIT_DISPLAY_ROTATION_0:	return MICROBIT_ACCELEROMETER_EVT_TILT_DOWN;	// = TOP
		case MICROBIT_DISPLAY_ROTATION_90:	return MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT;
		case MICROBIT_DISPLAY_ROTATION_180:	return MICROBIT_ACCELEROMETER_EVT_TILT_UP;		// = BOTTOM
	}
}

int microBitGestureEventTiltRight()
{
	switch(display::displayRotation()) {
		case MICROBIT_DISPLAY_ROTATION_180:	return MICROBIT_ACCELEROMETER_EVT_TILT_LEFT;
		case MICROBIT_DISPLAY_ROTATION_270:	return MICROBIT_ACCELEROMETER_EVT_TILT_DOWN;	// = TOP
		default:
		case MICROBIT_DISPLAY_ROTATION_0:	return MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT;
		case MICROBIT_DISPLAY_ROTATION_90:	return MICROBIT_ACCELEROMETER_EVT_TILT_UP;		// = BOTTOM
	}
}
int microBitGestureEventTiltBottom()
{
	switch(display::displayRotation()) {
		case MICROBIT_DISPLAY_ROTATION_90:	return MICROBIT_ACCELEROMETER_EVT_TILT_LEFT;
		case MICROBIT_DISPLAY_ROTATION_180:	return MICROBIT_ACCELEROMETER_EVT_TILT_DOWN;	// = TOP
		case MICROBIT_DISPLAY_ROTATION_270:	return MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT;
		default:
		case MICROBIT_DISPLAY_ROTATION_0:	return MICROBIT_ACCELEROMETER_EVT_TILT_UP;		// = BOTTOM
	}
}

}	// gesture
}	// microbit_dal_ext_kit
