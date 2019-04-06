/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Button utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitButton.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	StateForButtons
*/

StateForButtons::StateForButtons()
	: State<Buttons>(button::kNone)
{
}

/**	@class	StateChangeForButtons
*/

StateChangeForButtons::StateChangeForButtons()
	: StateChange<Buttons>(button::kNone)
{
}

namespace button {

static bool hasPseudoButtonAClicked = false;
static bool hasPseudoButtonBClicked = false;

int microBitIDButtonLeft()	// returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B
{
	return display::isUpsideDown() ? MICROBIT_ID_BUTTON_B : MICROBIT_ID_BUTTON_A;
}

int microBitIDButtonRight()	// returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B
{
	return display::isUpsideDown() ? MICROBIT_ID_BUTTON_A : MICROBIT_ID_BUTTON_B;
}

void clickPseudoButton(char button /* a, b or w */)
{
	switch (button) {
		case 'a':
		case 'A': {
			hasPseudoButtonAClicked = true;
			break;
		}
		case 'b':
		case 'B': {
			hasPseudoButtonBClicked = true;
			break;
		}
		case 'w':
		case 'W': {
			hasPseudoButtonAClicked = true;
			hasPseudoButtonBClicked = true;
			break;
		}
	}
}

bool isButtonAPressed()
{
	if(hasPseudoButtonAClicked) {
		hasPseudoButtonAClicked = false;
		return true;
	}

	ExtKit& g = ExtKit::global();
	MicroBitButton& b = g.buttonA();
	return b.isPressed();
}

bool isButtonBPressed()
{
	if(hasPseudoButtonBClicked) {
		hasPseudoButtonBClicked = false;
		return true;
	}

	ExtKit& g = ExtKit::global();
	MicroBitButton& b = g.buttonB();
	return b.isPressed();
}

static void swap(bool& a, bool& b)
{
	bool t = a;
	a = b;
	b = t;
}

Buttons readMicroBitButtons()
{
	Buttons buttons = 0;
	bool isButtonLPressed = isButtonAPressed();
	bool isButtonRPressed = isButtonBPressed();
	if(display::isUpsideDown()) {
		swap(isButtonLPressed, isButtonRPressed);
	}
	if(isButtonLPressed) {
		buttons |= button::kL;
	}
	if(isButtonRPressed) {
		buttons |= button::kR;
	}
	return buttons;
}

void waitUntilMicroBitButtonsAreReleased()
{
	while(isButtonAPressed() || isButtonBPressed()) {
		time::sleep(100 /* milliseconds */);
	}
}

}	// button
}	// microbit_dal_ext_kit
