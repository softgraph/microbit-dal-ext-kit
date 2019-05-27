/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// NeoPixel component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_NEO_PIXEL_H
#define EXT_KIT_NEO_PIXEL_H

#include "ExtKitColor.h"
#include "ExtKitComponent.h"
#include "ExtKitDirection.h"

class MicroBitPin;

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for a generic LED Strip using WS2812B modules also known as NeoPixel
class NeoPixel : public Component
{
public:
	/// Max brightness value in percent
	typedef int	MaxBrightness;

	/// The lowest value for max brightness
	static const MaxBrightness kMaxBrightnessLowest = 5;

	/// No limit value for max brightness
	static const MaxBrightness kMaxBrightnessNoLimit = 100;

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor with a digital port and a led count
	NeoPixel(const char* name, MicroBitPin& ledPort, int ledCount);

	/// Destructor
	~NeoPixel();

	/// Apply the current colors and max brightness to the LED strip
	void show();

	/// Set max brightness value in percent. Call show() to apply the change.
	void setMaxBrightness(MaxBrightness limit);

	/// Change max brightness value in percent. Call show() to apply the change.
	void changeMaxBrightness(int offset);

	/// Get max brightness value in percent
	MaxBrightness maxBrightness();

	/// Fill all led modules with a color. Call show() to apply the change.
	void fillColor(Color color);

	/// Fill all led modules with a rainbow color pattern. Call show() to apply the change.
	void fillColorWithRainbow();

	/// Set a color to a led module. Call show() to apply the change.
	void setColor(int index, Color color);

	/// Get a color from a led module. Call show() to apply the change.
	Color color(int index);

	/// Rotate led modules left. Call show() to apply the change.
	void rotateLeft();

	/// Rotate led modules right. Call show() to apply the change.
	void rotateRight();

	/// Set a color map for a indicator. Call show() to apply the change.
	void setColorMapForIndicator(Color colorOff, Color colorOn);

	/// Fill all led modules using a indicator pattern
	void fillColorWithIndicatorPattern(uint32_t indicatorPattern);

	/// Set a color map for a focus. Call show() to apply the change.
	void setColorMapForFocus(Color colorOff, Color colorOn1, Color colorOn2, Color colorOn3);

	/// Set a rainbow map for a focus. Call show() to apply the change
	void setRainbowMapForFocus();

	/// Fill all led modules using a focus direction
	void fillColorWithFocusDirection(Direction focusDirection);

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

	/// Fill Color Directly
	void fillColorDirectly(Color color);

	/// Set Color Directly
	void setColorDirectly(int index, Color color);

	/// Fill Color Using Color Mode
	void fillColorUsingColorMode();

	/// Dump Pin
	void debug_dumpPin(MicroBitPin* pin);

	/// Color Mode
	enum ColorMode {
		kManual,				///< Manual Color (No Mode)
		kColorMapForIndicator,	///< Use Specified Color Map for Indicator
		kColorMapForFocus,		///< Use Specified Color Map for Focus
		kRainbowMapForFocus		///< Use Rainbow Map for Focus
	};

	/// Led Port
	MicroBitPin&	mLedPort;

	/// Led Count
	int				mLedCount;

	/// Led Hue Unit
	int 			mLedHueUnit;

	/// Led Bufer Length
	int				mLedBufferLength;

	/// Led Bufer
	uint8_t*		mLedBuffer;

	/// Max Brightness
	MaxBrightness	mMaxBrightness;

	/// Color Mode
	ColorMode		mColorMode;

	/// Color Map for Color Mode `kColorMapForIndicator` or `kColorMapForFocus`
	Color			mColorMap[4];

	/// Indicator Pattern for Color Mode `kColorMapForIndicator`
	uint32_t		mIndicatorPattern;

	/// Focus Direction for Color Mode `kColorMapForFocus` or `kRainbowMapForFocus`
	Direction		mFocusDirection;

};	// NeoPixel

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_NEO_PIXEL_H
