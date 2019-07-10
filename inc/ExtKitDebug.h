/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Debug utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DEBUG_H
#define EXT_KIT_DEBUG_H

#include "ExtKit_Common.h"

class ManagedString;

/// The debug log prefix for an event item log
#define	EXT_KIT_DEBUG_EVENT			"[E] "

/// The debug log prefix for an action item
#define	EXT_KIT_DEBUG_ACTION		"[A] "

/// The debug log prefix for an information item
#define	EXT_KIT_DEBUG_INFO			"[I] "

/// The debug log prefix for a trace item
#define	EXT_KIT_DEBUG_TRACE			"[T] "

/// The debug log prefix for a trace item
#define	EXT_KIT_DEBUG_STATISTICS	"[S] "

namespace microbit_dal_ext_kit {

/// Activate or deactivate the debugger
void debug_activateDebugger(bool activate);

/// Check whether the debugger is active or not
bool debug_isDebuggerActive();

/// Send strings to the debugger
void debug_sendLine(bool withDebugPrefix, const char* suffix, const char* s1, const char* s2 = 0, const char* s3 = 0, const char* s4 = 0, const char* s5 = 0);

/// Send a string to the debugger
inline void debug_sendLine(const char* s1, bool withDebugPrefix = true, const char* suffix = "\r\n")
{
	debug_sendLine(withDebugPrefix, suffix, s1);
}

/// Send strings to the debugger
inline void debug_sendLine(const char* s1, const char* s2, bool withDebugPrefix = true, const char* suffix = "\r\n")
{
	debug_sendLine(withDebugPrefix, suffix, s1, s2);
}

/// Send strings to the debugger
inline void debug_sendLine(const char* s1, const char* s2, const char* s3, bool withDebugPrefix = true, const char* suffix = "\r\n")
{
	debug_sendLine(withDebugPrefix, suffix, s1, s2, s3);
}

/// Send strings to the debugger
inline void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, bool withDebugPrefix = true, const char* suffix = "\r\n")
{
	debug_sendLine(withDebugPrefix, suffix, s1, s2, s3, s4);
}

/// Send strings to the debugger
inline void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, bool withDebugPrefix = true, const char* suffix = "\r\n")
{
	debug_sendLine(withDebugPrefix, suffix, s1, s2, s3, s4, s5);
}

/// Send a memory dump block to the debugger
void debug_sendMemoryDump(const void* buffer, size_t length);

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DEBUG_H
