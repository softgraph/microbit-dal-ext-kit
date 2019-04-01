/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// NeoPixel component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitNeoPixel.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	NeoPixel
	@reference	Microsoft pxt-ws2812b sendBuffer.asm (MIT license)
		- https://makecode.microbit.org/pkg/Microsoft/pxt-ws2812b
		- https://github.com/Microsoft/pxt-ws2812b
		- https://github.com/Microsoft/pxt-ws2812b/blob/master/sendBuffer.asm
*/

static const Features kFeature = feature::kNeoPixel;

static const int kBytesPerLed = 3;	// bytes per one led module

static const uint8_t* sendBuffer(MicroBitPin* pin, const uint8_t* buf, int len);

/* Component */ bool NeoPixel::isConfigured()
{
	return feature::isConfigured(kFeature);
}

NeoPixel::NeoPixel(const char* name, MicroBitPin& digitalPort, int ledCount)
	: Component(name)
	, mLedPort(digitalPort)
	, mLedCount(0)
	, mLedHueUnit(0)
	, mLedBufferLength(0)
	, mLedBuffer(0)
	, mMaxBrightness(NeoPixel::kMaxBrightnessNoLimit)
	, mColorMode(kManual)
	, mIndicatorPattern(0)
	, mFocusDirection(direction::kInvalid)
{
	EXT_KIT_ASSERT(0 < ledCount);

	mLedPort.setDigitalValue(0);	// configure the port for digital output
	wait_us(50);					// 50 us is required to reset LED modules

//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::NeoPixel");

//	debug_sendLine(EXT_KIT_DEBUG_INFO "NeoPixel::mLedPort");
//	debug_dumpPin(&mLedPort);

	mLedCount = ledCount;
	mLedHueUnit = 360 / ledCount;
	mLedBufferLength = ledCount * kBytesPerLed;
	mLedBuffer = new uint8_t[mLedBufferLength * 2];	// consists of two buffers with and without brightness control
	EXT_KIT_ASSERT_OR_PANIC(mLedBuffer, kPanicOutOfMemory);
}

NeoPixel::~NeoPixel()
{
	delete mLedBuffer;
}

/* Component */ void NeoPixel::doStart()
{
	fillColor(Color::black);
	show();
}

void NeoPixel::show()
{
	uint8_t* src = &mLedBuffer[0];
	uint8_t* dst = &mLedBuffer[mLedBufferLength];
	for(int i = 0; i < mLedCount; i++) {
		uint8_t g	= *src++;
		uint8_t r	= *src++;
		uint8_t b	= *src++;
		uint32_t power = g + r + b;	// range: 0 - 765
		uint32_t maxPower = 0xFF * 3 * mMaxBrightness / kMaxBrightnessNoLimit;
		if(maxPower < power) {
			if(0 < g) {
				g = g * maxPower / power;
				if(g == 0) {
					g = 1;
				}
			}
			if(0 < r) {
				r = r * maxPower / power;
				if(r == 0) {
					r = 1;
				}
			}
			if(0 < b) {
				b = b * maxPower / power;
				if(b == 0) {
					b = 1;
				}
			}
		}
		*dst++ = g;
		*dst++ = r;
		*dst++ = b;
	}

//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::show");

//	debug_sendLine(EXT_KIT_DEBUG_INFO "NeoPixel::mLedBuffer");
//	debug_sendMemoryDump(&mLedBuffer[0], mLedBufferLength);
//	debug_sendMemoryDump(&mLedBuffer[mLedBufferLength], mLedBufferLength);

//	debug_sendLine(EXT_KIT_DEBUG_INFO "NeoPixel::mLedPort");
//	debug_dumpPin(&mLedPort);

	sendBuffer(&mLedPort, &mLedBuffer[mLedBufferLength], mLedBufferLength);
}

void NeoPixel::setMaxBrightness(NeoPixel::MaxBrightness limit)
{
	mMaxBrightness = numeric::clamp(kMaxBrightnessLowest, kMaxBrightnessNoLimit, limit);
}

void NeoPixel::changeMaxBrightness(int offset)
{
	setMaxBrightness(mMaxBrightness + offset);
}

NeoPixel::MaxBrightness NeoPixel::maxBrightness()
{
	return mMaxBrightness;
}

