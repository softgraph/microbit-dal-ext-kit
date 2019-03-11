/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Component. The root base class for any Component.
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_COMPONENT_H
#define EXT_KIT_COMPONENT_H

#include "ExtKitFeature.h"

namespace microbit_dal_ext_kit {

/// Component. The root base class for any Component.
/* virtual */ class Component
{
public:
	/// Check that the required hardware/software resources are avaialable and return available Features.
	static /* to be overridden */ Features avaiableFeatures();

	/// Check that the required Features are configured.
	static /* to be overridden */ bool isConfigured();

	/// Constructor.
	Component(const char* name);

	/// Destructor.
	virtual ~Component();

	/// Start the service.
	virtual /* to be overridden */ void start();

	/// Stop the service.
	virtual /* to be overridden */ void stop();

protected:
	const char* mName;

};	// Component

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_COMPONENT_H
