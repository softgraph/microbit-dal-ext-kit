/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
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

/// @cond static

/// Scroll Parameter
struct ScrollParam
{
	ScrollParam(const ManagedString& s, char c)
		: s(s), c(c)
	{
	}

	ManagedString	s;
	char	c;

};	// ScrollParam

/// @endcond static

static DisplayRotation sDisplayRotation = MICROBIT_DISPLAY_ROTATION_0;
static bool sBackToFront = false;
static int sScrollSpeed = MICROBIT_DEFAULT_SCROLL_SPEED;

static void scrollString(void* /* new */ p);

void setDisplayRotation(DisplayRotation displayRotation, bool backToFront)
{
	sDisplayRotation = displayRotation;
	sBackToFront = backToFront;

	MicroBitDisplay& d = ExtKit::global().display();
	d.rotateTo(displayRotation);
}

DisplayRotation displayRotation()
{
	return sDisplayRotation;
}

bool isBackToFront()
{
	return sBackToFront;
}

bool isUpsideDown()
{
	return sDisplayRotation == MICROBIT_DISPLAY_ROTATION_180;
}

void clear(uint32_t durationInMilliseconds)
{
	MicroBitDisplay& d = ExtKit::global().display();
	if(0 < durationInMilliseconds) {
		MicroBitImage saved = d.screenShot();	d.clear();
		time::sleep(durationInMilliseconds);	d.print(saved);
	}
	else {
		d.clear();
	}
}

void showImage(MicroBitImage image, uint32_t durationInMilliseconds)
{
	MicroBitDisplay& d = ExtKit::global().display();
	if(0 < durationInMilliseconds) {
		MicroBitImage saved = d.screenShot();	d.clear();
		time::sleep(100 /* milliseconds */);	d.print(image);
		time::sleep(durationInMilliseconds);	d.clear();
		time::sleep(100 /* milliseconds */);	d.print(saved);
	}
	else {
		d.print(image);
	}
}

void showChar(char c, uint32_t durationInMilliseconds)
{
	MicroBitDisplay& d = ExtKit::global().display();
	if(0 < durationInMilliseconds) {
		MicroBitImage saved = d.screenShot();	d.clear();
		time::sleep(100 /* milliseconds */);	d.printChar(c);
		time::sleep(durationInMilliseconds);	d.clear();
		time::sleep(100 /* milliseconds */);	d.print(saved);
	}
	else {
		d.printChar(c);
	}
}

void flashChar(char c, uint32_t durationInMilliseconds)
{
	showChar(c, durationInMilliseconds);
}

void setScrollSpeed(int scrollSpeed)
{
	sScrollSpeed = scrollSpeed;
}

void scrollString(const ManagedString& s, char c)
{
	ScrollParam* scrollParam = new ScrollParam(s, c);
	EXT_KIT_ASSERT_OR_PANIC(scrollParam, panic::kOutOfMemory);

	scrollString(scrollParam);
}

void scrollStringAsync(const ManagedString& s, char c)
{
	ScrollParam* scrollParam = new ScrollParam(s, c);
	EXT_KIT_ASSERT_OR_PANIC(scrollParam, panic::kOutOfMemory);

	create_fiber(scrollString, scrollParam);
}

void scrollString(void* /* new */ p)
{
	EXT_KIT_ASSERT(p);

	MicroBitDisplay& d = ExtKit::global().display();
	d.stopAnimation();
	fiber_sleep(1 /* milliseconds */);

	ScrollParam* /* new */ scrollParam = (ScrollParam*) p;
	if(scrollParam->c) {
		d.clear();
		d.scroll(scrollParam->s, sScrollSpeed);
		d.printChar(scrollParam->c);
	}
	else {
		MicroBitImage saved = d.screenShot();
		d.clear();
		d.scroll(scrollParam->s, sScrollSpeed);
		d.print(saved);
	}
	delete scrollParam;
}

/// @cond static

/// Bar Graph for a single digit
typedef char BarGraph[2 * 5];

/// @endcond static

/// Bar Graphs for dighits
static const BarGraph sBarGraph[] = {
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
	{0, 0,
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
	 1, 1},	// 9
	{1, 1,
	 1, 1,
	 1, 1,
	 1, 1,
	 1, 1}	// FULL
};

void showNumber(int twoDigitNumber /* 00-99 */, uint32_t durationInMilliseconds)
{
	int d1;
	int d2;
	if(twoDigitNumber < 0) {
		d1 = 0;		// 0
		d2 = 10;	// FULL
	}
	else if(99 < twoDigitNumber) {
		d1 = 10;	// FULL
		d2 = 10;	// FULL
	}
	else if(twoDigitNumber < 100) {
		d1 = twoDigitNumber / 10;	// 0-9
		d2 = twoDigitNumber % 10;	// 0-9
	}
	const char* p1 = &sBarGraph[d1][0];
	const char* p2 = &sBarGraph[d2][0];
	MicroBitImage image(5,5);
	for (int16_t y = 0; y < 5; y++) {
		image.setPixelValue(0, y, *p1++ ? 1 : 0);
		image.setPixelValue(1, y, *p1++ ? 1 : 0);
		image.setPixelValue(3, y, *p2++ ? 1 : 0);
		image.setPixelValue(4, y, *p2++ ? 1 : 0);
	}
	showImage(image, durationInMilliseconds);
}

