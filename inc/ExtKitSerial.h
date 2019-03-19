/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Serial utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_SERIAL_H
#define EXT_KIT_SERIAL_H

#include "ExtKit_Common.h"

class ManagedString;

namespace microbit_dal_ext_kit {

/// Serial utility
namespace serial {

/// Initialize RX.
void initializeRx();

/// Initialize TX.
void initializeTx();

/// Send data to the serial port
void send(char c);

/// Send data to the serial port
void send(int i);

/// Send data to the serial port
void send(const char* s);

/// Send data to the serial port
void send(const ManagedString& s);

/// Send a line to the serial port
void sendLine(char c, const char* suffix = "\r\n");

/// Send a line to the serial port
void sendLine(int i, const char* suffix = "\r\n");

/// Send a line to the serial port
void sendLine(const char* s, const char* suffix = "\r\n");

/// Send a line to the serial port
void sendLine(const ManagedString& s, const char* suffix = "\r\n");

/// Send a memory dump block to the serial port
void sendMemoryDump(const void* buffer, size_t length);

}	// serial
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SERIAL_H
