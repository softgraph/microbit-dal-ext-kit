/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// ZipHalo component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitZipHalo.h"	// self
#include "ExtKit_System.h"

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

static MicroBitPin& sNeoPixelPort	= gP0;	// digital output port for NeoPixel
static const int kNeoPixelLedCount	= 24;
static const NeoPixel::MaxBrightness kMaxBrightnessDefault	= 100;

/* Component */ bool NeoPixelForZipHalo::isConfigured()
{
	return NeoPixel::isConfigured() && feature::isConfigured(kFeature);
}

NeoPixelForZipHalo::NeoPixelForZipHalo()
	: NeoPixel("NeoPixelForZipHalo", /* digitalPort */ sNeoPixelPort, kNeoPixelLedCount)
{
	setMaxBrightness(kMaxBrightnessDefault);
}

void NeoPixelForZipHalo::resetMaxBrightness()
{
	setMaxBrightness(kMaxBrightnessDefault);
}

}	// microbit_dal_ext_kit
