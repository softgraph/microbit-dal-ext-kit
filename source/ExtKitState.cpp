/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// State utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitState.h"	// self
#include "ExtKitState.cpp.h"	// Implementation for "ExtKitState.h"

namespace microbit_dal_ext_kit {

/*
	Explicit Template Instantiation
*/

template class State<uint8_t>;
template class State<uint16_t>;
template class State<uint32_t>;

template class StateChange<uint8_t>;
template class StateChange<uint16_t>;
template class StateChange<uint32_t>;

}	// microbit_dal_ext_kit