void NeoPixel::fillColor(Color color)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::fillColor");

	fillColorDirectly(color);
	mColorMode = kManual;
}

void NeoPixel::fillColorDirectly(Color color)
{
	const uint8_t g	= color.g();
	const uint8_t r	= color.r();
	const uint8_t b	= color.b();
	uint8_t* p = mLedBuffer;
	for(int i = 0; i < mLedCount; i++) {
		*p++ = g;
		*p++ = r;
		*p++ = b;
	}
}

void NeoPixel::fillColorWithRainbow()
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::fillColorWithRainbow");

	for(int i = 0; i < mLedCount; i++) {
		setColorDirectly(i, Color(360, mLedHueUnit * i, 0xff, 0xff));
	}
	mColorMode = kManual;
}

void NeoPixel::setColor(int index, Color color)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::setColor");

	setColorDirectly(index, color);
	mColorMode = kManual;
}

void NeoPixel::setColorDirectly(int index, Color color)
{
	EXT_KIT_ASSERT(0 <= index);
	EXT_KIT_ASSERT(index < mLedCount);

	uint8_t* p = &mLedBuffer[index * kBytesPerLed];
	*p++ = color.g();
	*p++ = color.r();
	*p++ = color.b();
}

Color NeoPixel::color(int index)
{
	EXT_KIT_ASSERT(0 <= index);
	EXT_KIT_ASSERT(index < mLedCount);

	uint8_t* p = &mLedBuffer[index * kBytesPerLed];
	uint8_t g = *p++;
	uint8_t r = *p++;
	uint8_t b = *p++;
	return Color(r, g, b);
}

void NeoPixel::rotateLeft()
{
	if(mLedCount <= 1) {
		return;
	}

	uint8_t* src = &mLedBuffer[0];
	uint8_t* dst = &mLedBuffer[0];
	const uint8_t v1 = *src++;
	const uint8_t v2 = *src++;
	const uint8_t v3 = *src++;
	for(int i = 1; i < mLedCount; i++) {
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
	}
	*dst++ = v1;
	*dst++ = v2;
	*dst++ = v3;
}

void NeoPixel::rotateRight()
{
	if(mLedCount <= 1) {
		return;
	}

	uint8_t* src = &mLedBuffer[mLedBufferLength];
	uint8_t* dst = &mLedBuffer[mLedBufferLength];
	const uint8_t v1 = *(--src);
	const uint8_t v2 = *(--src);
	const uint8_t v3 = *(--src);
	for(int i = 1; i < mLedCount; i++) {
		*(--dst) = *(--src);
		*(--dst) = *(--src);
		*(--dst) = *(--src);
	}
	*(--dst) = v1;
	*(--dst) = v2;
	*(--dst) = v3;
}

void NeoPixel::setColorMapForIndicator(Color colorOff, Color colorOn)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::setColorMapForIndicator");

	mColorMap[0] = colorOff;
	mColorMap[1] = colorOn;
	mColorMap[2] = colorOn;
	mColorMap[3] = colorOn;
	mColorMode = kColorMapForIndicator;
	fillColorUsingColorMode();
}

void NeoPixel::fillColorWithIndicatorPattern(uint32_t indicatorPattern)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::fillColorWithIndicatorPattern: 0x", string::hex(indicatorPattern).toCharArray());

	mIndicatorPattern = indicatorPattern;
	fillColorUsingColorMode();
}

void NeoPixel::setColorMapForFocus(Color colorOff, Color colorOn1, Color colorOn2, Color colorOn3)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::setColorMapForFocus");

	mColorMap[0] = colorOff;
	mColorMap[1] = colorOn1;
	mColorMap[2] = colorOn2;
	mColorMap[3] = colorOn3;
	mColorMode = kColorMapForFocus;
	fillColorUsingColorMode();
}

void NeoPixel::setRainbowMapForFocus()
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::setRainbowMapForFocus");

	mColorMode = kRainbowMapForFocus;
	fillColorUsingColorMode();
}

void NeoPixel::fillColorWithFocusDirection(Direction focusDirection)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "NeoPixel::fillColorWithFocusDirection: 0x", string::hex(focusDirection).toCharArray());

	mFocusDirection = focusDirection;
	fillColorUsingColorMode();
}