void showBits(uint32_t bits /* 0x00000 - 0xfffff */, uint32_t durationInMilliseconds)
{
	MicroBitImage image(5,5);
	for (int16_t x = 4; 0 <= x; x--) {
		for (int16_t y = 4; 1 <= y; y--) {
			image.setPixelValue(x, y, bits & 1 ? 1 : 0);
			bits >>= 1;
		}
		image.setPixelValue(x, 0, 1);
	}
	showImage(image, durationInMilliseconds);
}

/// @cond static

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageHollowSquare,
	1,1,1,1,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidDiamond,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
	0,1,1,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageHollowDiamond,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
	0,1,0,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageLargeX,
	1,0,0,0,1,
	0,1,0,1,0,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1
)

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSmallX,
	0,0,0,0,0,
	0,1,0,1,0,
	0,0,1,0,0,
	0,1,0,1,0,
	0,0,0,0,0
)

/// @endcond static

void showButton(Buttons buttons, uint32_t durationInMilliseconds)
{
	char c = 0;
	const MicroBitImage* image = 0;
	Direction direction = direction::kCenter;
	if(buttons == button::kNone) {
		c = ' ';
	}
	else if(buttons == button::kInvalid) {
		c = '!';
	}
	else if((buttons & button::kLR) == button::kLR) {
		c = 'W';
	}
	else if(buttons & button::kL) {
		c = 'L';
	}
	else if(buttons & button::kR) {
		c = 'R';
	}
	else if(buttons & button::kDirN) {
		direction = direction::kN;
	}
	else if(buttons & button::kDirE) {
		direction = direction::kE;
	}
	else if(buttons & button::kDirS) {
		direction = direction::kS;
	}
	else if(buttons & button::kDirW) {
		direction = direction::kW;
	}
	else if(buttons & button::kStart) {
		image = &sImageSolidDiamond;
	}
	else if(buttons & button::kSelect) {
		image = &sImageHollowDiamond;
	}
	else if(buttons & button::kOption1) {
		c = '1';
	}
	else if(buttons & button::kOption2) {
		c = '2';
	}
	else if(buttons & button::kOption3) {
		c = '3';
	}
	else {
		c = '?';
	}

	if(c) {
		showChar(c, durationInMilliseconds);
	}
	else if(image) {
		showImage(*const_cast<MicroBitImage*>(image), durationInMilliseconds);
	}
	else if(direction != direction::kCenter) {
		showDirection(direction, kAngle, durationInMilliseconds);
	}
}

/// @cond static

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarN,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarNW,
	1,1,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarW,
	0,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarSW,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	1,0,0,0,0,
	1,1,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarS,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarSE,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,1,
	0,0,0,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarE,
	0,0,0,0,0,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarNE,
	0,0,0,1,1,
	0,0,0,0,1,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarNNW,
	1,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarWNW,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarWSW,
	0,0,0,0,0,
	0,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarSSW,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	1,1,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarSSE,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,1,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarESE,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarENE,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageGuideBarNNE,
	0,0,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
)

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleN,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleNW,
	1,1,1,1,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleW,
	0,0,1,0,0,
	0,1,0,0,0,
	1,0,0,0,0,
	0,1,0,0,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleSW,
	0,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,1,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleS,
	0,0,0,0,0,
	0,0,0,0,0,
	1,0,0,0,1,
	0,1,0,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleSE,
	0,0,0,0,0,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,1,1,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleE,
	0,0,1,0,0,
	0,0,0,1,0,
	0,0,0,0,1,
	0,0,0,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageAngleNE,
	0,1,1,1,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,0
)

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowN,
	0,0,1,0,0,
	0,1,1,1,0,
	1,0,1,0,1,
	0,0,1,0,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowNW,
	1,1,1,0,0,
	1,1,0,0,0,
	1,0,1,0,0,
	0,0,0,1,0,
	0,0,0,0,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowW,
	0,0,1,0,0,
	0,1,0,0,0,
	1,1,1,1,1,
	0,1,0,0,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowSW,
	0,0,0,0,1,
	0,0,0,1,0,
	1,0,1,0,0,
	1,1,0,0,0,
	1,1,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowS,
	0,0,1,0,0,
	0,0,1,0,0,
	1,0,1,0,1,
	0,1,1,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowSE,
	1,0,0,0,0,
	0,1,0,0,0,
	0,0,1,0,1,
	0,0,0,1,1,
	0,0,1,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowE,
	0,0,1,0,0,
	0,0,0,1,0,
	1,1,1,1,1,
	0,0,0,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageArrowNE,
	0,0,1,1,1,
	0,0,0,1,1,
	0,0,1,0,1,
	0,1,0,0,0,
	1,0,0,0,0
)

EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleN,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleNW,
	1,1,1,1,0,
	1,1,1,0,0,
	1,1,0,0,0,
	1,0,0,0,0,
	0,0,0,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleW,
	0,0,1,0,0,
	0,1,1,0,0,
	1,1,1,0,0,
	0,1,1,0,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleSW,
	0,0,0,0,0,
	1,0,0,0,0,
	1,1,0,0,0,
	1,1,1,0,0,
	1,1,1,1,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleS,
	0,0,0,0,0,
	0,0,0,0,0,
	1,1,1,1,1,
	0,1,1,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleSE,
	0,0,0,0,0,
	0,0,0,0,1,
	0,0,0,1,1,
	0,0,1,1,1,
	0,1,1,1,1
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleE,
	0,0,1,0,0,
	0,0,1,1,0,
	0,0,1,1,1,
	0,0,1,1,0,
	0,0,1,0,0
)
EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(static const, sImageSolidTriangleNE,
	0,1,1,1,1,
	0,0,1,1,1,
	0,0,0,1,1,
	0,0,0,0,1,
	0,0,0,0,0
)

/// Indices and count for pages
enum PageIndex
{
	kPage0,		///< Page 0
	kPage1,		///< Page 1
	kPageCount	///< Page count
};

/// Indices and count for images
enum ImageIndex
{
	kImageN,		///!< (kPage0) N for MICROBIT_DISPLAY_ROTATION_0
	kImageNW,		///!< (kPage0) NW for MICROBIT_DISPLAY_ROTATION_0
	kImageW,		///!< (kPage0) W for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_90)
	kImageSW,		///!< (kPage0) SW for MICROBIT_DISPLAY_ROTATION_0
	kImageS,		///!< (kPage0) S for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_180)
	kImageSE,		///!< (kPage0) SE for MICROBIT_DISPLAY_ROTATION_0
	kImageE,		///!< (kPage0) E for MICROBIT_DISPLAY_ROTATION_0 (or N for MICROBIT_DISPLAY_ROTATION_270)
	kImageNE,		///!< (kPage0) NE for MICROBIT_DISPLAY_ROTATION_0
	kImageCount,	///!< Image count

	kImageNNW = 0,	///!< (kPage1) NNW for MICROBIT_DISPLAY_ROTATION_0
	kImageWNW,		///!< (kPage1) WNW for MICROBIT_DISPLAY_ROTATION_0
	kImageWSW,		///!< (kPage1) WSW for MICROBIT_DISPLAY_ROTATION_0
	kImageSSW,		///!< (kPage1) SSW for MICROBIT_DISPLAY_ROTATION_0
	kImageSSE,		///!< (kPage1) SSE for MICROBIT_DISPLAY_ROTATION_0
	kImageESE,		///!< (kPage1) ESE for MICROBIT_DISPLAY_ROTATION_0
	kImageENE,		///!< (kPage1) ENE for MICROBIT_DISPLAY_ROTATION_0
	kImageNNE,		///!< (kPage1) NNE for MICROBIT_DISPLAY_ROTATION_0

};	// ImageIndex

/// @endcond static

