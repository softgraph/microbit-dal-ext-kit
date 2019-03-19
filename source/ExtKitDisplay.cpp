/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Display utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitDisplay.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace display {

typedef char	Graph[2 * 5];

static const Graph sBarGraph[] = {
	{0, 0,
	 0, 0,
	 0, 0,
	 0, 0,
	 0, 0},	// 0
	{0, 0,
	 0, 0,
	 0, 0,
	 0, 0,
	 0, 1},	// 1
	{0, 0,
	 0, 0,
	 0, 0,
	 0, 0,
	 1, 1},	// 2
	{0, 0,
	 0, 0,
	 0, 0,
	 0, 1,
	 1, 1},	// 3
	{0, 0,
	 0, 0,
	 0, 0,
	 1, 1,
	 1, 1},	// 4
	{0, 0,
	 0, 0,
	 0, 1,
	 1, 1,
	 1, 1},	// 5
	{0, 01,
	 0, 0,
	 1, 1,
	 1, 1,
	 1, 1},	// 6
	{0, 0,
	 0, 1,
	 1, 1,
	 1, 1,
	 1, 1},	// 7
	{0, 0,
	 1, 1,
	 1, 1,
	 1, 1,
	 1, 1},	// 8
	{0, 1,
	 1, 1,
	 1, 1,
	 1, 1,
	 1, 1}	// 9
};

static bool sIsUpsideDown = false;

void setUpsideDown()
{
	sIsUpsideDown = true;
	MicroBitDisplay& d = ExtKit::global().display();
	d.rotateTo(MICROBIT_DISPLAY_ROTATION_180);
}

bool isUpsideDown()
{
	return sIsUpsideDown;
}

void clear()
{
	MicroBitDisplay& d = ExtKit::global().display();
	d.clear();
}

void showChar(char c)
{
	MicroBitDisplay& d = ExtKit::global().display();
	d.printChar(c);
}

void flashChar(char c, uint32_t durationInMilliseconds)
{
	MicroBitDisplay& d = ExtKit::global().display();
	MicroBitImage saved = d.screenShot();
	d.clear();		time::sleep(100 /* milliseconds */);
	d.printChar(c);	time::sleep(durationInMilliseconds);
	d.clear();		time::sleep(100 /* milliseconds */);
	d.print(saved);
}

void scrollString(const ManagedString& s)
{
	MicroBitDisplay& d = ExtKit::global().display();
	MicroBitImage saved = d.screenShot();
	d.scroll(s);
	d.print(saved);
}

void showNumber(int twoDigitNumber /* 00-99 */)
{
	MicroBitDisplay& d = ExtKit::global().display();
	twoDigitNumber = numeric::clamp(0, 99, twoDigitNumber);
	const char* p1 = &sBarGraph[twoDigitNumber / 10][0];
	const char* p2 = &sBarGraph[twoDigitNumber % 10][0];
	MicroBitImage image(5,5);
	for (int16_t y = 0; y < 5; y++) {
		image.setPixelValue(0, y, *p1++ ? 1 : 0);
		image.setPixelValue(1, y, *p1++ ? 1 : 0);
		image.setPixelValue(3, y, *p2++ ? 1 : 0);
		image.setPixelValue(4, y, *p2++ ? 1 : 0);
	}
	d.print(image);
}

void showBits(uint32_t bits /* 0x00000 - 0xfffff */)
{
	MicroBitDisplay& d = ExtKit::global().display();
	MicroBitImage image(5,5);
	for (int16_t x = 4; 0 <= x; x--) {
		for (int16_t y = 4; 1 <= y; y--) {
			image.setPixelValue(x, y, bits & 1 ? 1 : 0);
			bits >>= 1;
		}
		image.setPixelValue(x, 0, 1);
	}
	d.print(image);
}

void showButton(Buttons buttons)
{
	MicroBitDisplay& d = ExtKit::global().display();
	if(buttons == button::kNone)					{ d.clear(); }
	else if(buttons == button::kInvalid)			{ d.printChar('!'); }
	else if((buttons & button::kLR) == button::kLR)	{ d.printChar('W'); }
	else if(buttons & button::kL)					{ d.printChar('L'); }
	else if(buttons & button::kR)					{ d.printChar('R'); }
	else if(buttons & button::kA)					{ d.printChar('A'); }
	else if(buttons & button::kB)					{ d.printChar('B'); }
	else if(buttons & button::kC)					{ d.printChar('C'); }
	else if(buttons & button::kD)					{ d.printChar('D'); }
	else if(buttons & button::kE)					{ d.printChar('E'); }
	else if(buttons & button::kF)					{ d.printChar('F'); }
	else if(buttons & button::kG)					{ d.printChar('G'); }
	else if(buttons & button::kH)					{ d.printChar('H'); }
	else											{ d.printChar('?'); }
}

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirN,		0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirE,		0,0,0,0,0, 0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirW,		0,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirS,		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirNE,	0,0,0,1,1, 0,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirNW,	1,1,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirSE,	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 0,0,0,1,1)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirSW,	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 1,1,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirLF,	1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirLB,	0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirRF,	0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, imageDirRB,	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,1)

void showDirection(Direction direction)
{
	MicroBitDisplay& d = ExtKit::global().display();
	switch(direction) {
		case direction::kCenter:	d.clear();				break;
		case direction::kN:			d.print(imageDirN);		break;
		case direction::kE:			d.print(imageDirE);		break;
		case direction::kW:			d.print(imageDirW);		break;
		case direction::kS:			d.print(imageDirS);		break;
		case direction::kNE:		d.print(imageDirNE);	break;
		case direction::kNW:		d.print(imageDirNW);	break;
		case direction::kSE:		d.print(imageDirSE);	break;
		case direction::kSW:		d.print(imageDirSW);	break;
		case direction::kLF:		d.print(imageDirLF);	break;
		case direction::kLB:		d.print(imageDirLB);	break;
		case direction::kRF:		d.print(imageDirRF);	break;
		case direction::kRB:		d.print(imageDirRB);	break;
		case direction::kInvalid:	d.printChar('!');		break;
		default:					d.printChar('?');		break;
	}
}

}	// display
}	// microbit_dal_ext_kit
