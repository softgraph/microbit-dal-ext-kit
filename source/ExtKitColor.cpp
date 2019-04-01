/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Color utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitColor.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	Color
	@reference	Color Names
		- https://en.wikipedia.org/wiki/Web_colors
		- https://en.wikipedia.org/wiki/Web_colors#HTML_color_names
		- https://en.wikipedia.org/wiki/Web_colors#CSS_colors
*/

/**
	Hue: 0°, Saturation: 0%, Brightness: 100%
*/
const Color Color::white		= { 0xFFFFFF };

/**
	Hue: 0°, Saturation: 0%, Brightness: 75%
*/
const Color Color::silver		= { 0xC0C0C0 };

/**
	Hue: 0°, Saturation: 0%, Brightness: 50%
*/
const Color Color::gray			= { 0x808080 };

/**
	Hue: 0°, Saturation: 0%, Brightness: 0%
*/
const Color Color::black		= { 0x000000 };

/**
	Hue: 0°, Saturation: 100%, Brightness: 100%
*/
const Color Color::red			= { 0xFF0000 };

/**
	Hue: 0°, Saturation: 100%, Brightness: 50%
*/
const Color Color::maroon		= { 0x800000 };

/**
	Hue: 38°, Saturation: 100%, Brightness: 100%
*/
const Color Color::orange		= { 0xffa500 };

/**
	Hue: 60°, Saturation: 100%, Brightness: 100%
*/
const Color Color::yellow		= { 0xFFFF00 };

/**
	Hue: 60°, Saturation: 100%, Brightness: 50%
*/
const Color Color::olive		= { 0x808000 };

/**
	Hue: 120°, Saturation: 100%, Brightness: 100%
*/
const Color Color::lime			= { 0x00FF00 };

/**
	Hue: 120°, Saturation: 100%, Brightness: 50%
*/
const Color Color::green		= { 0x008000 };

/**
	Hue: 180°, Saturation: 100%, Brightness: 100%
*/
const Color Color::aqua			= { 0x00FFFF };

/**
	Hue: 180°, Saturation: 100%, Brightness: 50%
*/
const Color Color::teal			= { 0x008080 };

/**
	Hue: 240°, Saturation: 100%, Brightness: 100%
*/
const Color Color::blue			= { 0x0000FF };

/**
	Hue: 240°, Saturation: 100%, Brightness: 50%
*/
const Color Color::navy			= { 0x000080 };

/**
	Hue: 300°, Saturation: 100%, Brightness: 100%
*/
const Color Color::fuchsia		= { 0xFF00FF };

/**
	Hue: 300°, Saturation: 100%, Brightness: 50%
*/
const Color Color::purple		= { 0x800080 };

Color::Color(uint16_t /* 360 */ whole, uint16_t /* hue level (e.g., 0-359) */ h, uint8_t /* saturation level */ s, uint8_t /* value (brightness) level */ v)
{
	static const uint16_t countOfPiece = 6;

	if(s == 0) {
		// grayscale
		mRGB = (v << 16) + (v << 8) + v;
		return;
	}

	uint16_t piece	= whole / countOfPiece;
	EXT_KIT_ASSERT((piece * countOfPiece) == whole);

	h %= whole;		// normalize h

	uint16_t region	= h / piece;
	EXT_KIT_ASSERT(region < countOfPiece);

	uint16_t hh		= h - (piece * region);
	hh = hh * 0x100 / piece;	// scale to 0-0xff

	uint8_t p		= 0xff - s;
	uint8_t q		= 0xff - ((s * hh) >> 8);
	uint8_t t		= 0xff - ((s * (0xff - hh)) >> 8);
	p = (p * v) >> 8;
	q = (q * v) >> 8;
	t = (t * v) >> 8;

	switch(region) {
		default:
		case 0:		mRGB = (v << 16) + (t << 8) + p;		break;	// v (r) + t + p
		case 2:		mRGB = (p << 16) + (v << 8) + t;		break;	// v (g) + t + p
		case 4:		mRGB = (t << 16) + (p << 8) + v;		break;	// v (b) + t + p
		case 1:		mRGB = (q << 16) + (v << 8) + p;		break;	// v (g) + p + q
		case 3:		mRGB = (p << 16) + (q << 8) + v;		break;	// v (b) + p + q
		case 5:		mRGB = (v << 16) + (p << 8) + q;		break;	// v (r) + p + q
	}
}

}	// microbit_dal_ext_kit
