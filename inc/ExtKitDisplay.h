/// Yotta module microbit-dal-ext-kit
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

#include "ExtKitButton.h"
#include "ExtKitDirection.h"

class ManagedString;

namespace microbit_dal_ext_kit {

/// Display utility
namespace display {

/// Set that the device is mounted upside down
void setUpsideDown();

/// Check that the device is mounted upside down
bool isUpsideDown();

void clear();
void showChar(char c);
void flashChar(char c, uint32_t durationInMilliseconds = 500);
void scrollString(const ManagedString& s);

void showNumber(int twoDigitNumber /* 00-99 */);
void showBits(uint32_t bits /* 0x00000 - 0xfffff */);
void showButton(Buttons buttons);
void showDirection(Direction direction);

}	// display
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DISPLAY_H
