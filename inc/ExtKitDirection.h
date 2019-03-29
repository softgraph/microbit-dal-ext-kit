/// Yotta module microbit-dal-ext-kit
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

/// Direction
typedef uint16_t	Direction;

/*
	Extern Template Instantiation
*/

extern template class State<Direction>;
extern template class StateChange<Direction>;

/// State For Direction
class StateForDirection : public State<Direction>
{
public:
	/// Constructor
	StateForDirection();

};	// StateForDirection

/// State Change For Direction
class StateChangeForDirection : public StateChange<Direction>
{
public:
	/// Constructor
	StateChangeForDirection();

};	// StateChangeForDirection

/// Direction values
namespace direction {

const Direction kInvalid	= (Direction) -1;
const Direction kCenter		= 0;
const Direction kN			= 1 << 0;		// north     or move forward
const Direction kE			= 1 << 1;		// east      or turn right
const Direction kW			= 1 << 2;		// wesr      or turn left
const Direction kS			= 1 << 3;		// south     or move backward
const Direction kNE			= kN | kE;		// northeast or move forward and turn right
const Direction kNW			= kN | kW;		// northwest or move forward and turn left
const Direction kSE			= kS | kE;		// southeast or move backward and turn right
const Direction kSW			= kS | kW;		// southwest or move backward and turn left

const Direction kLF			= 1 << 4;		// move left motor forward
const Direction kLB			= 1 << 5;		// move left motor backward
const Direction kRF			= 1 << 6;		// move right motor forward
const Direction kRB			= 1 << 7;		// move right motor backward

}	// direction
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DIRECTION_H
