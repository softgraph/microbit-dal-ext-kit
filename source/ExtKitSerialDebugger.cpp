/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Serial Debugger component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitSerialDebugger.h"	// self

#include "ExtKit.h"

namespace microbit_dal_ext_kit {

static const char* isRegistered(bool registered);
static void raiseFailedAssertion();
static void raiseUnexpectedError();

SerialDebugger::SerialDebugger(const char* name)
	: Component(name)
	, mCommand("")
	, mPrevChar(0)
	, mLineModeChar(0)
{
}

#if EXT_KIT_CONFIG_ENABLED(SERIAL_EXT_DEBUG)

/* Component */ void SerialDebugger::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		serial::initializeRx();		// required for receivng the event

		ExtKit& g = ExtKit::global();
		g.messageBus().listen(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_HEAD_MATCH, this, &SerialDebugger::handleSerialReceived);
		g.serial().eventAfter(1 /* character */);
	}
	else if(action == kPoststart) {
		/* virtual */ doHandleSerialDebuggerEnabled();
	}
	else if(action == kPrestop) {
		/* virtual */ doHandleSerialDebuggerDisabled();
	}
	else if(action == kStop) {
		ExtKit& g = ExtKit::global();
		g.messageBus().ignore(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_HEAD_MATCH, this, &SerialDebugger::handleSerialReceived);
	}

	Component::doHandleComponentAction(action);
}

#else	// SERIAL_EXT_DEBUG

/* Component */ void SerialDebugger::doHandleComponentAction(Action action)
{
	Component::doHandleComponentAction(action);
}

#endif	// SERIAL_EXT_DEBUG

/* SerialDebugger */ void SerialDebugger::doHandleSerialDebuggerEnabled()
{
	serial::sendLine("*** Hit any key to activate the serial debugger ***");
}

/* SerialDebugger */ void SerialDebugger::doHandleSerialDebuggerDisabled()
{
	serial::sendLine("*** The serial debugger is disabled ***");
}

void SerialDebugger::handleSerialReceived(MicroBitEvent event)
{
	if(event.source != MICROBIT_ID_SERIAL || event.value != MICROBIT_SERIAL_EVT_HEAD_MATCH) {
		return;
	}

	MicroBitSerial& serial = ExtKit::global().serial();
	ManagedString s = serial.read(1 /* character */);
	serial.clearRxBuffer();
	serial.eventAfter(1 /* character */);

	char c = s.charAt(0);
	doHandleSerialReceived(c);
}

#define BS	0x08	// BackSpace (ctrl-h)
#define LF	0x0a	// Line Feed (ctrl-j)
#define CR	0x0d	// Carriage Return (ctrl-m)
#define ESC	0x1b	// Escape
#define DEL	0x7f	// Delete

/* SerialDebugger */ void SerialDebugger::doHandleSerialReceived(char c)
{
	// Activate debugger if it is not activated
	if(!debug_isDebuggerActive()) {
		debug_activateDebugger(true);
		debug_sendCmdHelp();
		return;
	}

	// Ignore LF if the previous character is CR
	if((mPrevChar == CR) && (c == LF)) {
		mPrevChar = c;
		return;
	}

	// Save the previous character
	mPrevChar = c;

	// Convert LF to CR
	if(c == LF) {
		c = CR;
	}

	// Echo to the terminal
	switch(c) {
		case BS:
		case DEL: {
			serial::sendChar(BS);
			serial::sendChar(' ');
			serial::sendChar(BS);
			int16_t length = mCommand.length();
			if(length > 0) {
				length--;
				if(length) {
					// Delete the last character of the buffer
					mCommand = mCommand.substring(0, length);
				}
				else {
					goto clear_buffer;	// consumed
				}
			}
			return;
		}
		case CR:
		case ESC: {
			serial::sendLine("");
			break;
		}
		default: {
			serial::sendChar(c);
			break;
		}
	}

	// Switch mode if the line starts with one of the mode characters
	if(mCommand.length() == 0) {
		switch(c) {
			case ':': {
				mCommand = ManagedString(c);
				mLineModeChar = c;
				return;
			}
		}
	}

	// Terminate the command by CR or ESC
	switch(c) {
		case CR: {
			if(mLineModeChar) {
				// Evaluate the buffer
				doHandleLineCommand(mCommand);
			}
			// continue
		}
		case ESC: {
			goto clear_buffer;	// consumed
		}
	}

	// Update the command string buffer
	mCommand = mCommand + ManagedString(c);

	// Keep the buffer if Line Input Mode is on
	if(mLineModeChar) {
		return;
	}

	// Keep the buffer if the command is not handled
	if(!doHandleDirectCommand(mCommand)) {
		return;
	}

clear_buffer:
	// Clear the buffer and Line Input Mode
	mCommand = ManagedString::EmptyString;
	mLineModeChar = 0;
}

