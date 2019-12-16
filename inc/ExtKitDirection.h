/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Direction utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DIRECTION_H
#define EXT_KIT_DIRECTION_H

#include "ExtKit_Common.h"
#include "ExtKitState.h"

namespace microbit_dal_ext_kit {

/// Direction. The constants for type #Direction are defined in namespace microbit_dal_ext_kit::direction.
typedef uint16_t	Direction;

/// State specialization for #Direction
class StateForDirection : public State<Direction>
{
public:
	/// Constructor
	StateForDirection();

};	// StateForDirection

/// StateChange specialization for #Direction
class StateChangeForDirection : public StateChange<Direction>
{
public:
	/// Constructor
	StateChangeForDirection();

};	// StateChangeForDirection

/// Direction utility
namespace direction {

const Direction kInvalid	= (Direction) -1;	///< Invalid Value
const Direction kCenter		= 0;				///< Center or No Direction
const Direction kN			= 1 << 0;			///< North     or move forward
const Direction kE			= 1 << 1;			///< East      or turn right
const Direction kW			= 1 << 2;			///< West      or turn left
const Direction kS			= 1 << 3;			///< South     or move backward
const Direction kNE			= kN | kE;			///< Northeast or move forward and turn right
const Direction kNW			= kN | kW;			///< Northwest or move forward and turn left
const Direction kSE			= kS | kE;			///< Southeast or move backward and turn right
const Direction kSW			= kS | kW;			///< Southwest or move backward and turn left

const Direction kLF			= 1 << 4;			///< Move left motor forward
const Direction kLB			= 1 << 5;			///< Move left motor backward
const Direction kRF			= 1 << 6;			///< Move right motor forward
const Direction kRB			= 1 << 7;			///< Move right motor backward

const Direction kStop		= 1 << 15;			///< Stop

}	// direction
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DIRECTION_H
