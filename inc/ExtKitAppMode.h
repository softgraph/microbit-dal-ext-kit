/// Yotta module microbit-dal-ext-kit
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

/// An App Mode is a set of Features.
typedef Features	AppMode;

/// The Describer Protocol for App Mode.
/* abstract */ class AppModeDescriberProtocol
{
public:
	/// A character for App Mode.
	virtual /* to be implemented */ char charFor(AppMode appMode) const = 0;

	/// A name for App Mode.
	virtual /* to be implemented */ const char* nameFor(AppMode appMode) const = 0;

	/// Creates a new App Mode list which meets `condition`.
	virtual /* to be implemented */ int /* count */ appModesFor(Features condition, AppMode** /* OUT new */ appModes) const = 0;

};	// AppModeDescriberProtocol

/// Register App Mode Describer
void registerAppModeDescriber(const AppModeDescriberProtocol* describer);

/// App Mode Describer
const AppModeDescriberProtocol* appModeDescriber();

/// Select App Mode for the condition
void selectAppModeFor(Features condition);

/// Send App Moe information to the debugger.
void debug_sendAppMode(const char* title, AppMode appMode, bool withDebugPrefix = true);

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_APP_MODE_H