/* SerialDebugger */ bool /* consumed */ SerialDebugger::doHandleDirectCommand(ManagedString command)
{
	if(command.length() == 1) {
		const char c0 = command.charAt(0);
		switch(c0) {
			case '?': {
				debug_sendLine("", false);
				debug_sendCmdHelp();
				return true;	// consumed
			}
			case 'a':
			case 'A': {
				debug_sendLine("", false);
				button::clickPseudoButton('a');
				return true;	// consumed
			}
			case 'b':
			case 'B': {
				debug_sendLine("", false);
				button::clickPseudoButton('b');
				return true;	// consumed
			}
			case 'w':
			case 'W': {
				debug_sendLine("", false);
				button::clickPseudoButton('w');
				return true;	// consumed
			}
		}
	}
	else if(command.length() == 2) {
		const char c0 = command.charAt(0);
		const char c1 = command.charAt(1);
		switch(c0) {
			case 'x':
			case 'X': {
				debug_sendLine("", false);
				debug_sendLine("Key Code: 0x", string::hex(c1).toCharArray(), false);
				return true;	// consumed
			}
		}
	}
	return false;	// not consumed
}

/* SerialDebugger */ bool /* consumed */ SerialDebugger::doHandleLineCommand(ManagedString command)
{
	if(command.length() < 2) {
		return false;	// not consumed
	}

	const char c0 = command.charAt(0);
	if(c0 != ':') {
		return false;	// not consumed
	}

	if(command.length() == 2) {
		const char c1 = command.charAt(1);
		if((c1 == 'q') || (c1 == 'Q')) {	// Show Configuration
			debug_activateDebugger(false);
			return true;	// consumed
		}
	}
	else if(command.length() == 3) {
		const char c1 = command.charAt(1);
		const char c2 = command.charAt(2);
		if((c1 == 's') || (c1 == 'S')) {
			if((c2 == 'c') || (c2 == 'C')) {	// Show Configuration
				debug_sendConfig();
				return true;	// consumed
			}
			else if((c2 == 'd') || (c2 == 'D')) {	// Show Device information
				debug_sendDeviceInfo();
				return true;	// consumed
			}
			else if((c2 == 's') || (c2 == 'S')) {	// Show Statistics
				Statistics::debug_sendItems();
				return true;	// consumed
			}
		}
		else if((c1 == 'e') || (c1 == 'E')) {
			if((c2 == 'f') || (c2 == 'F')) {		// Emulate Failed assertion
				create_fiber(raiseFailedAssertion);
				return true;	// consumed
			}
			else if((c2 == 'p') || (c2 == 'P')) {	// Emulate Panic (Unexpected Error)
				create_fiber(raiseUnexpectedError);
				return true;	// consumed
			}
		}
		else if((c1 == 'i') || (c1 == 'I')) {
			if((c2 == 'd') || (c2 == 'D')) {	// Identify the Device
				display::scrollString("-");
				debug_sendLine("Identified", false);
				return true;	// consumed
			}
		}
		else if((c1 == 'r') || (c1 == 'R')) {
			if((c2 == 'd') || (c2 == 'D')) {	// Reset the Device
				microbit_reset();
 				return true;	// consumed
			}
		}
	}
	return false;	// not consumed
}

