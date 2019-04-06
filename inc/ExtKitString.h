/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// String utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_STRING_H
#define EXT_KIT_STRING_H

#include "ExtKit_Common.h"

class ManagedString;

/// Define Literal MicroBitImage
/**
	Example:
	@code
		EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(const, hello, "\x05", "Hello")
	@endcode
	The example above defines a const ManagedString named 'hello' with a literal string "Hello".
	It is basically equivalent to the following code but the string is not malloc()ed and therefore does not consume any heap space.
	@code
		const ManagedString hello("Hello");
	@endcode
*/
#define EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(	\
		qualifier /* 'const' or 'static const' */,	\
		name,	\
		stringForLength /* up to 255, e.g., "\x05" */,	\
		string)	\
	qualifier char x__ ## name[]	\
		__attribute__ ((aligned (4))) =	\
		"\xff\xff" stringForLength "\x00" string;	\
	qualifier ManagedString name((StringData*) x__ ## name);

namespace microbit_dal_ext_kit {

/// String utility
namespace string {

int16_t seek(const ManagedString& s, int16_t start, char prefix);	// returns MICROBIT_NO_DATA or the next position on s
int16_t beginsWith(const ManagedString& s, int16_t start, const char* prefix);	// returns MICROBIT_NO_DATA or the next position on s
uint32_t numberForHexString(const ManagedString& s, int16_t start);
ManagedString hex(uint32_t number, char prefix = 0);

}	// string
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_STRING_H
