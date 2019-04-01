/// Yotta module microbit-dal-ext-kit
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

/// JoystickBit Component
/**
	Support for ElecFreaks' Joystick:bit board.
	@reference	ELECFREAKS Joystick:bit for Micro:bit
		- https://www.elecfreaks.com/estore/elecfreaks-joystick-bit-for-micro-bit.html
*/
class JoystickBit : public Component
{
public:
	/// Inherited
	static /* Component */ Features avaiableFeatures();

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	JoystickBit();

	/// Read joystick buttons
	Buttons readJoystickButtons();

	/// Read joystick direction
	Direction readJoystickDirection();

};	// JoystickBit

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_JOYSTICK_BIT_H
