/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Display utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DISPLAY_H
#define EXT_KIT_DISPLAY_H

#include "MicroBitDisplay.h"

#include "ExtKitButton.h"
#include "ExtKitDirection.h"

class ManagedString;

namespace microbit_dal_ext_kit {

/// Display utility
namespace display {

/// Set Display Rotation
void setDisplayRotation(DisplayRotation displayRotation);

/// Display Rotation
DisplayRotation displayRotation();

/// Check that the device is Upside Down
bool isUpsideDown();

/// Clear Display
void clear();

/// Show Image
void showImage(MicroBitImage image);

/// Show Character
void showChar(char c);

/// Flash Character
void flashChar(char c, uint32_t durationInMilliseconds = 500);

/// Scroll Sring
void scrollString(const ManagedString& s);

/// Show Number
void showNumber(int twoDigitNumber /* 00-99 */);

/// Show Bits
void showBits(uint32_t bits /* 0x00000 - 0xfffff */);

/// Show Button
void showButton(Buttons buttons);

/// Show Direction
void showDirection(Direction direction);

}	// display
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DISPLAY_H
