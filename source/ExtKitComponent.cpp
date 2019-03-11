/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Component. The root base class for any Component.
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitComponent.h"	// self
#include "ExtKit_System.h"

namespace microbit_dal_ext_kit {

/**	@class	Component
*/

/* to be overridden */ Features Component::avaiableFeatures()
{
	return 0;	// not available
}

/* to be overridden */ bool Component::isConfigured()
{
	return false;	// not yet configured
}

Component::Component(const char* name)
	: mName(name)
{
	EXT_KIT_ASSERT_SAFE_CLASS_OBJECT(name, this);
}

Component::~Component()
{
}

/* to be overridden */ void Component::start()
{
	// nothing to do
}

/* to be overridden */ void Component::stop()
{
	// nothing to do
}

}	// microbit_dal_ext_kit
