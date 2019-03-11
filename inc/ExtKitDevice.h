/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Device utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DEVICE_H
#define EXT_KIT_DEVICE_H

#include "ExtKit_Common.h"

class MicroBitAccelerometer;
class MicroBitCompass;
class MicroBitMultiButton;
class MicroBitThermometer;

namespace microbit_dal_ext_kit {

/// Device utility.
namespace device {

/// Initialize the device.
void initialize();

/// Prepare for the button AB.
void prepareFor(MicroBitMultiButton* buttonAB);

/// Prepare for the accelerometer.
void prepareFor(MicroBitAccelerometer* accelerometer);

/// Prepare for the compass.
void prepareFor(MicroBitCompass *compass);

/// Prepare for the thermometer.
void prepareFor(MicroBitThermometer* thermometer);

/// Set that the device is mounted upside down.
void setUpsideDown();

/// Check that the device is mounted upside down.
bool isUpsideDown();

}	// device
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DEVICE_H
