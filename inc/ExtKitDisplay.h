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
void setDisplayRotation(DisplayRotation displayRotation, bool backToFront = false);

/// Display Rotation
DisplayRotation displayRotation();

/// Check that the device is mounted back to front, i.e., left and right are inverted.
bool isBackToFront();

/// Check that the device is mounted upside down, i.e. top and bottom are inverted.
bool isUpsideDown();

/// Clear Display
void clear();

/// Show an Image
void showImage(MicroBitImage image);

/// Show a Character
void showChar(char c);

/// Flash a Character
void flashChar(char c, uint32_t durationInMilliseconds = 500);

/// Set Scroll Speed
void setScrollSpeed(int speed);

/// Scroll a Sring and then Show a Character
void scrollString(const ManagedString& s, char c = 0);

/// Scroll a Sring and then Show a Character Asynchronously
void scrollStringAsync(const ManagedString& s, char c = 0);

/// Show a Number
void showNumber(int twoDigitNumber /* 00-99 */);

/// Show Bits
void showBits(uint32_t bits /* 0x00000 - 0xfffff */);

/// Show Button State
void showButton(Buttons buttons);

/// Show Direction State
void showDirection(Direction direction);

}	// display
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DISPLAY_H
