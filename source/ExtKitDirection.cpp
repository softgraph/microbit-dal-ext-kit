/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Button utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitDirection.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	StateForDirection
*/

StateForDirection::StateForDirection()
	: State<Direction>(direction::kCenter)
{
}

/**	@class	StateChangeForDirection
*/

StateChangeForDirection::StateChangeForDirection()
	: StateChange<Direction>(direction::kCenter)
{
}

}	// microbit_dal_ext_kit
