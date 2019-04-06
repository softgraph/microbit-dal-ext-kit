/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Button utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitOctave.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	StateForOctave
*/

StateForOctave::StateForOctave()
	: State<Octave>(octave::kCenter)
{
}

/**	@class	StateChangeForOctave
*/

StateChangeForOctave::StateChangeForOctave()
	: StateChange<Octave>(octave::kCenter)
{
}

}	// microbit_dal_ext_kit
