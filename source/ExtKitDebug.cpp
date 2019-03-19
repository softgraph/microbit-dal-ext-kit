/// Yotta module microbit-dal-ext-kit
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

static bool sIsDebuggerEnabled = false;

void debug_setDebugger(bool enabled)
{
	if(sIsDebuggerEnabled == enabled) {
		return;
	}

	if(enabled) {
		sIsDebuggerEnabled = true;
		debug_sendLine(EXT_KIT_DEBUG_INFO "Serial debugger: enabled");
	}
	else {
		debug_sendLine(EXT_KIT_DEBUG_INFO "Serial debugger: disabled");
		sIsDebuggerEnabled = false;
	}
}

bool debug_isDebuggerEnabled()
{
	return sIsDebuggerEnabled;
}

void debug_sendLine(const char* s, bool withDebugPrefix, const char* suffix)
{
	debug_sendLine(s, NULL, NULL, NULL, NULL, withDebugPrefix, suffix);
}

void debug_sendLine(const char* s1, const char* s2, bool withDebugPrefix, const char* suffix)
{
	debug_sendLine(s1, s2, NULL, NULL, NULL, withDebugPrefix, suffix);
}

void debug_sendLine(const char* s1, const char* s2, const char* s3, bool withDebugPrefix, const char* suffix)
{
	debug_sendLine(s1, s2, s3, NULL, NULL, withDebugPrefix, suffix);
}

void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, bool withDebugPrefix, const char* suffix)
{
	debug_sendLine(s1, s2, s3, s4, NULL, withDebugPrefix, suffix);
}

void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, bool withDebugPrefix, const char* suffix)
{
	if(!sIsDebuggerEnabled) {
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
	if(!sIsDebuggerEnabled) {
		return;
	}

	serial::sendMemoryDump(buffer, length);
}

}	// microbit_dal_ext_kit
