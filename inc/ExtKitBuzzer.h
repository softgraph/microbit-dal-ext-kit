/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Buzzer component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_BUZZER_H
#define EXT_KIT_BUZZER_H

#include "ExtKitComponent.h"
#include "ExtKitOctave.h"
#include "ExtKitPianoKey.h"

class MicroBitPin;

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for a generic buzzer
class Buzzer : public Component
{
public:
	/// Check that a buzzer module is possibly available on the port and return available Features
	static /* Component */ Features avaiableFeatures(MicroBitPin& analogPort);

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor with an analog port
	Buzzer(const char* name, MicroBitPin& analogPort);

	/// Destructor
	~Buzzer();

	/// Play a tone
	void playTone(PianoKeys& /* INOUT */ pianoKeys, Octave octave);

protected:
	/// Inherited
	/* Component */ void doStart();

	/// Sound Port
	MicroBitPin&	mSoundPort;

	/// Current Tone
	PianoKeys		mCurrentTone;

	/// Current Octave
	Octave			mCurrentOctave;

};	// Buzzer

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_BUZZER_H
