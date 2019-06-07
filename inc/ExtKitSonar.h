/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Sonar component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_SONAR_H
#define EXT_KIT_SONAR_H

#include "ExtKitComponent.h"
#include "ExtKitState.h"

class MicroBitEvent;
class MicroBitPin;

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides the support for a generic sonar modules such as HC-SR04
class Sonar : public Component
{
public:
	/// Handler Protocol
	/* interface */ class HandlerProtocol
	{
	public:
		/// Handle Sonar Echo.
		/** Duration of 1000 us (1 ms) means that the distace to the object is 171.5 mm if the speed of sound is 343 m/s. Please note the speed of sound depends strongly on temperature.
		*/
		virtual /* to be implemented */ void handleSonarEcho(uint32_t duration /* in microseconds*/) = 0;

	};	// HandlerProtocol

	/// Echo Input Stabilizer
	/**
		0: No stabilizer - raw data
		1: The weakest stabilizer - mix the latest and the previous data in the proportion 7:1
		:
		7: The strongest stabilizer - mix the latest and the previous data in the proportion 1:7
	*/
	typedef uint8_t EchoInputStabilizer;

	/// Constructor
	Sonar(const char* name, MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler, EchoInputStabilizer echoInputStabilizer = 0);

	/// Trigger sonar.
	/** Suggest to use over 60 ms measurement cycle, in order to prevent trigger signal to the echo signal.
	*/
	void trigger();

protected:
	/// Trigger Output Port
	MicroBitPin&		mTriggerOutput;

	/// Echo Input Port
	MicroBitPin&		mEchoInput;

	/// Handler
	HandlerProtocol&	mHandler;

private:
	/// Handle Echo Input
	void handleEchoInput(MicroBitEvent event);

	/// Previous Sonar Duration
	uint32_t	mPreviousSonarDuration;

	/// Echo Input Stabilizer
	EchoInputStabilizer		mEchoInputStabilizer;

};	// Sonar

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SONAR_H
