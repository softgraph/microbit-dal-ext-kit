/// Yotta module microbit-dal-ext-kit
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

static void raiseFailedAssertion();
static void raiseUnexpectedError();

SerialDebugger::SerialDebugger(const char* name)
	: Component(name)
{
}

#if EXT_KIT_CONFIG_ENABLED(SERIAL_EXT_DEBUG)

/* Component */ void SerialDebugger::start()
{
	ExtKit& g = ExtKit::global();
	g.messageBus().listen(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_HEAD_MATCH, this, &SerialDebugger::handleSerialReceived);
	serial::initializeRx();		// required for receivng the event
	g.serial().eventAfter(1 /* character */);

	doHandleSerialEnabled();
}

#else	// SERIAL_EXT_DEBUG

/* Component */ void SerialDebugger::start()
{
}

#endif	// SERIAL_EXT_DEBUG

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

/* to be overridden */ void SerialDebugger::doHandleSerialEnabled()
{
	serial::sendLine("*** Hit Enter to enable the serial debugger ***");
}

/* to be overridden */ void SerialDebugger::doHandleSerialReceived(char c)
{
	if(!debug_isDebuggerEnabled()) {
		debug_setDebugger(true);
		debug_sendCmdHelp();
		return;
	}

	doHandleCommand(c);
}

/* to be overridden */ void SerialDebugger::doHandleCommand(char c)
{
	serial::sendLine(c);
	switch(c) {
		case '?': {
			debug_sendCmdHelp();
			break;
		}
		case 'c':
		case 'C': {
			debug_sendConfig();
			break;
		}
		case 'd':
		case 'D': {
			debug_sendDeviceInfo();
			break;
		}
		case 'a':
		case 'A': {
			button::clickPseudoButton('a');
			break;
		}
		case 'b':
		case 'B': {
			button::clickPseudoButton('b');
			break;
		}
		case 'w':
		case 'W': {
			button::clickPseudoButton('w');
			break;
		}
		case 'f':
		case 'F': {
			create_fiber(raiseFailedAssertion);
			break;
		}
		case 'u':
		case 'U': {
			create_fiber(raiseUnexpectedError);
			break;
		}
		case 'i':
		case 'I': {
			display::scrollString("-");
			debug_sendLine("Identified", false);
			break;
		}
		case 'r':
		case 'R': {
			microbit_reset();
			break;
		}
		case 'q':
		case 'Q': {
			debug_setDebugger(false);
			break;
		}
	}
}

/* to be overridden */ void SerialDebugger::debug_sendCmdHelp()
{
	static const char* serialCmdHelp[] = {
		"--- Help ---",
		"?: show this Help",
		"c: show Configuration",
		"d: show Device information",
		"a: emulate button A clicked",
		"b: emulate button B clicked",
		"w: emulate button A + B clicked",
		"f: emulate Failed assertion",
		"u: emulate Unexpected error",
		"i: Identify the device",
		"r: Reset the device",
		"q: Quit the debugger",
		NULL
	};

	const char** p = serialCmdHelp;
	while (*p) {
		debug_sendLine(*p++, false);
	}
}

/* to be overridden */ void SerialDebugger::debug_sendConfig()
{
	ExtKit& g = ExtKit::global();

	debug_sendLine("--- Active App Mode ---", false);
	debug_sendAppMode(0, feature::configured(), false);

	debug_sendLine("--- Global object ---", false);
	debug_sendLine("owner: ", g.owner(), false);
	if(g.accelerometer()) {
		debug_sendLine("accelerometer: registered", false);
	} else {
		debug_sendLine("accelerometer: not registered", false);
	}
	if(g.compass()) {
		debug_sendLine("compass:       registered", false);
	} else {
		debug_sendLine("compass:       not registered", false);
	}
	if(g.radio()) {
		debug_sendLine("radio:         registered", false);
	} else {
		debug_sendLine("radio:         not registered", false);
	}
	if(g.thermometer()) {
		debug_sendLine("thermometer:   registered", false);
	} else {
		debug_sendLine("thermometer:   not registered", false);
	}

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

/* to be overridden */ void SerialDebugger::debug_sendDeviceInfo()
{
	debug_sendLine("--- Hardware Information ---", false);
	debug_sendLine("Serial Number: 0x", string::hex(microbit_serial_number()).toCharArray(), false);
	debug_sendLine("Friendly Name: ", microbit_friendly_name(), false);

	debug_sendLine("--- Software Information ---", false);
	debug_sendLine("Build Date: ", __DATE__, " ", __TIME__, false);
	debug_sendLine("microbit-dal version: ", microbit_dal_version(), false);
	debug_sendLine("microbit_dal_ext_kit version: " YOTTA_MICROBIT_DAL_EXT_KIT_VERSION_STRING, false);
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
