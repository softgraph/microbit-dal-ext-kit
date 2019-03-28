/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// TouchPiano component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitTouchPiano.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	TouchPiano
	@sa	Waveshare TouchPiano WSTouchPiano.ts (MIT License)
		- https://github.com/waveshare/TouchPiano
		- https://github.com/waveshare/TouchPiano/blob/master/WSTouchPiano.ts
*/

static const Features kFeature = feature::kTouchPiano;
static const int kI2cAddress	= 0x57 << 1;

/* Component */ Features TouchPiano::avaiableFeatures()
{
	char buf[2];
	int ret = ExtKit::global().i2c().read(kI2cAddress, buf, (int) sizeof(buf));
	return (ret == MICROBIT_OK) ? kFeature : 0;
}

/* Component */ bool TouchPiano::isConfigured()
{
	return feature::isConfigured(kFeature);
}

TouchPiano::TouchPiano()
	: Component("TouchPiano")
{
}

void TouchPiano::read(PianoKeys* /* OUT */ outKeys)
{
	char buf[2];
	int ret = ExtKit::global().i2c().read(kI2cAddress, buf, (int) sizeof(buf));
	*outKeys = (ret == MICROBIT_OK) ? buf[0] + (buf[1] << 8) : 0;
}

/**	@class	NeoPixelForTouchPiano
*/

static const int kNeoPixelLedCount	= 4;
static const NeoPixel::MaxBrightness kMaxBrightnessDefault = 10;

/* Component */ bool NeoPixelForTouchPiano::isConfigured()
{
	return NeoPixel::isConfigured() && feature::isConfigured(kFeature);
}

NeoPixelForTouchPiano::NeoPixelForTouchPiano()
	: NeoPixel("NeoPixelForTouchPiano", /* digitalPort */ ExtKit::global().p1(), kNeoPixelLedCount)
{
	setMaxBrightness(kMaxBrightnessDefault);
}

/* NeoPixel */ void NeoPixelForTouchPiano::fillColorWithRainbow()
{
	static const Color rainbowPattern[kNeoPixelLedCount] = {
		Color::white,
		Color::lime,
		Color::red,
		Color::blue
	};

	for(int i = 0; i < kNeoPixelLedCount; i++) {
		setColor(i, rainbowPattern[i]);
	}
	show();
}

void NeoPixelForTouchPiano::fillColorWithIndicatorRange(int indicatorRange /* 0-7 */)
{
	static const uint8_t indicatorPattern[8] = {
		0x0,	// [0] 0000b
		0x8,	// [1] 1000b
		0xc,	// [2] 1100b
		0x4,	// [3] 0100b
		0x6,	// [4] 0110b
		0x2,	// [5] 0010b
		0x3,	// [6] 0011b
		0x1		// [7] 0001b
	};

	indicatorRange = numeric::clamp(0, 7, indicatorRange);
	uint8_t pattern = indicatorPattern[indicatorRange];
	fillColorWithIndicatorPattern(pattern);
	show();
}

/**	@class	BuzzerForTouchPiano
*/

BuzzerForTouchPiano::BuzzerForTouchPiano()
	: Buzzer("BuzzerForTouchPiano", /* analogPort */ ExtKit::global().p0())
{
}

}	// microbit_dal_ext_kit