/* SerialDebugger */ void SerialDebugger::debug_sendCmdHelp()
{
	debug_sendLine("--- Help ---", false);
	debug_sendLine("--- Direct Commands (No Enter key is required)", false);
	/* virtual */ debug_sendHelpForDirectCommands();

	debug_sendLine("--- Line Commands (Enter key is required)", false);
	/* virtual */ debug_sendHelpForLineCommands();
}

/* SerialDebugger */ void SerialDebugger::debug_sendHelpForDirectCommands()
{
	static const char* const lineArray[] = {
		"?   show this Help",
		"a   emulate button A clicked",
		"b   emulate button B clicked",
		"w   emulate button A + B clicked",
		"x_  eXamine the key code of the following character at _",
		0	// END OF TABLE
	};

	debug_sendLines(lineArray);
}

/* SerialDebugger */ void SerialDebugger::debug_sendHelpForLineCommands()
{
	static const char* const lineArray[] = {
		":sc     Show Configuration",
		":sd     Show Device information",
		":ss     Show Statistics",
		":ef     Emulate Failed assertion",
		":ep     Emulate Panic (Unexpected Error)",
		":id     Identify the Device",
		":rd     Reset the Device",
		":q      Quit the debugger",
		0	// END OF TABLE
	};

	debug_sendLines(lineArray);
}

void SerialDebugger::debug_sendLines(const char* const * lineArray /* terminated by 0 */)
{
	const char* const * p = lineArray;
	while(*p) {
		debug_sendLine(*p++, false);
	}
}

/* SerialDebugger */ void SerialDebugger::debug_sendConfig()
{
	ExtKit& g = ExtKit::global();

	debug_sendLine("--- Active App Mode ---", false);
	debug_sendAppMode(0, appMode(), false);

	debug_sendLine("--- Global object ---", false);
	debug_sendLine("owner:         ", g.owner(), false);
	debug_sendLine("accelerometer: ", isRegistered(g.accelerometer()), false);
	debug_sendLine("compass:       ", isRegistered(g.compass()), false);
	debug_sendLine("radio:         ", isRegistered(g.radio()), false);
	debug_sendLine("thermometer:   ", isRegistered(g.thermometer()), false);

	debug_sendLine("--- Yotta Config (microbit-dal) ---", false);
	debug_sendLine("CONFIG MICROBIT_SRAM_BASE:   0x", string::hex(MICROBIT_SRAM_BASE).toCharArray(), false);
	debug_sendLine("CONFIG MICROBIT_HEAP_END:    0x", string::hex(MICROBIT_HEAP_END).toCharArray(), false);
	debug_sendLine("CONFIG CORTEX_M0_STACK_BASE: 0x", string::hex(CORTEX_M0_STACK_BASE).toCharArray(), false);
	debug_sendLine("CONFIG MICROBIT_SRAM_END:    0x", string::hex(MICROBIT_SRAM_END).toCharArray(), false);

#if CONFIG_ENABLED(MICROBIT_BLE_ENABLED)
	debug_sendLine("CONFIG MICROBIT_BLE_ENABLED: enabled", false);
#else	// MICROBIT_BLE_ENABLED
	debug_sendLine("CONFIG MICROBIT_BLE_ENABLED: disabled", false);
#endif	// MICROBIT_BLE_ENABLED

#if CONFIG_ENABLED(MICROBIT_BLE_PAIRING_MODE)
	debug_sendLine("CONFIG MICROBIT_BLE_PAIRING_MODE: enabled", false);
#else	// MICROBIT_BLE_PAIRING_MODE
	debug_sendLine("CONFIG MICROBIT_BLE_PAIRING_MODE: disabled", false);
#endif	// MICROBIT_BLE_PAIRING_MODE

#if CONFIG_ENABLED(MICROBIT_DBG)
	debug_sendLine("CONFIG MICROBIT_DBG: enabled", false);
#else	// MICROBIT_DBG
	debug_sendLine("CONFIG MICROBIT_DBG: disabled", false);
#endif	// MICROBIT_DBG

#if CONFIG_ENABLED(MICROBIT_HEAP_DBG)
	debug_sendLine("CONFIG MICROBIT_HEAP_DBG: enabled", false);
#else	// MICROBIT_HEAP_DBG
	debug_sendLine("CONFIG MICROBIT_HEAP_DBG: disabled", false);
#endif	// MICROBIT_HEAP_DBG

	debug_sendLine("--- Yotta Config (microbit-dal-ext-kit) ---", false);

#if EXT_KIT_CONFIG_ENABLED(ASSERT)
	debug_sendLine("CONFIG ASSERT: enabled", false);
#else	// ASSERT
	debug_sendLine("CONFIG ASSERT: disabled", false);
#endif	// ASSERT

	debug_sendLine("CONFIG RADIO_GROUP: ", ManagedString(EXT_KIT_CONFIG_VALUE(RADIO_GROUP)).toCharArray(), false);

#if EXT_KIT_CONFIG_ENABLED(SERIAL_EXT_DEBUG)
	debug_sendLine("CONFIG SERIAL_EXT_DEBUG: enabled", false);
#else	// SERIAL_EXT_DEBUG
	debug_sendLine("CONFIG SERIAL_EXT_DEBUG: disabled", false);
#endif	// SERIAL_EXT_DEBUG

	debug_sendLine("CONFIG SERIAL_RXBUF: ", ManagedString(EXT_KIT_CONFIG_VALUE(SERIAL_RXBUF)).toCharArray(), false);
	debug_sendLine("CONFIG SERIAL_TXBUF: ", ManagedString(EXT_KIT_CONFIG_VALUE(SERIAL_TXBUF)).toCharArray(), false);

//	debug_sendLine("gSerial.getRxBufferSize(): ", ManagedString(gSerial.getRxBufferSize()).toCharArray(), false);
//	debug_sendLine("gSerial.getTxBufferSize(): ", ManagedString(gSerial.getTxBufferSize()).toCharArray(), false);
}

