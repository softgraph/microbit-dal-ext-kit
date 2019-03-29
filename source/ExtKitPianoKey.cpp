/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Button utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitPianoKey.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	StateForPianoKeys
*/

StateForPianoKeys::StateForPianoKeys()
	: State<PianoKeys>(pianoKey::kNone)
{
}

/**	@class	StateChangeForPianoKeys
*/

StateChangeForPianoKeys::StateChangeForPianoKeys()
	: StateChange<PianoKeys>(pianoKey::kNone)
{
}

}	// microbit_dal_ext_kit
