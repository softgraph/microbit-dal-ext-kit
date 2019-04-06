/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// ZipHalo component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_ZIP_HALO_H
#define EXT_KIT_ZIP_HALO_H

#include "ExtKitBuzzer.h"
#include "ExtKitComponent.h"
#include "ExtKitNeoPixel.h"

namespace microbit_dal_ext_kit {

/// ZipHalo Component
/**
	Support for Kitronik's Zip Halo board.
	@reference	Kitronik Zip Halo
		- https://www.kitronik.co.uk/5625-zip-halo-for-the-bbc-microbit.html
		- https://www.kitronik.co.uk/blog/get-started-with-zip-halo
*/
class ZipHalo : public Component
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	ZipHalo();

};	// ZipHalo

/// NeoPixel Component for ZipHalo
class NeoPixelForZipHalo : public NeoPixel
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	NeoPixelForZipHalo();

	/// Reset max brightness value in percent. Call show() to apply the change.
	void resetMaxBrightness();

};	// NeoPixelForZipHalo

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_ZIP_HALO_H
