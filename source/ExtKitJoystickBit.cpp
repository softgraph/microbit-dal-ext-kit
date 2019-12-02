/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// JoystickBit component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitJoystickBit.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	JoystickBit
	@reference	Code example for ElecFreaks Joystick:bit for Micro:bit (SKU: EF03407)
		- https://www.elecfreaks.com/estore/elecfreaks-joystick-bit-for-micro-bit.html
	@reference	joytick:bit Package for ElecFreaks Joystick:bit V2 For micro:bit (SKU: EF03417)
		- https://makecode.microbit.org/pkg/tinkertanker/pxt-joystickbit
	@reference	Tinkertanker/pxt-joystickbit/joystickbit.ts (MIT license)
		- https://github.com/Tinkertanker/pxt-joystickbit
		- https://github.com/Tinkertanker/pxt-joystickbit/blob/master/joystickbit.ts
*/

static const int kJoystickDirectionCenterMin = 400;
static const int kJoystickDirectionCenterMax = 600;

bool JoystickBit::isAvaiable()
{
	MicroBitIO& io = ExtKit::global().io();
	int valueX = io.P0.getAnalogValue();
	int valueY = io.P1.getAnalogValue();
	return
		(((kJoystickDirectionCenterMin <= valueX) && (valueX <= kJoystickDirectionCenterMax)) &&
		 ((kJoystickDirectionCenterMin <= valueY) && (valueY <= kJoystickDirectionCenterMax)));
}

JoystickBit::JoystickBit(HardwareVariant hardwareVariant)
	: Component("JoystickBit")
	, mHardwareVariant(hardwareVariant)
{
}

/* Component */ void JoystickBit::doHandleComponentAction(Action action)
{
	if(action == kStart)
	{
		MicroBitIO& io = ExtKit::global().io();
		switch(mHardwareVariant) {
			default:
			case V1: {
				debug_sendLine(EXT_KIT_DEBUG_ACTION "JoystickBit::doHandleComponentAction(kStart) mHardwareVariant: V1");

				// the following analog inputs are available
				//	io.P0.getAnalogValue();	// X
				//	io.P1.getAnalogValue();	// Y
				//	io.P2.getAnalogValue();	// Buttons
				break;
			}
			case V2: {
				debug_sendLine(EXT_KIT_DEBUG_ACTION "JoystickBit::doHandleComponentAction(kStart) mHardwareVariant: V2");

				// configure digital inputs and outputs
				io.P0.setDigitalValue(0);	// Buzzer
				io.P12.getDigitalValue(PullUp);	// Button C
				io.P13.getDigitalValue(PullUp);	// Button D
				io.P14.getDigitalValue(PullUp);	// Button E
				io.P15.getDigitalValue(PullUp);	// Button F
				io.P16.setDigitalValue(1);	// Vibration motor

				// the following analog inputs become available after the configuration above
				//	io.P1.getAnalogValue();	// X
				//	io.P2.getAnalogValue();	// Y
				break;
			}
		}
	}

	/* super */ Component::doHandleComponentAction(action);
}

Buttons JoystickBit::readJoystickButtons()
{
	Buttons buttons = button::readMicroBitButtons();
	MicroBitIO& io = ExtKit::global().io();
	switch(mHardwareVariant) {
		default:
		case V1: {
			int value = io.P2.getAnalogValue();
			if(value < 256) {
				buttons |= button::kDirN;
			}
			else if(value < 597) {
				buttons |= button::kDirE;
			}
			else if(value < 725) {
				buttons |= button::kDirS;
			}
			else if(value < 793) {
				buttons |= button::kDirW;
			}
			else if(value < 836) {
				buttons |= button::kSelect;
			}
			else if(value < 938) {
				buttons |= button::kStart;
			}
			break;
		}
		case V2: {
			if(buttons & button::kL) {
				buttons |= button::kSelect;
			}
			if(buttons & button::kR) {
				buttons |= button::kStart;
			}
			buttons &= ~button::kLR;
			buttons |= io.P12.getDigitalValue() ? 0 : button::kDirW;
			buttons |= io.P13.getDigitalValue() ? 0 : button::kDirN;
			buttons |= io.P14.getDigitalValue() ? 0 : button::kDirS;
			buttons |= io.P15.getDigitalValue() ? 0 : button::kDirE;
			break;
		}
	}
	return buttons;
}

Direction JoystickBit::readJoystickDirection()
{
	Direction direction = 0;
	MicroBitIO& io = ExtKit::global().io();
	switch(mHardwareVariant) {
		default:
		case V1: {
			int valueX = io.P0.getAnalogValue();
			int valueY = io.P1.getAnalogValue();
			if(valueX < kJoystickDirectionCenterMin) {
				direction |= direction::kW;
			}
			else if(kJoystickDirectionCenterMax < valueX) {
				direction |= direction::kE;
			}
			if(valueY < kJoystickDirectionCenterMin) {
				direction |= direction::kS;
			}
			else if(kJoystickDirectionCenterMax < valueY) {
				direction |= direction::kN;
			}
			break;
		}
		case V2: {
			int valueX = io.P1.getAnalogValue();
			int valueY = io.P2.getAnalogValue();
			//	debug_sendLine(EXT_KIT_DEBUG_TRACE "JoystickBit::readJoystickDirection() valueX: ", string::dec(valueX).toCharArray());
			//	debug_sendLine(EXT_KIT_DEBUG_TRACE "JoystickBit::readJoystickDirection() valueY: ", string::dec(valueY).toCharArray());

			if(valueX < kJoystickDirectionCenterMin) {
				direction |= direction::kE;
			}
			else if(kJoystickDirectionCenterMax < valueX) {
				direction |= direction::kW;
			}
			if(valueY < kJoystickDirectionCenterMin) {
				direction |= direction::kS;
			}
			else if(kJoystickDirectionCenterMax < valueY) {
				direction |= direction::kN;
			}
			break;
		}
	}
	return direction;
}

}	// microbit_dal_ext_kit
