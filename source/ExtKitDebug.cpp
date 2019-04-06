/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Debug utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitDebug.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

static bool sIsDebuggerActive = false;

void debug_activateDebugger(bool activate)
{
	if(sIsDebuggerActive == activate) {
		return;
	}

	if(activate) {
		sIsDebuggerActive = true;
		debug_sendLine(EXT_KIT_DEBUG_INFO "Serial debugger: activated");
	}
	else {
		debug_sendLine(EXT_KIT_DEBUG_INFO "Serial debugger: deactivated");
		sIsDebuggerActive = false;
	}
}

bool debug_isDebuggerActive()
{
	return sIsDebuggerActive;
}

void debug_sendLine(bool withDebugPrefix, const char* suffix, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
	if(!sIsDebuggerActive) {
		return;
	}

	if(withDebugPrefix) {
		static time::SystemTime lastTime = 0;
		time::SystemTime time = time::systemTime();
		time::SystemTime diff = time - lastTime;
		serial::send("@");
		serial::send((int) time);
		serial::send(" +");
		serial::send((int) diff);
		serial::send("\t");
		lastTime = time;
	}
	serial::send(s1);
	serial::send(s2);
	serial::send(s3);
	serial::send(s4);
	serial::send(s5);
	serial::send(suffix);
}

void debug_sendMemoryDump(const void* buffer, size_t length)
{
	if(!sIsDebuggerActive) {
		return;
	}

	serial::sendMemoryDump(buffer, length);
}

}	// microbit_dal_ext_kit
