/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Error utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitError.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace error {

void raise(const char *desc, const char *file, int line, int panicCode)
{
	serial::send(desc);
	serial::send(", file: ");
	serial::send(file);
	serial::send(", line: ");
	serial::sendLine(line);

	if(panicCode) {
		microbit_panic(panicCode);
	}
	else {
		//	give other fibers a chance to keep running
		while(1) {
			time::sleep(1000  /* milliseconds */);
		}
	}
}

void raise(const char *desc, const char* name, const void* object, int panicCode)
{
	serial::send(desc);
	serial::send(", name: ");
	serial::send(name);
	serial::send(", object: 0x");
	serial::sendLine(string::hex((uint32_t) object).toCharArray());

	if(panicCode) {
		microbit_panic(panicCode);
	}
	else {
		//	give other fibers a chance to keep running
		while(1) {
			time::sleep(1000  /* milliseconds */);
		}
	}
}

}	// error
}	// microbit_dal_ext_kit
