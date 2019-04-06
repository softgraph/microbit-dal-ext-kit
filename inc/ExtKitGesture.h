/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Gesture utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_GESTURE_H
#define EXT_KIT_GESTURE_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Gesture utility
namespace gesture {

/// Event value for MICROBIT_ID_GESTURE. Returns MICROBIT_ACCELEROMETER_EVT_TILT_LEFT if display::displayRotation() is MICROBIT_DISPLAY_ROTATION_0.
int microBitGestureEventTiltLeft();

/// Event value for MICROBIT_ID_GESTURE. Returns MICROBIT_ACCELEROMETER_EVT_TILT_DOWN (= TOP) if display::displayRotation() is MICROBIT_DISPLAY_ROTATION_0.
int microBitGestureEventTiltTop();

/// Event value for MICROBIT_ID_GESTURE. Returns MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT if display::displayRotation() is MICROBIT_DISPLAY_ROTATION_0.
int microBitGestureEventTiltRight();

/// Event value for MICROBIT_ID_GESTURE. Returns MICROBIT_ACCELEROMETER_EVT_TILT_UP (= BOTTOM) if display::displayRotation() is MICROBIT_DISPLAY_ROTATION_0.
int microBitGestureEventTiltBottom();

}	// gesture
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GESTURE_H
