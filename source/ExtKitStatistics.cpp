/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Statistics utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitStatistics.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@struct StatisticRecord
*/

Statistics::StatisticRecord::StatisticRecord(const ManagedString& title)
	: Node()
	, title(title)
	, count(0)
	, total(0)
{
}

/**	@class Statistics
*/

RootForDynamicNodes	Statistics::sRoot;

void Statistics::incrementItem(const ManagedString& title)
{
	StatisticRecord& r = prepareItem(title);
	r.count++;
}

void Statistics::setItem(const ManagedString& title, uint16_t value)
{
	StatisticRecord& r = prepareItem(title);
	r.count = value;
}

void Statistics::debug_sendItems()
{
	Node* p = &sRoot;
	while((p = p->next) != &sRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		StatisticRecord* r = static_cast<StatisticRecord*>(p);
		if(!r->count) {
			continue;
		}
		uint16_t count = r->count;
		r->count = 0;
		r->total += count;
		debug_sendLine(EXT_KIT_DEBUG_STATISTICS, r->title.toCharArray(), "\t0x", string::hex(count).toCharArray());
		// incrementItem() may be called inside this debug_sendLine() call.
	}
}

Statistics::StatisticRecord& Statistics::prepareItem(const ManagedString& title)
{
	Node* p = &sRoot;
	while((p = p->next) != &sRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		StatisticRecord* r = static_cast<StatisticRecord*>(p);
		if(&(r->title) == &title) {
			return *r;
		}
	}

	StatisticRecord* r = new StatisticRecord(title);
	EXT_KIT_ASSERT_OR_PANIC(r, panic::kOutOfMemory);

	r->linkBefore(sRoot);
	return *r;
}

}	// microbit_dal_ext_kit
