/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// State utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_STATE_H
#define EXT_KIT_STATE_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Generic State Template
template <class T>
class State
{
public:
	/// Constructor
	State(T value);

	/// Get Value
	T value() const;

	/// Set Value
	bool /* changed */ set(T newValue);

protected:
	T mValue;

};	// State<T>

/// Generic State Change Template
template <class T>
class StateChange : public State<T>
{
public:
	/// Constructor
	StateChange(T value);

	/// Get Last Value
	T lastValue() const;

	/// Read Value
	bool /* changed */ read(T& /* OUT */ readValue);

protected:
	T mLastValue;

};	// State<T>

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_STATE_H