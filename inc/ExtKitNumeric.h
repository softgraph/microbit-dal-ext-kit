/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Numeric utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_NUMERIC_H
#define EXT_KIT_NUMERIC_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Numeric utility
namespace numeric {

///	Clamp value.
inline int clamp(int min, int max, int value)
{
	if(value < min)			{ return min; }
	else if(max < value)	{ return max; }
	else					{ return value; }
}

}	// numeric
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_NUMERIC_H
