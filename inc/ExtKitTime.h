/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Time utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_TIME_H
#define EXT_KIT_TIME_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Time utility
namespace time {

/// System Time in milliseconds
typedef uint32_t	SystemTime;

/// Long System Time in milliseconds
typedef uint64_t	LongSystemTime;

/// Get the current System Time in milliseconds
SystemTime /* milliseconds */ systemTime();

/// Get the current Long System Time in milliseconds
LongSystemTime /* milliseconds */ longSystemTime();

/// Duration in milliseconds For a System Time
SystemTime durationFor(SystemTime target);

/// Duration in milliseconds For a Long System Time
LongSystemTime durationFor(LongSystemTime target);

/// Check whether a System Time is elapsed or not
bool isElapsed(SystemTime target);

/// Check whether a Long System Time is elapsed or not
bool isElapsed(LongSystemTime target);

/// Sleep milliseconds
void sleep(uint32_t milliseconds);

/// Sleep forever
void sleep();

}	// time
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_TIME_H
