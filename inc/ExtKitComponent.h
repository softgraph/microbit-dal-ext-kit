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

/// The root base class for any ext-kit Component. A Component is a small service provider and controlled by start() and stop().
/* abstract */ class Component
{
	friend class CompositeComponent;

public:
	/// Virtual Destructor
	virtual ~Component();

	/// Start service
	void start();

	/// Restart service
	void restart();

	/// Stop service
	void stop();

protected:
	/// Component Status: The component is inacive.
	static const uint16_t kStatusInactive	= 0;

	/// Component Status Bit: The component is acive, i.e. started.
	static const uint16_t kStatusActive		= 1 << 0;

	/// Component Status Bit: The component is starting.
	static const uint16_t kStatusStarting	= 1 << 1;

	/// Component Status Bit: The component is stopping.
	static const uint16_t kStatusStopping	= 1 << 2;

	/// Component Action
	enum Action {
		/* kPrestart, kStart and kPoststart are invoked within start() */
		kPrestart	= kStatusStarting,					///< Prestart
		kStart		= kStatusActive + kStatusStarting,	///< Start
		kPoststart	= kStatusActive,					///< Poststart

		/* kPrestop, kStop and kPoststop are invoked within stop() */
		kPrestop	= kStatusActive + kStatusStopping,	///< Prestop
		kStop		= kStatusStopping,					///< Stop
		kPoststop	= kStatusInactive					///< PostStop
	};

	/// Constructor
	Component(const char* name);

	/// Do Handle Component Action
	virtual /* Component */ void doHandleComponentAction(Action action);

	/// Component Name
	const char*	mName;

	/// Component Status Bits
	uint16_t	mStatus;

};	// Component

/// The base class for any ext-kit Component which has child Component(s)
/* abstract */ class CompositeComponent : public Component
{
protected:
	/// Constructor
	CompositeComponent(const char* name);

	/// Add Child Component
	void addChild(Component& component);

	/// Remove Child Component
	void removeChild(Component& component);

	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

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

	/// Root Node for ComponentRecord
	RootForDynamicNodes	mRoot;

};	// CompositeComponent

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_COMPONENT_H
