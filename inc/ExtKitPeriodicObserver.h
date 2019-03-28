/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Periodic Observer component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_PERIODIC_LISTENER_H
#define EXT_KIT_PERIODIC_LISTENER_H

#include "ExtKitComponent.h"
#include "ExtKitNode.h"

namespace microbit_dal_ext_kit {

/// Periodic Observer Component
class PeriodicObserver : public Component
{
	friend class Handler;

public:
	/// Period Unit
	enum PeriodUnit {
		/// 100 milliseconds
		kUnit100ms
	};

	/// Handler
	/* abstract */ class Handler
	{
		friend class PeriodicObserver;

	public:
		/// Function
		typedef void Function(uint32_t count, PeriodUnit unit);

		/// Protocol
		/* interface */ class Protocol
		{
		public:
			virtual /* to be implemented */ void handlePeriodicEvent(uint32_t count, PeriodUnit unit) = 0;

		};	// Protocol

		/// Priority
		enum Priority {
			kPriorityVeryLow,
			kPriorityLow,
			kPriorityMedium,
			kPriorityHigh,
			kPriorityVeryHigh
		};

		/// Listen using Function
		static void listen(PeriodUnit unit, Function& function, Priority priority = kPriorityMedium);

		/// Listen using Protocol
		static void listen(PeriodUnit unit, Protocol& protocol, Priority priority = kPriorityMedium);

		/// Ignore Function
		static void ignore(PeriodUnit unit, Function& function);

		/// Ignore Protocol
		static void ignore(PeriodUnit unit, Protocol& protocol);

	private:
		/// Record
		struct Record : public Node
		{
			/// Period Unit
			PeriodUnit	unit;

			/// Function
			Function* 	function;

			/// Protocol
			Protocol*	protocol;

			/// Priority
			Priority	priority;

			/// Constructor
			Record(PeriodUnit unit, Function& function, Priority priority);

			/// Constructor
			Record(PeriodUnit unit, Protocol& protocol, Priority priority);

		};	// Record

	};	// Handler

	/// Get global instance. Valid only after an instance of class `PeriodicObserver` is created.
	static PeriodicObserver& global();

	/// Constructor
	PeriodicObserver();

protected:
	/// Inherited
	/* Component */ void doStart();

	/// Inherited
	/* Component */ void doStop();

private:
	/// The Main Loop Entry
	static void loopEntry(void* param);

	/// The Main Loop
	void loop();

	/// Notify Periodic Event
	void notify(uint32_t count, PeriodUnit unit);

	/// Notify Periodic Event
	void notify(uint32_t count, PeriodUnit unit, Handler::Priority priority);

	/// Global instance
	static PeriodicObserver*	sGlobal;

	/// Root Node for `Handler::Record`
	RootForDynamicNodes	mRoot;

};	// PeriodicObserver

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_PERIODIC_LISTENER_H
