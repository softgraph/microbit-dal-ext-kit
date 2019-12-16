/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Statistics utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_STATISTICS_H
#define EXT_KIT_STATISTICS_H

#include "ExtKit_Common.h"
#include "ExtKitNode.h"

class ManagedString;

namespace microbit_dal_ext_kit {

///	Statistics utility
class Statistics
{
public:
	/// Increment item count
	static void incrementItem(const ManagedString& title);

	/// Set item value
	static void setItem(const ManagedString& title, uint16_t value);

	/// Send changed items to the debugger
	static void debug_sendItems();

private:
	/// Statistic Record
	struct StatisticRecord : public Node
	{
		const ManagedString&	title;
		uint16_t				count;
		uint16_t				total;

		StatisticRecord(const ManagedString& title);
	};	// StatisticRecord

	/// Prepare item
	static StatisticRecord& prepareItem(const ManagedString& title);

	/// Root Node for StatisticRecord
	static RootForDynamicNodes	sRoot;

};	// Statistics

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_STATISTICS_H
