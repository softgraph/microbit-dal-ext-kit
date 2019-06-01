/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// ZipHalo component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitZipHalo.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	ZipHalo
*/

ZipHalo::ZipHalo()
	: Component("ZipHalo")
{
}

/**	@class	NeoPixelForZipHalo
*/

static const int kNeoPixelLedCount	= 24;

NeoPixelForZipHalo::NeoPixelForZipHalo()
	: NeoPixel("NeoPixelForZipHalo", /* ledPort */ ExtKit::global().p0(), kNeoPixelLedCount)
{
}

}	// microbit_dal_ext_kit