void NeoPixel::fillColorUsingColorMode()
{
	if(mColorMode == kColorMapForIndicator) {
		uint32_t indicatorPattern = mIndicatorPattern;
		if(0 < mLedCount) {
			for(int i = mLedCount - 1; 0 <= i; i--) {
				setColorDirectly(i, indicatorPattern & 1 ? mColorMap[1] : mColorMap[0]);
				indicatorPattern >>= 1;
			}
		}
	}
	else if((mColorMode == kColorMapForFocus) || (mColorMode == kRainbowMapForFocus)) {
		int offset = -1;
		switch(mFocusDirection) {
			case direction::kN:		{
				offset = 0;
				break;
			}
			case direction::kLF:
			case direction::kNE:	{
				offset = 3;
				break;
			}
			case direction::kE:		{
				offset = 6;
				break;
			}
			case direction::kLB:
			case direction::kSE:	{
				offset = 9;
				break;
			}
			case direction::kS:		{
				offset = 12;
				break;
			}
			case direction::kRB:
			case direction::kSW:	{
				offset = 15;
				break;
			}
			case direction::kW:		{
				offset = 18;
				break;
			}
			case direction::kRF:
			case direction::kNW:	{
				offset = 21;
				break;
			}
		}
		if(mColorMode == kColorMapForFocus) {
			fillColorDirectly(mColorMap[0]);
			if(0 < offset) {
				setColorDirectly(offset - 1,	mColorMap[1]);
				setColorDirectly(offset,		mColorMap[2]);
				setColorDirectly(offset + 1,	mColorMap[3]);
			}
			else if(offset == 0) {
				setColorDirectly(23,			mColorMap[1]);
				setColorDirectly(0,				mColorMap[2]);
				setColorDirectly(1,				mColorMap[3]);
			}
		}
		else {	// (mColorMode == kRainbowMapForFocus)
			if(0 <= offset) {
				for(int i = 0; i < mLedCount; i++) {
					setColorDirectly(i, Color(360, mLedHueUnit * (i + 24 - offset), 0xff, 0xff));
				}
			}
		}
	}
}

void NeoPixel::debug_dumpPin(MicroBitPin* pin)
{
	debug_sendMemoryDump(pin, sizeof(MicroBitPin) /* 16 */);
	void** array = (void**) pin;
	debug_sendMemoryDump(array[2], sizeof(DigitalOut) /* 24 */);
}

/*
	An output example of NeoPixel::debug_dumpPin() for P1
*/

//	ec 21 00 20:  78 32 02 00  08 00 02 00  e8 29 00 20  0f 01 02 00

#if 0
#include "MicroBitComponent.h"
	class MicroBitComponent {
		void*			vtable;		// [0] 78 32 02 00
		uint16_t		id;			// [4] 08 00 (MICROBIT_ID_IO_P1)
		uint8_t			status;		// [6] 02    (IO_STATUS_DIGITAL_OUT)
									// [7] 00    (padding)
	};								// [8]

#include "TARGET_MCU_NRF51822/TARGET_NRF51_MICROBIT/PinNames.h"
#include "MicroBitPin.h"
	class MicroBitPin : public MicroBitComponent {
		void*			pin;		// [8]  e8 29 00 20 (DigitalOut*)
		PinCapability	capability;	// [12] 0f    (PIN_CAPABILITY_ALL)
		uint8_t			pullMode;	// [13] 01     (PullDown)
		PinName			name;		// [14] 02 00 (MICROBIT_PIN_P1=P0_2=p2)
	};								// [16]
#endif	// 0

//	e8 29 00 20:  02 00 00 00  04 00 00 00  14 05 00 50  08 05 00 50
//	f8 29 00 20:  0c 05 00 50  10 05 00 50

#if 0
#include "TARGET_MCU_NRF51822/gpio_object.h"
	typedef struct {
		PinName			pin;		// [0]  02 00 (MICROBIT_PIN_P1=P0_2=p2)
									// [2]  00 00 (padding)
		uint32_t		mask;		// [4]  04 00 00 00 -> r1 in sendBuffer()
		__IO uint32_t*	reg_dir;	// [8]  14 05 00 50
		__IO uint32_t*	reg_set;	// [12] 08 05 00 50 -> r3 in sendBuffer()
		__IO uint32_t*	reg_clr;	// [16] 0c 05 00 50 -> r2 in sendBuffer()
		__I  uint32_t*	reg_in;		// [20] 10 05 00 50
	} gpio_t;						// [24]

