/// Yotta module microbit-dal-ext-kit
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

class MicroBitEvent;
class MicroBitPin;

namespace microbit_dal_ext_kit {

/// Sonar Component
/**
	Support for a sonar modules such as HC-SR04.
*/
class Sonar : public Component
{
public:
	/// Handler Protocol
	/* interface */ class HandlerProtocol
	{
	public:
		/// Handle Sonar Echo
		virtual /* to be implemented */ void handleSonarEcho(uint64_t durationInMs) = 0;

	};	// HandlerProtocol

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	Sonar(MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler);

	/// Trigger sonar
	void trigger();

protected:
	/// Handle Echo Input
	void handleEchoInput(MicroBitEvent event);

	MicroBitPin&		mTriggerOutputPort;
	HandlerProtocol&	mHandler;

};	// Sonar

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SONAR_H
