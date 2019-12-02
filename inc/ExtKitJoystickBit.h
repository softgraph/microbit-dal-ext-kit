/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// JoystickBit component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_JOYSTICK_BIT_H
#define EXT_KIT_JOYSTICK_BIT_H

#include "ExtKitButton.h"
#include "ExtKitComponent.h"
#include "ExtKitDirection.h"

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for ElecFreaks' Joystick:bit board
/**
	@reference	ElecFreaks Joystick:bit for Micro:bit (SKU: EF03407)
		- https://www.elecfreaks.com/estore/elecfreaks-joystick-bit-for-micro-bit.html
	@reference	ElecFreaks Joystick:bit V2 For micro:bit (SKU: EF03417)
		- https://www.elecfreaks.com/estore/game-bit-for-micro-bit.html
*/
class JoystickBit : public Component
{
public:
	/// Check that the required hardware is avaialable.
	/**
	 * @return returns true if Joystick:bit for Micro:bit (SKU: EF03407) is available
	 * @note returns false even if Joystick:bit V2 For micro:bit (SKU: EF03417) is available
	 */
	static bool isAvaiable();

	enum HardwareVariant
	{
		V1,
		V2

	};	// HardwareVariant

	/// Constructor
	/**
	 * @param hardwareVariant
	 * - V1: Joystick:bit for Micro:bit (SKU: EF03407)
	 * - V2: Joystick:bit V2 For micro:bit (SKU: EF03417)
	 */
	JoystickBit(HardwareVariant hardwareVariant = V1);

	/// Read joystick buttons
	Buttons readJoystickButtons();

	/// Read joystick direction
	Direction readJoystickDirection();

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

	/// Hardware Variant
	HardwareVariant mHardwareVariant;

};	// JoystickBit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_JOYSTICK_BIT_H
