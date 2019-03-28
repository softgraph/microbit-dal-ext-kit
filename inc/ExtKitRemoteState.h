/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Remote State Component
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

/*
	Extern Template Instantiation for class `State<T>`
*/

extern template class State<uint8_t>;

/// Remote State utility
/* abstract */ class RemoteState
{
public:
	/// Remote State Request Marker
	/**
		The radio command with the marker, sent by the Remote State Receiver, is as follows:<br>
		CategoryCharacter `kMarkerRequest`
	*/
	static const char kMarkerRequest		= '?';

	/// Remote State Response Marker followed by a sequence number
	/**
		The radio command with the marker, sent by the Remote State Transmitter, is as follows:<br>
		CategoryCharacter `kMarkerResponse` [0-9a-f]+ (OtherMarkerCharacter [0-9a-f]+)+
	*/
	static const char kMarkerResponse		= '!';

	/// Remote State Notification Marker followed by a sequence number
	/**
		The radio command with the marker, sent by the Remote State Transmitter, is as follows:<br>
		CategoryCharacter `kMarkerNotification` [0-9a-f]+ (OtherMarkerCharacter [0-9a-f]+)+
	*/
	static const char kMarkerNotification	= '@';

	/// Transmitter Component
	class Transmitter : public Component
	{
	public:
		/// Get global instance. Valid only after an instance of class `RemoteState` is created.
		static Transmitter& global();

		/// Inherited
		static /* Component */ bool isConfigured();

		/// Constructor
		Transmitter();

		/// Protocol
		/* interface */ class Protocol
		{
		public:
			/// Remote State to be sent
			virtual /* to be implemented */ ManagedString remoteState() = 0;

		};	// Protocol

		/// Listen
		void listen(char category, Protocol& transmitter);

		/// Ignore
		void ignore(char category);

		/// Request To Send
		void requestToSend(char category);

	protected:
		/// Inherited
		/* Component */ void doStart();

		/// Inherited
		/* Component */ void doStop();

	private:
		/// Record
		struct Record : public Node
		{
		public:
			/// Constructor
			Record(char category, Protocol& protocol);

			/// Request To Send
			void requestToSend(bool asResponse);

			/// Send
			void send(const ManagedString& remoteState, bool asResponse);

			/// Handle Radio Command Received
			void handleRadioCommandReceived(ManagedString& received);

			/// Protocol
			Protocol&	protocol;

			/// Category
			char	category;

		private:
			/// Sequence Number
			uint8_t		mSequence;

		};	// Record

		/// Handle Radio Datagram Received
		void handleRadioDatagramReceived(MicroBitEvent event);

		/// Global instance
		static Transmitter*	sGlobal;

		/// Root Node for `Record`
		RootForDynamicNodes	mRoot;

	};	// Transmitter

	/// Receiver Component
	class Receiver : public Component, PeriodicObserver::Handler::Protocol
	{
	public:
		/// Get global instance. Valid only after an instance of class `RemoteState` is created.
		static Receiver& global();

		/// Inherited
		static /* Component */ bool isConfigured();

		/// Constructor
		Receiver();

		/// Protocol
		/* interface */ class Protocol
		{
		public:
			/// Handle Remote State received
			virtual /* to be implemented */ void handleRemoteState(ManagedString& received) = 0;

		};	// Protocol

		/// Listen
		void listen(char category, Protocol& receiver);

		/// Ignore
		void ignore(char category);

	protected:
		/// Inherited
		/* Component */ void doStart();

		/// Inherited
		/* Component */ void doStop();

	private:
		/// Record
		struct Record : public Node
		{
		public:
			/// Constructor
			Record(char category, Protocol& protocol);

			/// Request To Send
			void requestToSend();

			/// Handle Radio Command Received
			void handleRadioCommandReceived(ManagedString& received);

			/// Handle Periodic Event
			void handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit);

		public:
			/// Protocol
			Protocol&	protocol;

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

		};	// Record

		/// Handle Radio Datagram Received
		void handleRadioDatagramReceived(MicroBitEvent event);

		/// Inherited
		/* PeriodicObserver::Handler::Protocol */ void handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit);

		private:
		/// Global instance
		static Receiver*	sGlobal;

		/// Root Node for `Record`
		RootForDynamicNodes mRoot;

	};	// Receiver

};	// RemoteState

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_REMOTE_STATE_H
