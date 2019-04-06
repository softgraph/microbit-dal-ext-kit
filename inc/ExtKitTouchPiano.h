/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// TouchPiano component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_TOUCH_PIANO_H
#define EXT_KIT_TOUCH_PIANO_H

#include "ExtKitBuzzer.h"
#include "ExtKitComponent.h"
#include "ExtKitNeoPixel.h"
#include "ExtKitPianoKey.h"

namespace microbit_dal_ext_kit {

/// TouchPiano Component
/**
	Support for Waveshare's Mini Piano Module for micro:bit.
	@reference	Waveshare Mini Piano Module for micro:bit
		- https://www.waveshare.com/piano-for-micro-bit.htm
		- https://www.waveshare.com/wiki/Piano_for_micro_bit
*/
class TouchPiano : public Component
{
public:
	/// Inherited
	static /* Component */ Features avaiableFeatures();

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	TouchPiano();

	/// Read piano keys
	void read(PianoKeys* /* OUT */ outKeys);

};	// TouchPiano

/// NeoPixel Component for TouchPiano
class NeoPixelForTouchPiano : public NeoPixel
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	NeoPixelForTouchPiano();

	/// Inherited
	/* NeoPixel */ void fillColorWithRainbow();

	/// Fill all led modules using a indicator range
	void fillColorWithIndicatorRange(int indicatorRange /* 0-7 */);

};	// NeoPixelForTouchPiano

/// Buzzer Component for TouchPiano
class BuzzerForTouchPiano : public Buzzer
{
public:
	/// Constructor
	BuzzerForTouchPiano();

};	// BuzzerForTouchPiano

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_TOUCH_PIANO_H
