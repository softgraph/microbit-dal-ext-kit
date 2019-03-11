/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Error utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitError.h"	// self
#include "ExtKit_System.h"

namespace microbit_dal_ext_kit {
namespace error {

void raise(const char *desc, const char *file, int line)
{
	serial::send(desc);
	serial::send(", file: ");
	serial::send(file);
	serial::send(", line: ");
	serial::sendLine(line);

	//	give other fibers a chance to keep running
	while(1) {
		time::sleep(1000  /* milliseconds */);
	}
}

void raise(const char *desc, const char* name, const void* object)
{
	serial::send(desc);
	serial::send(", name: ");
	serial::send(name);
	serial::send(", object: 0x");
	serial::sendLine(string::hex((uint32_t) object).toCharArray());

	//	give other fibers a chance to keep running
	while(1) {
		time::sleep(1000  /* milliseconds */);
	}
}

}	// error
}	// microbit_dal_ext_kit
