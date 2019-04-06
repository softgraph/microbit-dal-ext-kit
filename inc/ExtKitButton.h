/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Button utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_BUTTON_H
#define EXT_KIT_BUTTON_H

#include "ExtKit_Common.h"
#include "ExtKitState.h"

namespace microbit_dal_ext_kit {

/// Buttons
typedef uint16_t	Buttons;

/*
	Extern Template Instantiation
*/

extern template class State<uint16_t>;
extern template class StateChange<uint16_t>;

/// State For Buttons
class StateForButtons : public State<Buttons>
{
public:
	/// Constructor
	StateForButtons();

};	// StateForButtons

/// State Change For Buttons
class StateChangeForButtons : public StateChange<Buttons>
{
public:
	/// Constructor
	StateChangeForButtons();

};	// StateChangeForButtons

/// Button utility
namespace button {

const Buttons kInvalid	= (Buttons) -1;
const Buttons kNone		= 0;
const Buttons kL		= 1 << 0;		// Button L = micro:bit Button A, or B if display::isUpsideDown() is true
const Buttons kR		= 1 << 1;		// Button R = micro:bit Button B, or A if display::isUpsideDown() is true
const Buttons kA		= 1 << 2;		// Button A
const Buttons kB		= 1 << 3;		// Button B
const Buttons kC		= 1 << 4;		// Button C
const Buttons kD		= 1 << 5;		// Button D
const Buttons kE		= 1 << 6;		// Button E
const Buttons kF		= 1 << 7;		// Button F
const Buttons kG		= 1 << 8;		// Button G
const Buttons kH		= 1 << 9;		// Button H
const Buttons kLR		= kL | kR;		// Button L + R

int microBitIDButtonLeft();		// returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B
int microBitIDButtonRight();	// returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B
void clickPseudoButton(char button /* a, b or w */);
bool isButtonAPressed();
bool isButtonBPressed();
Buttons readMicroBitButtons();
void waitUntilMicroBitButtonsAreReleased();

}	// button
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_BUTTON_H
