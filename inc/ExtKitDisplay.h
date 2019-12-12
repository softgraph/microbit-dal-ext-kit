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
/**
 * @param displayRotation
 * @param backToFront
 * @note Here are examples of `displayRotation` and `backToFront`.
 * - `displayRotation` is MICROBIT_DISPLAY_ROTATION_0 and `backToFront` is false
 *   @code
 *           Forward (N)
 *          +-----------+
 *          |           |
 *     Left | A  LCD  B | Right
 *      (W) |           | (E)
 *          +-+-+-+-+-+-+
 *           Backward (S)
 *   @endcode
 * - `displayRotation` is MICROBIT_DISPLAY_ROTATION_0 and `backToFront` is true
 *   @code
 *           Backward (S)
 *          +-----------+
 *          |           |
 *    Right | A  LCD  B | Left
 *      (E) |           | (W)
 *          +-+-+-+-+-+-+
 *           Forward (N)
 *   @endcode
 * - `displayRotation` is MICROBIT_DISPLAY_ROTATION_90 and `backToFront` is false
 *   @code
 *           Forward (N)
 *          +-----------+
 *          +     A     |
 *     Left +    LCD    | Right
 *      (W) +     B     | (E)
 *          +-----------+
 *           Backward (S)
 *   @endcode
 * - `displayRotation` is MICROBIT_DISPLAY_ROTATION_180 and `backToFront` is false
 *   @code
 *           Forward (N)
 *          +-+-+-+-+-+-+
 *          |           |
 *     Left | B  LCD  A | Right
 *      (W) |           | (E)
 *          +-----------+
 *           Backward (S)
 *   @endcode
 * - `displayRotation` is MICROBIT_DISPLAY_ROTATION_270 and `backToFront` is false
 *   @code
 *           Forward (N)
 *          +-----------+
 *          |     B     +
 *     Left |    LCD    + Right
 *      (W) |     A     + (E)
 *          +-----------+
 *           Backward (S)
 *   @endcode
 */
void setDisplayRotation(DisplayRotation displayRotation, bool backToFront = false);

/// Display Rotation
/** @sa setDisplayRotation() */
DisplayRotation displayRotation();

/// Check that the device is mounted back to front.
/** @returns true if setDisplayRotation() has been called with the following conditions
 * - backToFront: true
 */
bool isBackToFront();

/// Check that the device is mounted upside down.
/** @returns true if setDisplayRotation() has been called with the following conditions
 * - displayRotation: MICROBIT_DISPLAY_ROTATION_180
 */
bool isUpsideDown();

/// Clear Display
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void clear(uint32_t durationInMilliseconds = 0);

/// Show an Image
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showImage(MicroBitImage image, uint32_t durationInMilliseconds = 0);

/// Show a Character
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showChar(char c, uint32_t durationInMilliseconds = 0);

/// Flash a Character
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 * @deprecated This method is obsolete and will be removed in a future release. Please use `showChar()` with `durationInMilliseconds` instead.
 */
void flashChar(char c, uint32_t durationInMilliseconds = 500);

/// Set Scroll Speed
void setScrollSpeed(int speed);

/// Scroll a Sring and then Show a Character
void scrollString(const ManagedString& s, char c = 0);

/// Scroll a Sring and then Show a Character Asynchronously
void scrollStringAsync(const ManagedString& s, char c = 0);

/// Show a Number
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showNumber(int twoDigitNumber /* 00-99 */, uint32_t durationInMilliseconds = 0);

/// Show Bits
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showBits(uint32_t bits /* 0x00000 - 0xfffff */, uint32_t durationInMilliseconds = 0);

/// Show Button %State
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showButton(Buttons buttons, uint32_t durationInMilliseconds = 0);

/// Arrow Type
enum ArrowType
{
	/// Guide Bar like |
	kGuideBar,

	/// Angle like <
	kAngle,

	/// Arrow like ←
	kArrow,

	/// Solid Triangle like ◀︎
	kSolidTriangle

};

/// Count of Arrow Types
const size_t kCountArrowTypes = kSolidTriangle + 1;

/// Show Direction %State
/**
 * @note The function will be blocked until the flashing is completed if `durationInMilliseconds` is not 0.
 */
void showDirection(Direction direction, ArrowType arrowType = kGuideBar, uint32_t durationInMilliseconds = 0);

}	// display
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DISPLAY_H