static const MicroBitImage* sArrowImages[kCountArrowTypes][kPageCount][kImageCount] = {
	{	// [kGuideBar]
		{	// [kPage0]
			&sImageGuideBarN,	// [kImageN]
			&sImageGuideBarNW,	// [kImageNW]
			&sImageGuideBarW,	// [kImageW]
			&sImageGuideBarSW,	// [kImageSW]
			&sImageGuideBarS,	// [kImageS]
			&sImageGuideBarSE,	// [kImageSE]
			&sImageGuideBarE,	// [kImageE]
			&sImageGuideBarNE	// [kImageNE]
		},
		{	// [kPage1]
			&sImageGuideBarNNW,	// [kImageNNW]
			&sImageGuideBarWNW,	// [kImageWNW]
			&sImageGuideBarWSW,	// [kImageWSW]
			&sImageGuideBarSSW,	// [kImageSSW]
			&sImageGuideBarSSE,	// [kImageSSE]
			&sImageGuideBarESE,	// [kImageESE]
			&sImageGuideBarENE,	// [kImageENE]
			&sImageGuideBarNNE	// [kImageNNE]
		}
	},
	{	// [kAngle]
		{	// [kPage0]
			&sImageAngleN,	// [kImageN]
			&sImageAngleNW,	// [kImageNW]
			&sImageAngleW,	// [kImageW]
			&sImageAngleSW,	// [kImageSW]
			&sImageAngleS,	// [kImageS]
			&sImageAngleSE,	// [kImageSE]
			&sImageAngleE,	// [kImageE]
			&sImageAngleNE	// [kImageNE]
		},
		{	// [kPage1]
			0,	// [kImageNNW]
			0,	// [kImageWNW]
			0,	// [kImageWSW]
			0,	// [kImageSSW]
			0,	// [kImageSSE]
			0,	// [kImageESE]
			0,	// [kImageENE]
			0	// [kImageNNE]
		}
	},
	{	// [kArrow]
		{	// [kPage0]
			&sImageArrowN,	// [kImageN]
			&sImageArrowNW,	// [kImageNW]
			&sImageArrowW,	// [kImageW]
			&sImageArrowSW,	// [kImageSW]
			&sImageArrowS,	// [kImageS]
			&sImageArrowSE,	// [kImageSE]
			&sImageArrowE,	// [kImageE]
			&sImageArrowNE	// [kImageNE]
		},
		{	// [kPage1]
			0,	// [kImageNNW]
			0,	// [kImageWNW]
			0,	// [kImageWSW]
			0,	// [kImageSSW]
			0,	// [kImageSSE]
			0,	// [kImageESE]
			0,	// [kImageENE]
			0	// [kImageNNE]
		}
	},
	{	// [kSolidTriangle]
		{	// [kPage0]
			&sImageSolidTriangleN,	// [kImageN]
			&sImageSolidTriangleNW,	// [kImageNW]
			&sImageSolidTriangleW,	// [kImageW]
			&sImageSolidTriangleSW,	// [kImageSW]
			&sImageSolidTriangleS,	// [kImageS]
			&sImageSolidTriangleSE,	// [kImageSE]
			&sImageSolidTriangleE,	// [kImageE]
			&sImageSolidTriangleNE	// [kImageNE]
		},
		{	// [kPage1]
			0,	// [kImageNNW]
			0,	// [kImageWNW]
			0,	// [kImageWSW]
			0,	// [kImageSSW]
			0,	// [kImageSSE]
			0,	// [kImageESE]
			0,	// [kImageENE]
			0	// [kImageNNE]
		}
	}
};

void showDirection(Direction direction, ArrowType arrowType, uint32_t durationInMilliseconds)
{
	bool backToFront = isBackToFront();
	char c = 0;
	const MicroBitImage* image = 0;
	PageIndex pageIndex = kPage0;
	int /* ImageIndex */ imageIndex = -1;
	switch(direction) {
		case direction::kCenter: {
			c = ' ';
			break;
		}
		case direction::kN: {
			imageIndex = backToFront ? kImageS : kImageN;
			break;
		}
		case direction::kE: {
			imageIndex = backToFront ? kImageW : kImageE;
			break;
		}
		case direction::kW: {
			imageIndex = backToFront ? kImageE : kImageW;
			break;
		}
		case direction::kS: {
			imageIndex = backToFront ? kImageN : kImageS;
			break;
		}
		case direction::kNE: {
			imageIndex = backToFront ? kImageSW : kImageNE;
			break;
		}
		case direction::kNW: {
			imageIndex = backToFront ? kImageSE : kImageNW;
			break;
		}
		case direction::kSE: {
			imageIndex = backToFront ? kImageNW : kImageSE;
			break;
		}
		case direction::kSW: {
			imageIndex = backToFront ? kImageNE : kImageSW;
			break;
		}
		case direction::kLF: {
			pageIndex = kPage1;
			imageIndex = backToFront ? kImageESE : kImageWNW;
			break;
		}
		case direction::kLB: {
			pageIndex = kPage1;
			imageIndex = backToFront ? kImageENE : kImageWSW;
			break;
		}
		case direction::kRF: {
			pageIndex = kPage1;
			imageIndex = backToFront ? kImageWSW : kImageENE;
			break;
		}
		case direction::kRB: {
			pageIndex = kPage1;
			imageIndex = backToFront ? kImageWNW : kImageESE;
			break;
		}
		case direction::kStop: {
			image = &sImageSmallX;
			break;
		}
		case direction::kInvalid: {
			c = '!';
			break;
		}
		default: {
			c = '?';
			break;
		}
	}

	if(c) {
		showChar(c, durationInMilliseconds);
	}
	else if(image) {
		showImage(*const_cast<MicroBitImage*>(image), durationInMilliseconds);
	}
	else if(0 <= imageIndex) {
		image = sArrowImages[arrowType][pageIndex][imageIndex];
		if(image) {
			showImage(*const_cast<MicroBitImage*>(image), durationInMilliseconds);
		}
	}
}

}	// display
}	// microbit_dal_ext_kit
