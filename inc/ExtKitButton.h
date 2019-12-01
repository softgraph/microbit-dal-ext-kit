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

/// Buttons. The constants for type `#Buttons` are defined in namespace `microbit_dal_ext_kit::button`.
typedef uint16_t	Buttons;

/// `State` specialization for `#Buttons`
class StateForButtons : public State<Buttons>
{
public:
	/// Constructor
	StateForButtons();

};	// StateForButtons

/// `StateChange` specialization for `#Buttons`
class StateChangeForButtons : public StateChange<Buttons>
{
public:
	/// Constructor
	StateChangeForButtons();

};	// StateChangeForButtons

/// Button utility
namespace button {

const Buttons kInvalid	= (Buttons) -1;	///< Invalid Value
const Buttons kNone		= 0;			///< No button
const Buttons kL		= 1 << 0;		///< Button L = micro:bit Button A (or B if either `display::isBackToFront()` or `display::isUpsideDown()` is true)
const Buttons kR		= 1 << 1;		///< Button R = micro:bit Button B (or A if either `display::isBackToFront()` or `display::isUpsideDown()` is true)
const Buttons kLR		= kL | kR;		///< Button L + R
const Buttons kDirN		= 1 << 2;		///< Button Direction North
const Buttons kDirE		= 1 << 3;		///< Button Direction East
const Buttons kDirS		= 1 << 4;		///< Button Direction South
const Buttons kDirW		= 1 << 5;		///< Button Direction West
const Buttons kTiltU	= kDirN;		///< Button Tilt Up
const Buttons kTiltD	= kDirS;		///< Button Tilt Down
const Buttons kPanR		= kDirE;		///< Button Pan Right
const Buttons kPanL		= kDirW;		///< Button Pan Left
const Buttons kStart	= 1 << 6;		///< Button Start
const Buttons kSelect	= 1 << 7;		///< Button Select
const Buttons kOption1	= 1 << 8;		///< Button Option 1
const Buttons kOption2	= 1 << 9;		///< Button Option 2
const Buttons kOption3	= 1 << 10;		///< Button Option 3

const Buttons kA		= 1 << 2;		///< Button A (deprecated)
const Buttons kB		= 1 << 3;		///< Button B (deprecated)
const Buttons kC		= 1 << 4;		///< Button C (deprecated)
const Buttons kD		= 1 << 5;		///< Button D (deprecated)
const Buttons kE		= 1 << 6;		///< Button E (deprecated)
const Buttons kF		= 1 << 7;		///< Button F (deprecated)
const Buttons kG		= 1 << 8;		///< Button G (deprecated)
const Buttons kH		= 1 << 9;		///< Button H (deprecated)

int microBitIDButtonLeft();		///< MicroBit ID for left button.  Returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B.
int microBitIDButtonRight();	///< MicroBit ID for right button. Returns MICROBIT_ID_BUTTON_A or MICROBIT_ID_BUTTON_B.
void clickPseudoButton(char button /* a, b or w */);	///< Click pseudo button
bool isButtonAPressed();		///< Check whether button A is pressed or not
bool isButtonBPressed();		///< Check whether button B is pressed or not
Buttons readMicroBitButtons();	///< Read MicroBit buttons
void waitUntilMicroBitButtonsAreReleased();		///< Wait until MicroBit buttons are released

/// Choose a menu key character from `options` as a sub-menu item at `position`.
/**	For the details of `hints`, see also `appMode::DescriberProtocol::hints()`.
*/
char chooseFrom(const char* options, int position, const char* const * hints = 0);

}	// button
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_BUTTON_H
