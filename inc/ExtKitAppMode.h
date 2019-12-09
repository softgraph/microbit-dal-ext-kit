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

///	App Mode utility
namespace appMode {

/// Set Active Mode
void setActiveMode(AppMode appMode);

/// Active Mode
AppMode activeMode();

/// The Describer Protocol for App Mode
/* interface */ class DescriberProtocol
{
public:
	/// Menu Key Hints
	/**	Returns an array of hint strings terminated by a null pointer. A hint string consists of the following three parts for a sub-menu item.
		- Character 0: A menu key character
		- Character 1: Available sub-menu depth - one of '0'-'9' or '*'
		- Character 2-: A hint description
	*/
	virtual /* to be implemented */ const char* const * hints() const = 0;

	/// A short menu key string uniquely summarizes an App Mode
	virtual /* to be implemented */ const char* menuKeyFor(AppMode appMode) const = 0;

	/// A description for an App Mode
	virtual /* to be implemented */ const char* descriptionFor(AppMode appMode) const = 0;

	/// Creates a new array of App Modes which meets `condition` and `menuKeyFilter`
	virtual /* to be implemented */ int /* count */ appModesFor(AppMode condition, const char* menuKeyFilter, AppMode** /* OUT new[] */ outAppModes) const = 0;

};	// DescriberProtocol

/// Active App Mode Describer
/**	Returns null until `appMode::registerDescriber()` or `appMode::selectFor()` is called.
*/
const DescriberProtocol* describer();

/// Register an App Mode Describer
void registerDescriber(const DescriberProtocol& describer);

/// Select an App Mode match for the condition or allow the user to choose an App Mode
void selectFor(AppMode condition, const DescriberProtocol& describer);

/// Send App Mode information to the debugger
void debug_sendAppMode(const char* title, AppMode appMode, bool withDebugPrefix = true);

}	// appMode
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_APP_MODE_H