#include "DigitalOut.h"
	class DigitalOut {
		gpio_t			gpio;		// [0]
	};								// [24]
#endif	// 0

/**
	@reference	Microsoft pxt-ws2812b sendBuffer.asm (MIT license)
		- https://github.com/Microsoft/pxt-ws2812b
		- https://github.com/Microsoft/pxt-ws2812b/blob/master/sendBuffer.asm
*/
const uint8_t* sendBuffer(MicroBitPin* pin, const uint8_t* buf, int len)
{
	const uint8_t* ret = 0;
	asm volatile(
		".syntax unified		\n\t"	// allow adds/subs/lsrs

		// read from inputs
		"mov r0, %[pin]			\n\t"	// r0 := pin (MicroBitPin*)
		"mov r4, %[buf]			\n\t"	// r4 := buf (const uint8_t*)
		"mov r5, %[len]			\n\t"	// r5 := len (int)
		"subs r5, #1			\n\t"	// r5--

		// *** BEGIN code from sendBuffer.asm ***

		"ldr r0, [r0, #8]		\n\t"	// r0 := pin->pin (DigitalOut*)
		"ldr r1, [r0, #4]		\n\t"	// r1 := pin->pin->mask
		"ldr r2, [r0, #16]		\n\t"	// r2 := pin->pin->reg_clr
		"ldr r3, [r0, #12]		\n\t"	// r3 := pin->pin->reg_set

		"cpsid i				\n\t"	// disable irq
		"b .start				\n\t"	// goto .start

	".nextbit:					\n\t"	// [0] or [20]
		"str r1, [r3, #0]		\n\t"	// [1][2]		pin := high	... low duration is 1000 ns ([22]-[6] = 16 cycles) or 437.5 ns ([22]-[15] = 7 cycles)
		"tst r6, r0				\n\t"	// [3]
		"bne .islate			\n\t"	// [4]			goto .islate [5][6] if r6 (mask) & r0 (data) is ON
		"str r1, [r2, #0]		\n\t"	// [5][6]		pin := low	... high duration is 250 ns ([6]-[2] = 4 cycles)

	".islate:					\n\t"	// [6]
		"lsrs r6, r6, #1		\n\t"	// [7]			r6 (mask) >>= 1
		"bne .justbit			\n\t"	// [8]			goto .justbit [9][10] if r6 (mask) != 0

		// ; not just a bit - need new byte
		"adds r4, #1			\n\t"	// [9]			r4 (buf) ++
		"subs r5, #1			\n\t"	// [10]			r5 (len) --
		"bcc .stop				\n\t"	// [11]			goto .stop [12][13] if r5 (len) < 0

	".start:					\n\t"	// [11]
		"movs r6, #0x80			\n\t"	// [12]			r6 (mask) := 0x80
		"nop					\n\t"	// [13]

	".common:					\n\t"	// [13]
		"str r1, [r2, #0]		\n\t"	// [14][15]		pin := low	... high duration is 812.5 ns ([15] - [2] = 13 cycles)

		// ; always re-load byte - it just fits with the cycles better this way
		"ldrb r0, [r4, #0]		\n\t"	// [16][17]		r0 (data) := * r4 (buf)
		"b .nextbit				\n\t"	// [18][19][20]

	".justbit:					\n\t"	// [10]
		// ; no nops, branch taken is already 3 cycles
		"b .common				\n\t"	// [11][12][13]

	".stop:						\n\t"	// [13]
		"str r1, [r2, #0]		\n\t"	// [14][15]		pin := low	... high duration is 812.5 ns ([15] - [2] = 13 cycles)

		"cpsie i				\n\t"	// enable irq

		// *** END code from sendBuffer.asm ***

		// write to output
		"mov %[ret], r4			\n\t"	// ret := r4

		// output_operand_list
		: [ret] "=r" (ret)

		// input_operand_list
		: [pin] "r" (pin), [buf] "r" (buf), [len] "r" (len)

		// clobbered_register_list
		: "r4", "r5", "r6", "r7", "cc", "memory"
	);
	return ret;
}

}	// microbit_dal_ext_kit
