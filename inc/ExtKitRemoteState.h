/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Remote State components
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_REMOTE_STATE_H
#define EXT_KIT_REMOTE_STATE_H

#include "ManagedString.h"

#include "ExtKitComponent.h"
#include "ExtKitNode.h"
#include "ExtKitPeriodicObserver.h"
#include "ExtKitTime.h"
#include "ExtKitState.h"

class MicroBitEvent;

namespace microbit_dal_ext_kit {

/// Remote %State components
namespace remoteState {

/// Remote %State Request Marker
/**
	The radio command with the marker, sent by the Remote %State Receiver, is as follows: <br>
	CATEGORY_CHARACTER `#kMarkerRequest`
*/
const char kMarkerRequest		= '?';

/// Remote %State Response Marker followed by a sequence number
/**
	The radio command with the marker, sent by the Remote %State Transmitter, is as follows: <br>
	CATEGORY_CHARACTER `#kMarkerResponse` [0-9a-f]+ (OTHER_MARKER_CHARACTER [0-9a-f]+)+
*/
const char kMarkerResponse		= '!';

/// Remote %State Notification Marker followed by a sequence number
/**
	The radio command with the marker, sent by the Remote %State Transmitter, is as follows: <br>
	CATEGORY_CHARACTER `#kMarkerNotification` [0-9a-f]+ (OTHER_MARKER_CHARACTER [0-9a-f]+)+
*/
const char kMarkerNotification	= '@';

/// An ext-kit Component which provides the Remote %State Transmitter
class Transmitter : public Component
{
public:
	/// Get global instance. Valid only after an instance of class `Transmitter` is created.
	static Transmitter& global();

	/// Constructor
	Transmitter();

	/// Destructor
	~Transmitter();

	/// Category Protocol
	/* interface */ class CategoryProtocol
	{
	public:
		/// Remote State to be sent
		virtual /* to be implemented */ ManagedString remoteState() = 0;

	};	// CategoryProtocol

	/// Category Base
	/* abstract */ class CategoryBase : public CategoryProtocol
	{
	protected:
		/// Constructor
		CategoryBase(char category);

		/// Transmitter
		Transmitter&	mTransmitter;

		/// Category
		char	mCategory;

	};	// CategoryBase

	/// Listen
	void listen(char category, CategoryProtocol& transmitter);

	/// Ignore
	void ignore(char category);

	/// Request To Send
	void requestToSend(char category);

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

private:
	/// Category Record
	struct CategoryRecord : public Node
	{
	public:
		/// Constructor
		CategoryRecord(char category, CategoryProtocol& protocol);

		/// Request To Send
		void requestToSend(bool asResponse);

		/// Send
		void send(const ManagedString& remoteState, bool asResponse);

		/// Handle Radio Command Received
		void handleRadioCommandReceived(ManagedString& received);

		/// Category Protocol
		CategoryProtocol&	protocol;

		/// Category
		char	category;

	private:
		/// Sequence Number
		uint8_t		mSequence;

	};	// CategoryRecord

	/// Handle Radio Datagram Received
	void handleRadioDatagramReceived(MicroBitEvent event);

	/// Global instance
	static Transmitter*	sGlobal;

	/// Root Node for CategoryRecord
	RootForDynamicNodes	mRoot;

};	// Transmitter

/// An ext-kit Component which provides the Remote %State Receiver
class Receiver : public Component, PeriodicObserver::HandlerProtocol
{
public:
	/// Get global instance. Valid only after an instance of class `Receiver` is created.
	static Receiver& global();

	/// Constructor
	Receiver();

	/// Destructor
	~Receiver();

	/// Category Protocol
	/* interface */ class CategoryProtocol
	{
	public:
		/// Handle Remote State received
		virtual /* to be implemented */ void handleRemoteState(ManagedString& received) = 0;

	};	// CategoryProtocol

	/// Category Base
	/* abstract */ class CategoryBase : public CategoryProtocol
	{
	protected:
		/// Constructor
		CategoryBase(char category);

		/// Receiver
		Receiver&	mReceiver;

		/// Category
		char	mCategory;

	};	// CategoryBase

	/// Listen
	void listen(char category, CategoryProtocol& receiver);

	/// Ignore
	void ignore(char category);

protected:
	/// Inherited
	/* Component */ void doHandleComponentAction(Action action);

private:
	/// Category Record
	struct CategoryRecord : public Node
	{
	public:
		/// Constructor
		CategoryRecord(char category, CategoryProtocol& protocol);

		/// Request To Send
		void requestToSend();

		/// Handle Radio Command Received
		void handleRadioCommandReceived(ManagedString& received);

		/// Handle Periodic Event
		void handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit);

	public:
		/// Category Protocol
		CategoryProtocol&	protocol;

		/// Category
		char	category;

	private:
		/// Sequence Number
		State<uint8_t>	mSequence;

		/// Sync Duration in `PeriodicObserver::kUnit100ms`
		uint16_t	mSyncDuration;

		/// Sync Next Count in `PeriodicObserver::kUnit100ms`
		uint32_t	mSyncNextCount;

		/// Statistics Key String for Sync Duration
		ManagedString	mStatisticsSyncDuration;

		/// Statistics Key String for Recovery Count
		ManagedString	mStatisticsRecoveryCount;

	};	// CategoryRecord

	/// Handle Radio Datagram Received
	void handleRadioDatagramReceived(MicroBitEvent event);

	/// Inherited
	/* PeriodicObserver::HandlerProtocol */ void handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit);

	private:
	/// Global instance
	static Receiver*	sGlobal;

	/// Root Node for CategoryRecord
	RootForDynamicNodes mRoot;

};	// Receiver

}	// remoteState
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_REMOTE_STATE_H
