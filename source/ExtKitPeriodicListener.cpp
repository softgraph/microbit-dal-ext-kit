/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Periodic Listener component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitPeriodicListener.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@struct PeriodicListener::HandlerRecord
*/

PeriodicListener::HandlerRecord::HandlerRecord()
	: Node()
{
	this->unit		= kUnit100ms;
	this->function	= 0;
	this->protocol	= 0;
	this->priority	= PeriodicListener::kHandlerPriorityVeryLow;
}

PeriodicListener::HandlerRecord::HandlerRecord(PeriodUnit unit, HandlerFunction* function, HandlerPriority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= function;
	this->protocol	= 0;
	this->priority	= priority;
}

PeriodicListener::HandlerRecord::HandlerRecord(PeriodUnit unit, HandlerProtocol* protocol, HandlerPriority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= 0;
	this->protocol	= protocol;
	this->priority	= priority;
}

/**	@class PeriodicListener
*/

PeriodicListener::HandlerRecord PeriodicListener::sRoot;

void PeriodicListener::registerHandler(PeriodUnit unit, HandlerFunction* function, HandlerPriority priority)
{
	Node* p = new HandlerRecord(unit, function, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(sRoot);
}

void PeriodicListener::registerHandler(PeriodUnit unit, HandlerProtocol* protocol, HandlerPriority priority)
{
	Node* p = new HandlerRecord(unit, protocol, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(sRoot);
}

int /* result */ PeriodicListener::unregisterHandler(PeriodUnit unit, HandlerFunction* function)	// returns MICROBIT_NO_DATA or MICROBIT_OK
{
	Node* p = &sRoot;
	while((p = p->next) != &sRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if((r->function == function) && (r->unit == unit)) {
			r->unlink();
			delete r;
			return MICROBIT_OK;
		}
	}
	return MICROBIT_NO_DATA;
}

int /* result */ PeriodicListener::unregisterHandler(PeriodUnit unit, HandlerProtocol* protocol)	// returns MICROBIT_NO_DATA or MICROBIT_OK
{
	Node* p = &sRoot;
	while((p = p->next) != &sRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if((r->protocol == protocol) && (r->unit == unit)) {
			r->unlink();
			delete r;
			return MICROBIT_OK;
		}
	}
	return MICROBIT_NO_DATA;
}

PeriodicListener::PeriodicListener()
	: Component("PeriodicListener")
{
}

void PeriodicListener::start()
{
	create_fiber(loop);
}

void PeriodicListener::loop()
{
	uint32_t count100ms = 0;
	while(true) {
		time::SystemTime t1 = time::systemTime();
		notify(count100ms, kUnit100ms);
		time::SystemTime t2 = time::systemTime();
		time::SystemTime t0 = t2 - t1;
		if(100 > t0) {
			time::sleep(100 - t0 /* milliseconds */);
		}
		else {
			time::sleep(0 /* milliseconds */);
		}
		count100ms++;
	}
}

void PeriodicListener::notify(uint32_t count, PeriodUnit unit)
{
	notify(count, unit, PeriodicListener::kHandlerPriorityVeryHigh);
	notify(count, unit, PeriodicListener::kHandlerPriorityHigh);
	notify(count, unit, PeriodicListener::kHandlerPriorityMedium);
	notify(count, unit, PeriodicListener::kHandlerPriorityLow);
	notify(count, unit, PeriodicListener::kHandlerPriorityVeryLow);
}

void PeriodicListener::notify(uint32_t count, PeriodUnit unit, HandlerPriority priority)
{
	Node* p = &sRoot;
	while((p = p->next) != &sRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		HandlerRecord* r = static_cast<HandlerRecord*>(p);
		if(r->unit != unit || r->priority != priority) {
			continue;
		}
		HandlerFunction* function = r->function;
		if(function) {
			(*function)(count, unit);
			continue;
		}
		HandlerProtocol* protocol = r->protocol;
		if(protocol) {
			protocol->handlePeriodicEvent(count, unit);
			continue;
		}
	}
}

}	// microbit_dal_ext_kit
