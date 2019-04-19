/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Component - the root base class for any Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_COMPONENT_H
#define EXT_KIT_COMPONENT_H

#include "ExtKitFeature.h"
#include "ExtKitNode.h"

namespace microbit_dal_ext_kit {

/// Component - the root base class for any #Component
/* abstract */ class Component
{
public:
	/// Check that the required hardware/software resources are avaialable and return available Features.
	static /* to be overridden */ Features avaiableFeatures();

	/// Check that the required Features are configured
	static /* to be overridden */ bool isConfigured();

	/// Virtual Destructor
	virtual ~Component();

	/// Start service
	void start();

	/// Restart service
	void restart();

	/// Stop service
	void stop();

protected:
	/// Constructor
	Component(const char* name);

	/// Do start service
	virtual /* to be overridden */ void doStart()	{ /* nothing to do */ }

	/// Do stop service
	virtual /* to be overridden */ void doStop()	{ /* nothing to do */ }

	/// Status Bit: The component is acive, i.e. started.
	static const uint16_t kStatusActive = 1 << 0;

	/// Status Bit: The component is starting.
	static const uint16_t kStatusStarting = 1 << 1;

	/// Status Bit: The component is stopping.
	static const uint16_t kStatusStopping = 1 << 2;

	/// Component Name
	const char*	mName;

	/// Status Bits
	uint16_t	mStatus;

};	// Component

/// Composite Component
class CompositeComponent : public Component
{
protected:
	/// Constructor
	CompositeComponent(const char* name);

	/// Add Child Component
	void addChild(Component& component);

	/// Remove Child Component
	void removeChild(Component& component);

	/// Start Children
	void startChildren();

	/// Stop Children
	void stopChildren();

private:
	/// Component Record
	struct ComponentRecord : public Node
	{
	public:
		/// Constructor
		ComponentRecord(Component& component);

		/// Component
		Component&	component;

	};	// ComponentRecord

	/// Root Node for `ComponentRecord`
	RootForDynamicNodes	mRoot;

};	// CompositeComponent

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_COMPONENT_H
