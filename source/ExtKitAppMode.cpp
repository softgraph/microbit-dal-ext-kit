/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// App Mode utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitAppMode.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

static const AppModeDescriberProtocol* sDescriber = 0;

static void showCharFor(AppMode appMode);
static void flashCharFor(AppMode appMode);
static void debug_sendPossibleAppModes(const AppMode* appModes);

void registerAppModeDescriber(const AppModeDescriberProtocol& describer)
{
	sDescriber = &describer;
}

const AppModeDescriberProtocol* appModeDescriber()	// returns null until `registerAppModeDescriber()` is called
{
	return sDescriber;
}

void selectAppModeFor(Features condition, const AppModeDescriberProtocol& describer)
{
	EXT_KIT_ASSERT(condition);

	registerAppModeDescriber(describer);

	AppMode* selection = 0;
	int count = sDescriber->appModesFor(condition, /* OUT new */ &selection);
	EXT_KIT_ASSERT(0 < count);
	EXT_KIT_ASSERT(selection);

	AppMode appMode = 0;
	if(count == 1) {
		appMode = selection[0];
	}
	else {
		debug_sendPossibleAppModes(selection);
		int i = 0;
		showCharFor(selection[i]);
		while(1) {
			if(button::isButtonAPressed()) {
				i++;
				if(count <= i) {
					i = 0;
				}
				showCharFor(selection[i]);
				debug_sendAppMode(EXT_KIT_DEBUG_INFO "Focused App Mode: ", selection[i]);
				button::waitUntilMicroBitButtonsAreReleased();
			}
			else if(button::isButtonBPressed()) {
				button::waitUntilMicroBitButtonsAreReleased();
				appMode = selection[i];
				flashCharFor(appMode);
				break;
			}
			else {
				time::sleep(100 /* milliseconds */);
			}
		}
	}

	feature::setConfigured(appMode);
	showCharFor(appMode);
	debug_sendAppMode(EXT_KIT_DEBUG_INFO "Active App Mode: ", appMode);
	//	serial::sendLine("*** App Mode Selected ***");

	delete[] selection;
}

void showCharFor(AppMode appMode)
{
	char c = sDescriber ? sDescriber->charFor(appMode) : '?';
	display::showChar(c);
}

void flashCharFor(AppMode appMode)
{
	char c = sDescriber ? sDescriber->charFor(appMode) : '?';
	display::flashChar(c, 200);
}

void debug_sendPossibleAppModes(const AppMode* appModes)
{
	EXT_KIT_ASSERT(appModes);
	EXT_KIT_ASSERT(*appModes);

	debug_sendLine("--- Possible App Modes ---", false);
	while(*appModes) {
		debug_sendAppMode(0, *appModes++, false);
	}
}

void debug_sendAppMode(const char* title, AppMode appMode, bool withDebugPrefix)
{
	if(sDescriber) {
		static char buf[5];
		const char c = sDescriber->charFor(appMode);
		const char* name = sDescriber->nameFor(appMode);
		buf[0] = ' ';
		buf[1] = '(';
		buf[2] = c;
		buf[3] = ')';
		buf[4] = 0;
		debug_sendLine(title, name, buf, withDebugPrefix);
	}
	else {
		const char* appModeString = string::hex(appMode).toCharArray();
		debug_sendLine(title, " 0x", appModeString, withDebugPrefix);
	}
}

}	// microbit_dal_ext_kit
