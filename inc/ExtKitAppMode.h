/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// App Mode utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_APP_MODE_H
#define EXT_KIT_APP_MODE_H

#include "ExtKitFeature.h"

namespace microbit_dal_ext_kit {

/// App Mode
typedef uint32_t	AppMode;

/// Set App Mode
void setAppMode(AppMode appMode);

/// App Mode
AppMode appMode();

/// The Describer Protocol for App Mode
/* interface */ class AppModeDescriberProtocol
{
public:
	/// Hints for Menu Keys
	/**	An array of hint strings terminated by a null pointer. A hint string consists of the following three parts.
		- A character in any menu key
		- A position ('0'-'9' or '*') of the character in any menu key
		- the hint about the character
	*/
	virtual /* to be implemented */ const char* const * hints() const = 0;

	/// A menu key for an App Mode
	virtual /* to be implemented */ const char* menuKeyFor(AppMode appMode) const = 0;

	/// A description for an App Mode
	virtual /* to be implemented */ const char* descriptionFor(AppMode appMode) const = 0;

	/// Creates a new array of App Modes which meets `condition` and `menuKeyFilter`
	virtual /* to be implemented */ int /* count */ appModesFor(AppMode condition, const char* menuKeyFilter, AppMode** /* OUT new[] */ outAppModes) const = 0;

};	// AppModeDescriberProtocol

/// Active App Mode Describer.
const AppModeDescriberProtocol* appModeDescriber();	// returns null until `registerAppModeDescriber()` or `selectAppModeFor()` is called

/// Register App Mode Describer
void registerAppModeDescriber(const AppModeDescriberProtocol& describer);

/// Select App Mode for the condition
void selectAppModeFor(AppMode condition, const AppModeDescriberProtocol& describer);

/// Send App Mode information to the debugger
void debug_sendAppMode(const char* title, AppMode appMode, bool withDebugPrefix = true);

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_APP_MODE_H
