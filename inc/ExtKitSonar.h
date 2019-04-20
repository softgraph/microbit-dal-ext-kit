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

///	%Sonar Duration in milliseconds
typedef uint32_t	SonarDuration;

/*
	Extern Template Instantiation
*/

extern template class State<SonarDuration>;
extern template class StateChange<SonarDuration>;

/// `#State` for `#SonarDuration`
class StateForSonarDuration : public State<SonarDuration>
{
public:
	/// Constructor
	StateForSonarDuration();

};	// StateForSonarDuration

/// `#StateChange` for `#SonarDuration`
class StateChangeForSonarDuration : public StateChange<SonarDuration>
{
public:
	/// Constructor
	StateChangeForSonarDuration();

};	// StateChangeForSonarDuration

/// An ext-kit Component which provides the support for a generic sonar modules such as HC-SR04
class Sonar : public Component
{
public:
	/// Handler Protocol
	/* interface */ class HandlerProtocol
	{
	public:
		/// Handle Sonar Echo
		virtual /* to be implemented */ void handleSonarEcho(SonarDuration duration) = 0;

	};	// HandlerProtocol

	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	Sonar(MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler);

	/// Trigger sonar
	void trigger();

protected:
	/// Trigger Output Port
	MicroBitPin&		mTriggerOutputPort;

	/// Handler
	HandlerProtocol&	mHandler;

private:
	/// Handle Echo Input
	void handleEchoInput(MicroBitEvent event);

};	// Sonar

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SONAR_H
