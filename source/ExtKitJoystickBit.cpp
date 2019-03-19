/// Yotta module microbit-dal-ext-kit
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

/*
	@class	JoystickBit
	@sa	ELECFREAKS Joystick:bit code example.
		- https://www.elecfreaks.com/estore/elecfreaks-joystick-bit-for-micro-bit.html
*/

static const int kJoystickDirectionCenterMin = 400;
static const int kJoystickDirectionCenterMax = 600;

static const Features kFeature = feature::kJoystickBit;

/* Component */ Features JoystickBit::avaiableFeatures()
{
	ExtKit& g = ExtKit::global();
	int valueX = g.p0().getAnalogValue();
	int valueY = g.p1().getAnalogValue();
	bool available =
		(((kJoystickDirectionCenterMin <= valueX) && (valueX <= kJoystickDirectionCenterMax)) &&
		 ((kJoystickDirectionCenterMin <= valueY) && (valueY <= kJoystickDirectionCenterMax)));
	return available ? kFeature : 0;
}

/* Component */ bool JoystickBit::isConfigured()
{
	return feature::isConfigured(kFeature);
}

JoystickBit::JoystickBit()
	: Component("JoystickBit")
{
}

Buttons JoystickBit::readJoystickButtons()
{
	Buttons buttons = button::readMicroBitButtons();
	ExtKit& g = ExtKit::global();
	int value = g.p2().getAnalogValue();
	if(value < 256) {
		buttons |= button::kA;
	}
	else if(value < 597) {
		buttons |= button::kB;
	}
	else if(value < 725) {
		buttons |= button::kC;
	}
	else if(value < 793) {
		buttons |= button::kD;
	}
	else if(value < 836) {
		buttons |= button::kF;
	}
	else if(value < 938) {
		buttons |= button::kE;
	}
	return buttons;
}

Direction JoystickBit::readJoystickDirection()
{
	Direction direction = 0;
	ExtKit& g = ExtKit::global();
	int valueX = g.p0().getAnalogValue();
	int valueY = g.p1().getAnalogValue();
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
	return direction;
}

}	// microbit_dal_ext_kit
