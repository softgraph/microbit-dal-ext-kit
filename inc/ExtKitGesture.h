/// Yotta module microbit-dal-ext-kit
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

/// Returns MICROBIT_ACCELEROMETER_EVT_TILT_LEFT or RIGHT in accordance with display::isUpsideDown().
int microBitGestureEventTiltLeft();

/// Returns MICROBIT_ACCELEROMETER_EVT_TILT_LEFT or RIGHT in accordance with display::isUpsideDown().
int microBitGestureEventTiltRight();

}	// gesture
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_GESTURE_H
