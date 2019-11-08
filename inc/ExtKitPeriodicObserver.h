/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
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
#include "ExtKitError.h"
#include "ExtKitNode.h"
#include "ExtKitRequest.h"

namespace microbit_dal_ext_kit {

/// An ext-kit Component which provides observer service invoked periodically
class PeriodicObserver : public Component, RequestCompletionProtocol
{
public:
	/// Period Unit
	enum PeriodUnit {
		/// Never
		kUnitNever,
		/// 100 milliseconds
		kUnit100ms,
		/// 20 milliseconds
		kUnit20ms
	};

	/// Handler Function
	typedef void HandlerFunction(uint32_t count, PeriodUnit unit);

	/// Handler Protocol
	/* interface */ class HandlerProtocol
	{
	public:
		/// Handle Periodic Event
		virtual /* to be implemented */ void handlePeriodicEvent(uint32_t count, PeriodUnit unit) = 0;

	};	// HandlerProtocol

	/// Handler Priority
	enum HandlerPriority {
		kPriorityVeryLow,
		kPriorityLow,
		kPriorityMedium,
		kPriorityHigh,
		kPriorityVeryHigh
	};

	/// Get global instance. Valid only after an instance of class `PeriodicObserver` is created.
	static PeriodicObserver& global();

	/// Constructor
	PeriodicObserver();

	/// Destructor
	~PeriodicObserver();

	/// Request value: Request To Cancel. Expected response value: MICROBIT_CANCELLED.
	const int kRequestToCancel = 1;

	/// Inherited. Note that `request` should be retained until `waitForCompletion()` is returned.
	/* RequestCompletionProtocol */ int /* result */ issueRequest(RequestToken& request);

	/// Inherited.
	/* RequestCompletionProtocol */ RequestToken& /* response */ waitForCompletion();

	/// Listen using Function
	static void listen(PeriodUnit unit, HandlerFunction& function, HandlerPriority priority = kPriorityMedium);

	/// Listen using Protocol
	static void listen(PeriodUnit unit, HandlerProtocol& protocol, HandlerPriority priority = kPriorityMedium);

	/// Ignore Function
	static void ignore(PeriodUnit unit, HandlerFunction& function);

	/// Ignore Protocol
	static void ignore(PeriodUnit unit, HandlerProtocol& protocol);

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

private:
	/// Handler Record
	struct HandlerRecord : public Node
	{
		/// Period Unit
		PeriodUnit			unit;

		/// Function
		HandlerFunction* 	function;

		/// Protocol
		HandlerProtocol*	protocol;

		/// Priority
		HandlerPriority		priority;

		/// Constructor
		HandlerRecord(PeriodUnit unit, HandlerFunction& function, HandlerPriority priority);

		/// Constructor
		HandlerRecord(PeriodUnit unit, HandlerProtocol& protocol, HandlerPriority priority);

	};	// HandlerRecord

	/// The Main Loop Entry
	static void loopEntry(void* param);

	/// The Main Loop
	void loop();

	/// Count Target handlers for a Period Unit
	int countTarget(PeriodUnit unit);

	/// Notify Periodic Event
	void notify(uint32_t count, PeriodUnit unit);

	/// Notify Periodic Event
	int notify(uint32_t count, PeriodUnit unit, HandlerPriority priority);

	/// Global instance
	static PeriodicObserver*	sGlobal;

	/// Running
	bool	mRunning;

	/// Request To Cancel
	bool	mRequestToCancel;

	/// Request Token
	RequestToken*	mRequestToken;

	/// Root Node for `HandlerRecord`
	RootForDynamicNodes		mRoot;

};	// PeriodicObserver

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_PERIODIC_LISTENER_H
