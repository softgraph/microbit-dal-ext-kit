/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Serial Debugger component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_SERIAL_DEBUGGER_H
#define EXT_KIT_SERIAL_DEBUGGER_H

#include "ManagedString.h"

#include "ExtKitComponent.h"

class MicroBitEvent;

namespace microbit_dal_ext_kit {

/// Serial Debugger Component
class SerialDebugger : public Component
{
public:
	/// Constructor
	SerialDebugger(const char* name);

protected:
	/// Inherited
	/* Component */ void doStart();

	/// Inherited
	/* Component */ void doStop();

	/// Called when the serial debugger is enabled (ready to activate)
	virtual /* to be overridden */ void doHandleSerialDebuggerEnabled();

	/// Called when the serial debugger is disabled
	virtual /* to be overridden */ void doHandleSerialDebuggerDisabled();

	/// Called when a character is received from the serial port
	virtual /* to be overridden */ void doHandleSerialReceived(char c);

	/// Called when a command for Direct Input Mode is ready to evaluate
	virtual /* to be overridden */ bool /* consumed */ doHandleDirectCommand(ManagedString command);

	/// Called when a command for Line Input Mode is ready to evaluate
	virtual /* to be overridden */ bool /* consumed */ doHandleLineCommand(ManagedString command);

	/// Called when Show Help command is received
	virtual /* to be overridden */ void debug_sendCmdHelp();

	/// Called when Show Help command for Direct Input Mode is requested
	virtual /* to be overridden */ void debug_sendHelpForDirectCommands();

	/// Called when Show Help command for Line Input Mode is requested
	virtual /* to be overridden */ void debug_sendHelpForLineCommands();

	/// Send Lines
	void debug_sendLines(const char* const * lineArray /* terminated by 0 */);

	/// Called when Show Configuration command is received
	virtual /* to be overridden */ void debug_sendConfig();

	/// Called when Show Device information command is received
	virtual /* to be overridden */ void debug_sendDeviceInfo();

	/// Command string buffer
	ManagedString mCommand;

	/// Previous character
	char mPrevChar;

	/// Mode character of Line Input Mode. 0 means Direct Input Mode.
	char mLineModeChar;

private:
	/// Handle serial received event
	void handleSerialReceived(MicroBitEvent event);

};	// SerialDebugger

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SERIAL_DEBUGGER_H
