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
#include "ExtKitDirection.h"

namespace microbit_dal_ext_kit {

/// Gesture utility
namespace gesture {

/// MICROBIT_ID_GESTURE event for tilt to a directiction
/**
 * @param tiltDdirection one of the following directions
 * - direction::kN
 * - direction::kE
 * - direction::kW
 * - direction::kS
 * .
 * @returns one of the following events depending on the configuration set by display::setDisplayRotation()
 * - MICROBIT_ACCELEROMETER_EVT_TILT_LEFT ... tilt to the left (A buton side of the micro:bit)
 * - MICROBIT_ACCELEROMETER_EVT_TILT_DOWN ... tilt to the top (USB connector side of the micro:bit)
 * - MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT ... tilt to the right (B button side of the micro:bit)
 * - MICROBIT_ACCELEROMETER_EVT_TILT_UP ... tilt to the bottom (edge connector side of the micro:bit)
 * - MICROBIT_ACCELEROMETER_EVT_NONE
 * .
 */
int microBitGestureEventTilt(Direction tiltDdirection);

/// MICROBIT_ID_GESTURE event for tilt to the logical left (west)
/**
 * @deprecated This method is obsolete and will be removed in a future release. Please use `microBitGestureEventTilt()` with `direction::kW` instead.
 */
int microBitGestureEventTiltLeft();

/// MICROBIT_ID_GESTURE event for tilt to the logical top (north)
/**
 * @deprecated This method is obsolete and will be removed in a future release. Please use `microBitGestureEventTilt()` with `direction::kN` instead.
 */
int microBitGestureEventTiltTop();

/// MICROBIT_ID_GESTURE event for tilt to the logical right (east)
/**
 * @deprecated This method is obsolete and will be removed in a future release. Please use `microBitGestureEventTilt()` with `direction::kE` instead.
 */
int microBitGestureEventTiltRight();

/// MICROBIT_ID_GESTURE event for tilt to the logical bottom (south)
/**
 * @deprecated This method is obsolete and will be removed in a future release. Please use `microBitGestureEventTilt()` with `direction::kS` instead.
 */
int microBitGestureEventTiltBottom();

}	// gesture
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GESTURE_H
