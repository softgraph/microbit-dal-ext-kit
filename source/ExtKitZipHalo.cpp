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

static const Features kFeature = feature::kZipHalo;

/* Component */ bool ZipHalo::isConfigured()
{
	return feature::isConfigured(kFeature);
}

ZipHalo::ZipHalo()
	: Component("ZipHalo")
{
}

/**	@class	NeoPixelForZipHalo
*/

static const int kNeoPixelLedCount	= 24;
static const NeoPixel::MaxBrightness kMaxBrightnessDefault	= 10;

/* Component */ bool NeoPixelForZipHalo::isConfigured()
{
	return NeoPixel::isConfigured() && feature::isConfigured(kFeature);
}

NeoPixelForZipHalo::NeoPixelForZipHalo()
	: NeoPixel("NeoPixelForZipHalo", /* digitalPort */ ExtKit::global().p0(), kNeoPixelLedCount)
{
	setMaxBrightness(kMaxBrightnessDefault);
}

void NeoPixelForZipHalo::resetMaxBrightness()
{
	setMaxBrightness(kMaxBrightnessDefault);
}

}	// microbit_dal_ext_kit
