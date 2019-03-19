/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Feature utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitFeature.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace feature {

static Features sConfiguredFeatures = 0;

void setConfigured(Features features)
{
	sConfiguredFeatures |= features;
}

bool isConfigured(Features features)
{
	return((sConfiguredFeatures & features) == features);
}

Features configured()
{
	return sConfiguredFeatures;
}

}	// feature
}	// microbit_dal_ext_kit
