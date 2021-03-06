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

Component::Component(const char* name)
	: mName(name)
	, mStatus(kStatusInactive)
{
	EXT_KIT_ASSERT_SAFE_CLASS_OBJECT(name, this);
}

Component::~Component()
{
}

void Component::start()
{
	if(mStatus != kStatusInactive) {
		return;
	}

	restart();
}

void Component::restart()
{
	doHandleComponentAction(kPrestart);
	doHandleComponentAction(kStart);
	doHandleComponentAction(kPoststart);
}

void Component::stop()
{
	if(mStatus == kStatusInactive) {
		// nothing to do
		return;
	}

	doHandleComponentAction(kPrestop);
	doHandleComponentAction(kStop);
	doHandleComponentAction(kPoststop);
}

/* Component */ void Component::doHandleComponentAction(Action action)
{
	mStatus = action;
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
	EXT_KIT_ASSERT_OR_PANIC(p, panic::kOutOfMemory);

	p->linkBefore(mRoot);
}

void CompositeComponent::removeChild(Component& component)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		ComponentRecord* r = static_cast<ComponentRecord*>(p);
		if(&(r->component) == &component) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

/* Component */ void CompositeComponent::doHandleComponentAction(Action action)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		ComponentRecord* r = static_cast<ComponentRecord*>(p);
		r->component.doHandleComponentAction(action);
	}

	/* super */ Component::doHandleComponentAction(action);
}

/**	@class	CompositeComponent::ComponentRecord
*/

CompositeComponent::ComponentRecord::ComponentRecord(Component& component)
	: component(component)
{
}

}	// microbit_dal_ext_kit
