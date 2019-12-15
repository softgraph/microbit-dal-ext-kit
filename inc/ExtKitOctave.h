/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Octave utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_OCTAVE_H
#define EXT_KIT_OCTAVE_H

#include "ExtKit_Common.h"
#include "ExtKitState.h"

namespace microbit_dal_ext_kit {

///	Octave. The constants for type `#Octave` are defined in namespace `microbit_dal_ext_kit::octave`.
typedef uint16_t	Octave;

/// `State` specialization for `#Octave`
class StateForOctave : public State<Octave>
{
public:
	/// Constructor
	StateForOctave();

};	// StateForOctave

/// `StateChange` specialization for `#Octave`
class StateChangeForOctave : public StateChange<Octave>
{
public:
	/// Constructor
	StateChangeForOctave();

};	// StateChangeForOctave

///	Octave utility
namespace octave {

///	Invalid value
const Octave kInvalid	= (Octave) -1;

///	The lowest octave value. `#PianoKeys` are assigned to C1 - C2.
const Octave kLowest	= 1;

///	The center octave value. `#PianoKeys` are assigned to C4 - C5.
const Octave kCenter	= 4;

///	The highest octave value. `#PianoKeys` are assigned to C7 - C8.
const Octave kHighest	= 7;

}	// octave
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_OCTAVE_H
