/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Debug Utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_DEBUG_H
#define EXT_KIT_DEBUG_H

#include "ExtKit_Common.h"

class ManagedString;

namespace microbit_dal_ext_kit {

/// The debug log prefix for an event item log.
#define	EXT_KIT_DEBUG_EVENT			"[E] "

/// The debug log prefix for an action item.
#define	EXT_KIT_DEBUG_ACTION		"[A] "

/// The debug log prefix for an information item.
#define	EXT_KIT_DEBUG_INFO			"[I] "

/// The debug log prefix for a trace item.
#define	EXT_KIT_DEBUG_TRACE			"[T] "

/// The debug log prefix for a trace item.
#define	EXT_KIT_DEBUG_STATISTICS	"[S] "

/// Set debugger enabled or disabled.
void debug_setDebugger(bool enabled);

/// Check whether the debugger is enabled or not.
bool debug_isDebuggerEnabled();

/// Send a string to the debugger.
void debug_sendLine(const char* s1, bool withDebugPrefix = true, const char* suffix = "\r\n");

/// Send strings to the debugger.
void debug_sendLine(const char* s1, const char* s2, bool withDebugPrefix = true, const char* suffix = "\r\n");

/// Send strings to the debugger.
void debug_sendLine(const char* s1, const char* s2, const char* s3, bool withDebugPrefix = true, const char* suffix = "\r\n");

/// Send strings to the debugger.
void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, bool withDebugPrefix = true, const char* suffix = "\r\n");

/// Send strings to the debugger.
void debug_sendLine(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, bool withDebugPrefix = true, const char* suffix = "\r\n");

/// Send a memory dump block to the debugger.
void debug_sendMemoryDump(const void* buffer, size_t length);

///	Debug Statistics utility.
namespace statistics {

/// Increment item count.
int /* result */ incrementItem(const ManagedString* title);	// returns MICROBIT_NO_RESOURCES or MICROBIT_OK

/// Set item value.
int /* result */ setItem(const ManagedString* title, uint16_t value);	// returns MICROBIT_NO_RESOURCES or MICROBIT_OK

/// Send changed items to the debugger.
void debug_sendItems();

}	// statistics
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_DEBUG_H
