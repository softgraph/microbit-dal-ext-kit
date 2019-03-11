/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Periodic Listener component
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

/// Periodic Listener Component
class PeriodicListener : public Component
{
public:
	/// Period Unit
	enum PeriodUnit {
		kUnit100ms
	};

	/// Handler
	typedef void Handler(uint32_t count, PeriodUnit unit);

	/// Handler Protocol
	/* virtual */ class HandlerProtocol
	{
	public:
		virtual /* to be implemented */ void handlePeriodicEvent(uint32_t count, PeriodUnit unit) = 0;

	};	// HandlerProtocol

	/// Handler Priority
	enum HandlerPriority {
		kHandlerPriorityVeryLow,
		kHandlerPriorityLow,
		kHandlerPriorityMedium,
		kHandlerPriorityHigh,
		kHandlerPriorityVeryHigh
	};

	/// Register Periodic Handler
	static void registerHandler(PeriodUnit unit, Handler* handler, HandlerPriority priority = kHandlerPriorityMedium);

	/// Register Periodic Handler Protocol
	static void registerHandler(PeriodUnit unit, HandlerProtocol* protocol, HandlerPriority priority = kHandlerPriorityMedium);

	/// Unregister Periodic Handler
	static int /* result */ unregisterHandler(PeriodUnit unit, Handler* handler);	// returns MICROBIT_NO_DATA or MICROBIT_OK

	/// Unregister Periodic Handler
	static int /* result */ unregisterHandler(PeriodUnit unit, HandlerProtocol* protocol);	// returns MICROBIT_NO_DATA or MICROBIT_OK

	/// Constructor.
	PeriodicListener();

	/// Inherited.
	/* Component */ void start();

private:
	/// Handler Record
	struct HandlerRecord : public Node
	{
		PeriodUnit			unit;
		Handler* 			handler;
		HandlerProtocol*	protocol;
		HandlerPriority		priority;

		HandlerRecord();
		HandlerRecord(PeriodUnit unit, Handler* handler, HandlerPriority priority);
		HandlerRecord(PeriodUnit unit, HandlerProtocol* protocol, HandlerPriority priority);
	};

	static HandlerRecord sRoot;

	static void loop();
	static void notify(uint32_t count, PeriodUnit unit);
	static void notify(uint32_t count, PeriodUnit unit, HandlerPriority priority);

};	// PeriodicListener

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_PERIODIC_LISTENER_H
