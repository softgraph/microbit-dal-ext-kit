/// Yotta module microbit-dal-ext-kit
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
{
	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

/* Component */ void PeriodicObserver::doStart()
{
	create_fiber(loopEntry, this);
}

/* Component */ void PeriodicObserver::doStop()
{
	///	@todo	set a flag to stop `PeriodicObserver::loop()`
}

void PeriodicObserver::loopEntry(void* param)
{
	EXT_KIT_ASSERT(param);

	PeriodicObserver* p = static_cast<PeriodicObserver*>(param);
	p->loop();
}

void PeriodicObserver::loop()
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

void PeriodicObserver::notify(uint32_t count, PeriodUnit unit)
{
	notify(count, unit, Handler::kPriorityVeryHigh);
	notify(count, unit, Handler::kPriorityHigh);
	notify(count, unit, Handler::kPriorityMedium);
	notify(count, unit, Handler::kPriorityLow);
	notify(count, unit, Handler::kPriorityVeryLow);
}

void PeriodicObserver::notify(uint32_t count, PeriodUnit unit, Handler::Priority priority)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Handler::Record* r = static_cast<Handler::Record*>(p);
		if(r->unit != unit || r->priority != priority) {
			continue;
		}

		Handler::Function* function = r->function;
		if(function) {
			(*function)(count, unit);
			continue;
		}

		Handler::Protocol* protocol = r->protocol;
		if(protocol) {
			protocol->handlePeriodicEvent(count, unit);
			continue;
		}
	}
}

/**	@class PeriodicObserver::Handler
*/

void PeriodicObserver::Handler::listen(PeriodUnit unit, Function& function, Priority priority)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node* p = new Record(unit, function, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(g.mRoot);
}

void PeriodicObserver::Handler::listen(PeriodUnit unit, Protocol& protocol, Priority priority)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node* p = new Record(unit, protocol, priority);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(g.mRoot);
}

void PeriodicObserver::Handler::ignore(PeriodUnit unit, Function& function)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node& root = g.mRoot;
	Node* p = &root;
	while((p = p->next) != &root) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if((r->function == &function) && (r->unit == unit)) {
			r->unlink();
			delete r;
			break;
		}
	}
}

void PeriodicObserver::Handler::ignore(PeriodUnit unit, Protocol& protocol)
{
	PeriodicObserver& g = PeriodicObserver::global();
	Node& root = g.mRoot;
	Node* p = &root;
	while((p = p->next) != &root) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if((r->protocol == &protocol) && (r->unit == unit)) {
			r->unlink();
			delete r;
			break;
		}
	}
}

/**	@struct PeriodicObserver::Handler::Record
*/

PeriodicObserver::Handler::Record::Record(PeriodUnit unit, Function& function, Priority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= &function;
	this->protocol	= 0;
	this->priority	= priority;
}

PeriodicObserver::Handler::Record::Record(PeriodUnit unit, Protocol& protocol, Priority priority)
	: Node()
{
	this->unit		= unit;
	this->function	= 0;
	this->protocol	= &protocol;
	this->priority	= priority;
}

}	// microbit_dal_ext_kit
