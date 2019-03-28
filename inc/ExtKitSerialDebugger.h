/// Yotta module microbit-dal-ext-kit
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

	/// Called when the serial port is enabled
	virtual /* to be overridden */ void doHandleSerialEnabled();

	/// Called when a character is received from the serial port
	virtual /* to be overridden */ void doHandleSerialReceived(char c);

	/// Called when a command is received from the serial port
	virtual /* to be overridden */ void doHandleCommand(char c);

	/// Called when Show Help command is received
	virtual /* to be overridden */ void debug_sendCmdHelp();

	/// Called when Show Configuration command is received
	virtual /* to be overridden */ void debug_sendConfig();

	/// Called when Show Device information command is received
	virtual /* to be overridden */ void debug_sendDeviceInfo();

private:
	/// Handle serial received event
	void handleSerialReceived(MicroBitEvent event);

};	// SerialDebugger

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_SERIAL_DEBUGGER_H