/* SerialDebugger */ void SerialDebugger::debug_sendDeviceInfo()
{
	debug_sendLine("--- Device Information ---", false);
	debug_sendLine("-- Hardware Information", false);
	debug_sendLine("Serial Number: 0x", string::hex(microbit_serial_number()).toCharArray(), false);
	debug_sendLine("Friendly Name: ", microbit_friendly_name(), false);

	debug_sendLine("-- Build Environment", false);
	debug_sendLine("sizeof(bool):   ", ManagedString((int) sizeof(bool)).toCharArray(), false);
	debug_sendLine("sizeof(int):    ", ManagedString((int) sizeof(int)).toCharArray(), false);
	debug_sendLine("sizeof(void*):  ", ManagedString((int) sizeof(void*)).toCharArray(), false);
	debug_sendLine("sizeof(size_t): ", ManagedString((int) sizeof(size_t)).toCharArray(), false);

//	State<uint8_t> a[2] = { State<uint8_t>(0), State<uint8_t>(1) };
//	debug_sendLine("sizeof(State<uint8_t>):    ", ManagedString((int) sizeof(a[0])).toCharArray(), false);
//	debug_sendLine("sizeof(State<uint8_t>[2]): ", ManagedString((int) sizeof(a)).toCharArray(), false);

	debug_sendLine("-- Software Information", false);
	debug_sendLine("Build Date: ", __DATE__, " ", __TIME__, false);
	debug_sendLine("mbed-classic version: " YOTTA_MBED_CLASSIC_VERSION_STRING, false);
	debug_sendLine("microbit-dal version: ", microbit_dal_version(), false);
	debug_sendLine("microbit_dal_ext_kit version: " YOTTA_MICROBIT_DAL_EXT_KIT_VERSION_STRING, false);
}

const char* isRegistered(bool registered)
{
	return registered ? "registered" : "not registered";
}

void raiseFailedAssertion()
{
	time::sleep(500 /* milliseconds */);
	EXT_KIT_ASSERT(!"Fail raised by the serial debugger");
}

void raiseUnexpectedError()
{
	time::sleep(500 /* milliseconds */);
	EXT_KIT_ASSERT_OR_PANIC(!"Error raised by the serial debugger", kPanicUnexpectedError);
}

}	// microbit_dal_ext_kit
