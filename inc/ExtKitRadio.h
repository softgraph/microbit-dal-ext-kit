/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Radio utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_RADIO_H
#define EXT_KIT_RADIO_H

#include "ExtKit_Common.h"

class ManagedString;

namespace microbit_dal_ext_kit {

/// Radio utility
namespace radio {

/// Prepare
void prepare();

/// Send
void send(const ManagedString& command);

/// Recv
ManagedString /* received */ recv();

}	// radio
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_RADIO_H
