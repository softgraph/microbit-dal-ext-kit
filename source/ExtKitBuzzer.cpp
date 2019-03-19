/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Buzzer component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitBuzzer.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	Buzzer
*/

static const Features kFeature = feature::kBuzzer;

static const int portValue = 2;

static uint16_t durationForPianoKeys(PianoKeys& /* INOUT */ pianoKeys, Octave octave);

/* Component */ Features Buzzer::avaiableFeatures(MicroBitPin& analogPort)
{
	bool available = false;
	{
		int value = analogPort.getAnalogValue();
		//	display::scrollString(value);
		if(value < 10) {
			available = true;
		}
	}
	return available ? kFeature : 0;
}

/* Component */ bool Buzzer::isConfigured()
{
	return feature::isConfigured(kFeature);
}

Buzzer::Buzzer(const char* name, MicroBitPin& analogPort)
	: Component(name)
	, mSoundPort(analogPort)
	, mCurrentTone(pianoKey::kNone)
	, mCurrentOctave(octave::kCenter)
{
	mSoundPort.setAnalogValue(0);	// configures the port for analog output
}

Buzzer::~Buzzer()
{
}

/* Component */ void Buzzer::start()
{
	mSoundPort.setAnalogValue(0);
	mCurrentTone = pianoKey::kNone;
	mCurrentOctave = octave::kCenter;
}

void Buzzer::playTone(PianoKeys& /* INOUT */ pianoKeys, Octave octave)
{
	if((pianoKeys & mCurrentTone) && (octave == mCurrentOctave)) {
		// keep the current tone until the piano key for the current tone is released
		return;
	}

	// switch to another tone or stop the current tone
	uint16_t duration = durationForPianoKeys(/* INOUT */ pianoKeys, octave);
	if(duration) {
		mSoundPort.setAnalogValue(0);
		mSoundPort.setAnalogPeriodUs((int) duration);
		mSoundPort.setAnalogValue(portValue);
		mCurrentTone = pianoKeys;
		mCurrentOctave = octave;
	}
	else {
		mSoundPort.setAnalogValue(0);
		mCurrentTone = pianoKey::kNone;
		mCurrentOctave = octave;
	}
}

uint16_t /* duration in microseconds */ durationForPianoKeys(PianoKeys& /* INOUT */ pianoKeys, Octave octave)
{
	EXT_KIT_ASSERT(octave::kLowest <= octave);
	EXT_KIT_ASSERT(octave <= octave::kHighest);

	#define D(x)	((uint16_t) (1000 * 1000 / (x)))
	static const uint16_t durationTable[][12] = {
		{	// C1 - B1 (C1 is Low C for octave::kLowest)
			D(32.703),  D(34.648),  D(36.708),  D(38.891),  D(41.203),  D(43.654),
			D(46.249),  D(48.999),  D(51.913),  D(55.000),  D(58.270),  D(61.735) },
		{	// C2 - B2
			D(65.406),  D(69.296),  D(73.416),  D(77.782),  D(82.407),  D(87.307),
			D(92.499),  D(97.999),  D(103.826), D(110.000), D(116.541), D(123.471) },
		{	// C3 - B3
			D(130.813), D(138.591), D(146.832), D(155.563), D(164.814), D(174.614),
			D(184.997), D(195.998), D(207.652), D(220.000), D(233.082), D(246.942) },
		{	// C4 - B4 (C4 is Low C for octave::kCenter)
			D(261.626), D(277.183), D(293.665), D(311.127), D(329.628), D(349.228),
			D(369.994), D(391.995), D(415.305), D(440.000), D(466.164), D(493.883) },
		{	// C5 - B5
			D(523.251), D(554.365), D(587.330), D(622.254), D(659.255), D(698.456),
			D(739.989), D(783.991), D(830.609), D(880.000), D(932.328), D(987.767) },
		{	// C6 - B6
			D(1046.502), D(1108.731), D(1174.659), D(1244.508), D(1318.510), D(1396.913),
			D(1479.978), D(1567.982), D(1661.219), D(1760.000), D(1864.655), D(1975.533) },
		{	// C7 - B7 (C7 is Low C for octave::kHighest)
			D(2093.005), D(2217.461), D(2349.318), D(2489.016), D(2637.020), D(2793.826),
			D(2959.955), D(3135.963), D(3322.438), D(3520.000), D(3729.310), D(3951.066) },
		{	// C8 - B8 (C8 is High C for octave::kHighest)
			D(4186.009), D(4434.922), D(4698.636), D(4978.031), D(5274.040), D(5587.651),
			D(5919.910), D(6271.926), D(6644.875), D(7040.000), D(7458.620), D(7902.132) }
	};

	const uint16_t* p = durationTable[octave - octave::kLowest];
	if(pianoKeys == pianoKey::kInvalid)		{	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: None");	*/	pianoKeys = pianoKey::kNone;	return 0; }
	else if(pianoKeys == pianoKey::kNone)	{	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: None");	*/	pianoKeys = pianoKey::kNone;	return 0; }
	else if(pianoKeys & pianoKey::kC)		{	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: C");		*/	pianoKeys = pianoKey::kC;		return p[0];  }
	else if(pianoKeys & pianoKey::kDb)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: Db");	*/	pianoKeys = pianoKey::kDb;		return p[1]; }
	else if(pianoKeys & pianoKey::kD)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: D");		*/	pianoKeys = pianoKey::kD;		return p[2]; }
	else if(pianoKeys & pianoKey::kEb)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: Eb");	*/	pianoKeys = pianoKey::kEb;		return p[3]; }
	else if(pianoKeys & pianoKey::kE)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: E");		*/	pianoKeys = pianoKey::kE;		return p[4]; }
	else if(pianoKeys & pianoKey::kF)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: F");		*/	pianoKeys = pianoKey::kF;		return p[5]; }
	else if(pianoKeys & pianoKey::kGb)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: Gb");	*/	pianoKeys = pianoKey::kGb;		return p[6]; }
	else if(pianoKeys & pianoKey::kG)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: G");		*/	pianoKeys = pianoKey::kG;		return p[7]; }
	else if(pianoKeys & pianoKey::kAb)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: Ab");	*/	pianoKeys = pianoKey::kAb;		return p[8]; }
	else if(pianoKeys & pianoKey::kA)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: A");		*/	pianoKeys = pianoKey::kA;		return p[9]; }
	else if(pianoKeys & pianoKey::kBb)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: Bb");	*/	pianoKeys = pianoKey::kBb;		return p[10]; }
	else if(pianoKeys & pianoKey::kB)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: B");		*/	pianoKeys = pianoKey::kB;		return p[11]; }
	else if(pianoKeys & pianoKey::kCC)		{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: CC");	*/	pianoKeys = pianoKey::kCC;		return p[12]; }
	else							{ 	/* debug_sendLine(EXT_KIT_DEBUG_INFO "PianoKey: None");	*/	pianoKeys = pianoKey::kNone;	return 0; }
}

}	// microbit_dal_ext_kit
