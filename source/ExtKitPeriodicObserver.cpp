/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Periodic Observer component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitPeriodicObserver.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class PeriodicObserver
*/

PeriodicObserver* PeriodicObserver::sGlobal = 0;

PeriodicObserver& PeriodicObserver::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

PeriodicObserver::PeriodicObserver()
	: Component("PeriodicObserver")
	, mRunning(false)
	, mRequestToCancel(false)
	, mRequestToken(0)
{
	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

PeriodicObserver::~PeriodicObserver()
{
	if(sGlobal == this) {
		sGlobal = 0;
	}
}

/* RequestCompletionProtocol */ int /* result */ PeriodicObserver::issueRequest(RequestToken& request)
{
	if(request.value != kRequestToCancel) {
		return MICROBIT_NOT_SUPPORTED;	// Unknown request
	}

	if(mRequestToken) {
		return MICROBIT_BUSY;	// There's an active request
	}

	if(!mRunning) {
		return MICROBIT_NO_DATA;	// Not running
	}

	// The request is accepted
	mRequestToCancel = true;
	mRequestToken = &request;
	return MICROBIT_OK;
}

/* RequestCompletionProtocol */ RequestToken& /* response */ PeriodicObserver::waitForCompletion()
{
	while(mRunning || ! mRequestToken) {
		time::sleep(100 /* milliseconds */);
	}

	// The request is completed
	RequestToken& response = *mRequestToken;
	mRequestToken = 0;
	response.value = MICROBIT_CANCELLED;
	return response;
}

/* Component */ void PeriodicObserver::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		mRunning = true;
		mRequestToCancel = false;

		create_fiber(loopEntry, this);
	}
	else if(action == kStop) {
		if(mRunning) {
			// Request to cancel
			mRequestToCancel = true;

			// Wait for the completion
			while(mRunning) {
				time::sleep(100 /* milliseconds */);
			}
		}
	}

	Component::doHandleComponentAction(action);
}

void PeriodicObserver::loopEntry(void* param)
{
	EXT_KIT_ASSERT(param);

	// Start the loop
	PeriodicObserver* p = static_cast<PeriodicObserver*>(param);
	p->loop();
}

void PeriodicObserver::loop()
{
	// Be running the loop
	const time::SystemTime kNext = 20;
	time::SystemTime target = time::systemTime() + kNext;
	uint32_t count = 0;
	while(!mRequestToCancel) {
		notify(count, kUnit20ms);
		if((count % 5) == 4) {	// for each count 4, 9, 14, ...
			notify(count / 5, kUnit100ms);
		}
		time::SystemTime duration = time::durationFor(target);
		time::sleep(duration);
		target += kNext;
		count++;
	}

	// Canceled
	mRunning = false;
	mRequestToCancel = false;
}

int PeriodicObserver::countTarget(PeriodUnit unit)
{
	int targetCount = 0;
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if(r->unit == unit) {
			targetCount++;
		}
	}
	return targetCount;
}

void PeriodicObserver::notify(uint32_t count, PeriodUnit unit)
{
	int targetCount = countTarget(unit);
	if(targetCount <= 0) {
		return;
	}
	targetCount -= notify(count, unit, kPriorityVeryHigh);
	if(targetCount <= 0) {
		return;
	}
	targetCount -= notify(count, unit, kPriorityHigh);
	if(targetCount <= 0) {
		return;
	}
	targetCount -= notify(count, unit, kPriorityMedium);
	if(targetCount <= 0) {
		return;
	}
	targetCount -= notify(count, unit, kPriorityLow);
	if(targetCount <= 0) {
		return;
	}
	notify(count, unit, kPriorityVeryLow);
}

int PeriodicObserver::notify(uint32_t count, PeriodUnit unit, HandlerPriority priority)
{
	int targetCount = 0;
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if(r->unit != unit || r->priority != priority) {
			continue;
		}

		HandlerFunction* function = r->function;
		if(function) {
			(*function)(count, unit);
			targetCount++;
			continue;
		}

		HandlerProtocol* protocol = r->protocol;
		if(protocol) {
			protocol->handlePeriodicEvent(count, unit);
			targetCount++;
			continue;
		}
	}
	return targetCount;
}

void PeriodicObserver::listen(PeriodUnit unit, HandlerFunction& function, HandlerPriority priority)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node* p = new HandlerRecord(unit, function, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, panic::kOutOfMemory);

	p->linkBefore(g.mRoot);
}

void PeriodicObserver::listen(PeriodUnit unit, HandlerProtocol& protocol, HandlerPriority priority)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node* p = new HandlerRecord(unit, protocol, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, panic::kOutOfMemory);

	p->linkBefore(g.mRoot);
}

void PeriodicObserver::ignore(PeriodUnit unit, HandlerFunction& function)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node& root = g.mRoot;
	Node* p = &root;
	while((p = p->next) != &root) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if((r->function == &function) && (r->unit == unit)) {
			r->unlink();
			delete r;
			break;
		}
	}
}

void PeriodicObserver::ignore(PeriodUnit unit, HandlerProtocol& protocol)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node& root = g.mRoot;
	Node* p = &root;
	while((p = p->next) != &root) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if((r->protocol == &protocol) && (r->unit == unit)) {
			r->unlink();
			delete r;
			break;
		}
	}
}

/**	@struct PeriodicObserver::HandlerRecord
*/

PeriodicObserver::HandlerRecord::HandlerRecord(PeriodUnit unit, HandlerFunction& function, HandlerPriority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= &function;
	this->protocol	= 0;
	this->priority	= priority;
}

PeriodicObserver::HandlerRecord::HandlerRecord(PeriodUnit unit, HandlerProtocol& protocol, HandlerPriority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= 0;
	this->protocol	= &protocol;
	this->priority	= priority;
}

}	// microbit_dal_ext_kit
