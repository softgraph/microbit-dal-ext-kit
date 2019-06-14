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

static AppMode sAppMode = 0;

static int /* count */ optionsFor(const AppMode* appModes, int appModeCount, int position, char** /* OUT new[] */ outOptions);
static char charFor(const char* menuKey, unsigned int index);
static void debug_sendPossibleAppModes(const AppMode* appModes);

void setAppMode(AppMode appMode)
{
	sAppMode = appMode;
}

AppMode appMode()
{
	return sAppMode;
}

void registerAppModeDescriber(const AppModeDescriberProtocol& describer)
{
	sDescriber = &describer;
}

const AppModeDescriberProtocol* appModeDescriber()	// returns null until `registerAppModeDescriber()` is called
{
	return sDescriber;
}

void selectAppModeFor(AppMode condition, const AppModeDescriberProtocol& describer)
{
	EXT_KIT_ASSERT(condition);

	// Ensure that the App Mode Describer is registered
	registerAppModeDescriber(describer);

	// Clear the previous App Mode
	sAppMode = 0;

	// Initializa the list of App Modes
	AppMode* appModes = 0;
	int appModeCount = 0;

	// Initializa the list of optinos
	char* options = 0;
	int optionCount = 0;

	// Initialize the menu key filter
	char menuKeyFilter[7 + 1] = {};
	const char* const * hints = sDescriber->hints();

	// Until the menu key filter is filled
	for(int i = 0; i < 7; i++) {
		// Update the list of App Modes for the menu key filter
		delete[] appModes;
		appModeCount = sDescriber->appModesFor(condition, menuKeyFilter, /* OUT new[] */ &appModes);
		EXT_KIT_ASSERT(0 < appModeCount);
		EXT_KIT_ASSERT(appModes);

		// Exit if only one App Mode is available
		if(appModeCount == 1) {
			// Set the App Mode
			sAppMode = appModes[0];
			break;
		}

		// Send the possible App Modes to the debugger
		if(i == 0) {
			debug_sendPossibleAppModes(appModes);
		}

		// Update the list of options for the current filter position (`i`)
		delete[] options;
		optionCount = optionsFor(appModes, appModeCount, i, /* OUT new[] */ &options);
		EXT_KIT_ASSERT(0 < optionCount);
		EXT_KIT_ASSERT(options);

		// Choose it if only one option is available
		if(optionCount == 1) {
			menuKeyFilter[i] = options[0];
			continue;
		}

		// Choose an option
		char c = button::chooseFrom(options, i, hints);

		// Update the filter
		menuKeyFilter[i] = c;
	}
	EXT_KIT_ASSERT(sAppMode);

	// Show the selected App Mode and then clear
	const char* menuKey = sDescriber->menuKeyFor(sAppMode);
	display::scrollString(ManagedString(menuKey), ' ');

	// Send the selected App Mode to the debugger
	debug_sendAppMode(EXT_KIT_DEBUG_INFO "Active App Mode: ", sAppMode);
 
	delete[] appModes;
	delete[] options;
}

int /* count */ optionsFor(const AppMode* appModes, int appModeCount, int position, char** /* OUT new[] */ outOptions)
{
	EXT_KIT_ASSERT(outOptions);

	// Initializa the list
	int count = 0;
	char* options = new char[appModeCount + 1];
	EXT_KIT_ASSERT_OR_PANIC(options, kPanicOutOfMemory);

	// Append options to the list
	options[0] = 0;
	while(*appModes) {
		const char* menuKey = sDescriber->menuKeyFor(*appModes++);
		char c = charFor(menuKey, position);
		if(!c || string::contains(c, options)) {
			continue;
		}
		options[count++] = c;
		options[count] = 0;
	}

	// Return the list
	*outOptions = options;
	return count;
}

char charFor(const char* menuKey, unsigned int index)
{
	return (menuKey && (index < strlen(menuKey))) ? menuKey[index] : 0;
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
		const char* menuKey = sDescriber->menuKeyFor(appMode);
		const char* description = sDescriber->descriptionFor(appMode);
		debug_sendLine(title, menuKey, " (", description, ")", withDebugPrefix);
	}
	else {
		const char* hexAppMode = string::hex(appMode).toCharArray();
		debug_sendLine(title, " 0x", hexAppMode, withDebugPrefix);
	}
}

}	// microbit_dal_ext_kit
