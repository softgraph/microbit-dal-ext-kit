/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Color utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_COLOR_H
#define EXT_KIT_COLOR_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Color
struct Color
{
public:
	// Well known color names

	/// CSS 1 & BW Color White
	static const Color white;

	/// CSS 1 Color Silver
	static const Color silver;

	/// CSS 1 Color Gray
	static const Color gray;

	/// CSS 1 & BW Color Black
	static const Color black;

	/// CSS 1 & RGB Color Red
	static const Color red;

	/// CSS 1 Color Maroon
	static const Color maroon;

	/// CSS 2.1 Color Orange
	static const Color orange;

	/// CSS 1 & CMY Color Yellow
	static const Color yellow;

	/// CSS 1 Color Olive
	static const Color olive;

	/// CSS 1 & RGB Color Lime (Green in RGB)
	static const Color lime;

	/// CSS 1 Color Green
	static const Color green;

	/// CSS 1 & CMY Color Aqua (Cyan in CMY)
	static const Color aqua;

	/// CSS 1 Color Teal
	static const Color teal;

	/// CSS 1 & RGB Color Blue
	static const Color blue;

	/// CSS 1 Color Navy
	static const Color navy;

	/// CSS 1 & CMY Color Fuchsia (Magenta in CMY)
	static const Color fuchsia;

	/// CSS 1 Color Purple
	static const Color purple;

	/// Constructor
	inline Color() {
		mRGB = 0;	// black
	}

	/// Constructor with a rgb color
	inline Color(uint32_t rgb) {
		mRGB = rgb;
	}

	/// Constructor with rgb color components
	inline Color(uint8_t /* red level */ r, uint8_t /* green level */ g, uint8_t /* blue level */ b) {
		mRGB = (r << 16) + (g << 8) + b;
	}

	/// Constructor with hsv color components
	Color(uint16_t /* 360 */ whole, uint16_t /* hue level (e.g., 0-359) */ h, uint8_t /* saturation level */ s, uint8_t /* value (brightness) level */ v);

	/// Get red color component of rgb
	inline uint8_t /* red level */ r() const {
		return (uint8_t) (mRGB >> 16);
	}

	/// Get green color component of rgb
	inline uint8_t /* green level */ g() const {
		return (uint8_t) (mRGB >> 8);
	}

	/// Get blue color component of rgb
	inline uint8_t /* blue level */ b() const {
		return (uint8_t) mRGB;
	}

private:
	/// Color representation in rgb
	uint32_t mRGB;

};	// Color

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_COLOR_H
