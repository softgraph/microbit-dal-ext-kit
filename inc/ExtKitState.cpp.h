/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// State utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_STATE_CPP_H
#define EXT_KIT_STATE_CPP_H

#include "ExtKitState.h"	// self

namespace microbit_dal_ext_kit {

/**	@class State
*/

template <class T>
State<T>::State(T value)
	: mValue(value)
{
}

template <class T>
T State<T>::value() const
{
	return mValue;
}

template <class T>
bool /* changed */ State<T>::set(T newValue)
{
	if(mValue == newValue) {
		return false;
	}
	mValue = newValue;
	return true;
}

/**	@class StateChange
*/

template <class T>
StateChange<T>::StateChange(T value)
	: State<T>(value)
	, mLastValue(value)
{
}

template <class T>
T StateChange<T>::lastValue() const
{
	return mLastValue;
}

template <class T>
bool /* changed */ StateChange<T>::read(T& /* OUT */ readValue)
{
	readValue = this->mValue;
	if(mLastValue == readValue) {
		return false;
	}
	mLastValue = readValue;
	return true;
}

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_STATE_CPP_H
