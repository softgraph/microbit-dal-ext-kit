/// Yotta module microbit-dal-ext-kit
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

/// Send to Radio
void sendToRadio(const ManagedString& radioCmd);

/// Receive from Radio
ManagedString /* received */ recvFromRadio();

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_RADIO_H
