/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Component - the root base class for any Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitComponent.h"	// self
#include "ExtKit.h"

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
	, mStatus(0)
{
	EXT_KIT_ASSERT_SAFE_CLASS_OBJECT(name, this);
}

Component::~Component()
{
}

void Component::start()
{
	if(mStatus & kStatusActive) {
		return;
	}

	restart();
}

void Component::restart()
{
	if(mStatus & kStatusStarting) {
		return;
	}

	mStatus |= kStatusStarting;
	doStart();
	mStatus &= ~kStatusStarting;

	mStatus |= kStatusActive;
}

void Component::stop()
{
	if(!(mStatus & kStatusActive)) {
		return;
	}
	if(mStatus & kStatusStopping) {
		return;
	}

	mStatus |= kStatusStopping;
	doStart();
	mStatus &= ~kStatusStopping;

	mStatus &= ~kStatusActive;
}

/**	@class	CompositeComponent
*/

CompositeComponent::CompositeComponent(const char* name)
	: Component(name)
{
}

void CompositeComponent::addChild(Component& component)
{
	Node* p = new ComponentRecord(component);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(mRoot);
}

void CompositeComponent::removeChild(Component& component)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		ComponentRecord* r = static_cast<ComponentRecord*>(p);
		if(&(r->component) == &component) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

void CompositeComponent::startChildren()
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		ComponentRecord* r = static_cast<ComponentRecord*>(p);
		r->component.start();
	}
}

void CompositeComponent::stopChildren()
{
	Node* p = &mRoot;
	while((p = p->prev) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		ComponentRecord* r = static_cast<ComponentRecord*>(p);
		r->component.stop();
	}
}

/**	@class	CompositeComponent::ComponentRecord
*/

CompositeComponent::ComponentRecord::ComponentRecord(Component& component)
	: component(component)
{
}

}	// microbit_dal_ext_kit
