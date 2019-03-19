/// Yotta module microbit-dal-ext-kit
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

int microBitGestureEventTiltLeft()	// for MICROBIT_ID_GESTURE
{
	return display::isUpsideDown() ? MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT : MICROBIT_ACCELEROMETER_EVT_TILT_LEFT;
}

int microBitGestureEventTiltRight()	// for MICROBIT_ID_GESTURE
{
	return display::isUpsideDown() ? MICROBIT_ACCELEROMETER_EVT_TILT_LEFT : MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT;
}

}	// gesture
}	// microbit_dal_ext_kit
