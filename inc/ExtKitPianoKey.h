/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Piano Key utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_PIANO_KEY_H
#define EXT_KIT_PIANO_KEY_H

#include "ExtKit_Common.h"
#include "ExtKitState.h"

namespace microbit_dal_ext_kit {

/// Piano Keys bit pattern
typedef uint16_t	PianoKeys;

/*
	Extern Template Instantiation
*/

extern template class State<PianoKeys>;
extern template class StateChange<PianoKeys>;

/// State For PianoKeys
class StateForPianoKeys : public State<PianoKeys>
{
public:
	/// Constructor
	StateForPianoKeys();

};	// StateForPianoKeys

/// State Change For PianoKeys
class StateChangeForPianoKeys : public StateChange<PianoKeys>
{
public:
	/// Constructor
	StateChangeForPianoKeys();

};	// StateChangeForPianoKeys

/// Piano Key utility
namespace pianoKey {

/// Invalid Value
const PianoKeys kInvalid	= (PianoKeys) -1;

/// No key
const PianoKeys kNone	= 0;

/// Low C key bit. Assigned to C4 (261.626Hz or Middle C) if octave value is octave::kCenter.
const PianoKeys kC	= 1 << 0;

/// Db key bit
const PianoKeys kDb	= 1 << 1;

/// D key bit
const PianoKeys kD	= 1 << 2;

/// Eb key bit
const PianoKeys kEb	= 1 << 3;

/// E key bit
const PianoKeys kE	= 1 << 4;

/// F key bit
const PianoKeys kF	= 1 << 5;

/// Gb key bit
const PianoKeys kGb	= 1 << 6;

/// G key bit
const PianoKeys kG	= 1 << 7;

/// Ab key bit
const PianoKeys kAb	= 1 << 8;

/// A key bit. Assigned to A4 (440.000Hz) if octave is octave::kCenter.
const PianoKeys kA	= 1 << 9;

/// Bb key bit
const PianoKeys kBb	= 1 << 10;

/// B key bit
const PianoKeys kB	= 1 << 11;

/// High C key bit. Assigned to C5 (523.251Hz) if octave is octave::kCenter.
const PianoKeys kCC	= 1 << 12;

/// Black keys
const PianoKeys kBlack	= kDb | kEb | kGb | kAb | kBb;

/// White keys
const PianoKeys kWhite	= kC | kD | kE | kF | kG | kA | kB | kCC;

}	// pianoKeys
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_PIANO_KEY_H
