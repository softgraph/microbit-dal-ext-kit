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

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	Sonar(MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler);

	/// Trigger sonar.
	/** Suggest to use over 60 ms measurement cycle, in order to prevent trigger signal to the echo signal.
	*/
	void trigger();

protected:
	/// Trigger Output Port
	MicroBitPin&		mTriggerOutput;

	/// Handler
	HandlerProtocol&	mHandler;

private:
	/// Handle Echo Input
	void handleEchoInput(MicroBitEvent event);

};	// Sonar

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SONAR_H
