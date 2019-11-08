/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Time utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitTime.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace time {

SystemTime /* milliseconds */ systemTime()
{
	//	Do the same as MicroBit::longSystemTime().
	return system_timer_current_time();
}

LongSystemTime /* milliseconds */ longSystemTime()
{
	return system_timer_current_time();
}

SystemTime durationFor(SystemTime target)
{
	target -= systemTime();
	return (target > (SystemTime) INT32_MAX) ? 0 : target;
}

LongSystemTime durationFor(LongSystemTime target)
{
	target -= longSystemTime();
	return (target > (LongSystemTime) INT64_MAX) ? 0 : target;
}

bool isElapsed(SystemTime target)
{
	return durationFor(target) == 0;
}

bool isElapsed(LongSystemTime target)
{
	return durationFor(target) == 0;
}

void sleep(uint32_t milliseconds)
{
	//	Do the same as MicroBit::sleep().
	fiber_sleep(milliseconds);
}

void sleep()
{
	// release the fiber, and enter the scheduler indefinitely
	release_fiber();
}

}	// time
}	// microbit_dal_ext_kit
