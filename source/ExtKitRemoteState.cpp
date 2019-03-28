/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Remote State Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitRemoteState.h"	// self
#include "ExtKit.h"
#include "ExtKitState.cpp.h"

namespace microbit_dal_ext_kit {

/*
	Explicit Template Instantiation for class `State<T>`
*/

template class State<uint8_t>;

/**	@class	RemoteState::Transmitter
*/

static const Features kFeatureTx = feature::kRemoteStateTx;

RemoteState::Transmitter* RemoteState::Transmitter::sGlobal = 0;

RemoteState::Transmitter& RemoteState::Transmitter::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

/* Component */ bool RemoteState::Transmitter::isConfigured()
{
	return feature::isConfigured(kFeatureTx);
}

RemoteState::Transmitter::Transmitter()
	: Component("RemoteState::Transmitter")
{
	MicroBitRadio* r = ExtKit::global().radio();
	EXT_KIT_ASSERT(r);

	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

/* Component */ void RemoteState::Transmitter::doStart()
{
	// Listen to radio datagrams from the receiver
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &RemoteState::Transmitter::handleRadioDatagramReceived);

	radio::prepare();
}

/* Component */ void RemoteState::Transmitter::doStop()
{
	// Ignore radio datagrams from the receiver
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &RemoteState::Transmitter::handleRadioDatagramReceived);
}

void RemoteState::Transmitter::listen(char category, Protocol& protocol)
{
	Node* p = new Record(category, protocol);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(mRoot);
}

void RemoteState::Transmitter::ignore(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if(r->category == category) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

void RemoteState::Transmitter::requestToSend(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if(r->category == category) {
			r->requestToSend(/* asResponse*/ false);
			break;
		}
	}
}

void RemoteState::Transmitter::handleRadioDatagramReceived(MicroBitEvent /* event */)
{
	ManagedString received = radio::recv();
	if(received.length() <= 1) {
		return;
	}

	char category = received.charAt(0);
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if(r->category == category) {
			r->handleRadioCommandReceived(received);
			break;
		}
	}
}

/**	@class	RemoteState::Transmitter::Record
*/

RemoteState::Transmitter::Record::Record(char category, RemoteState::Transmitter::Protocol& protocol)
	: protocol(protocol)
	, category(category)
	, mSequence(0)
{
}

void RemoteState::Transmitter::Record::requestToSend(bool asResponse)
{
	ManagedString s = protocol.remoteState();
	send(s, asResponse);
}

void RemoteState::Transmitter::Record::send(const ManagedString& remoteState, bool asResponse)
{
	ManagedString s(category);
	char sequenceMarker;
	if(asResponse) {
		sequenceMarker = kMarkerResponse;
	}
	else {
		sequenceMarker = kMarkerNotification;
		mSequence++;
	}
	s =	s + string::hex(mSequence, sequenceMarker);
	s = s + remoteState;
	radio::send(s);
}

void RemoteState::Transmitter::Record::handleRadioCommandReceived(ManagedString& received)
{
	char marker = received.charAt(1);
	if(marker != kMarkerRequest) {
		return;
	}

	requestToSend(/* asResponse*/ true);
}

/**	@class	RemoteState::Receiver
*/

static const Features kFeatureRx = feature::kRemoteStateRx;

RemoteState::Receiver* RemoteState::Receiver::sGlobal = 0;

RemoteState::Receiver& RemoteState::Receiver::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

/* Component */ bool RemoteState::Receiver::isConfigured()
{
	return feature::isConfigured(kFeatureRx);
}

RemoteState::Receiver::Receiver()
	: Component("RemoteState::Receiver")
{
	MicroBitRadio* r = ExtKit::global().radio();
	EXT_KIT_ASSERT(r);

	EXT_KIT_ASSERT(!sGlobal);
	sGlobal = this;
}

/* Component */ void RemoteState::Receiver::doStart()
{
	radio::prepare();

	// Listen to radio datagrams from the transmitter
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &RemoteState::Receiver::handleRadioDatagramReceived);

	// Listen Periodic Observer
	PeriodicObserver::Handler::listen(PeriodicObserver::kUnit100ms, *this, PeriodicObserver::Handler::kPriorityLow);

//	debug_sendLine(EXT_KIT_DEBUG_TRACE "RemoteState::Receiver::doStart");
}

/* Component */ void RemoteState::Receiver::doStop()
{
	// Ignore Periodic Observer
	PeriodicObserver::Handler::listen(PeriodicObserver::kUnit100ms, *this);

	// Ignore radio datagrams from the transmitter
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &RemoteState::Receiver::handleRadioDatagramReceived);

//	debug_sendLine(EXT_KIT_DEBUG_TRACE "RemoteState::Receiver::doStop");
}

void RemoteState::Receiver::listen(char category, Protocol& protocol)
{
	Node* p = new Record(category, protocol);
	EXT_KIT_ASSERT_OR_PANIC(p, kPanicOutOfMemory);

	p->linkBefore(mRoot);
}

void RemoteState::Receiver::ignore(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if(r->category == category) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

void RemoteState::Receiver::handleRadioDatagramReceived(MicroBitEvent /* event */)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "RemoteState::Receiver::handleRadioDatagramReceived");

	ManagedString received = radio::recv();
	if(received.length() <= 1) {
		return;
	}

	char category = received.charAt(0);
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		if(r->category == category) {
			r->handleRadioCommandReceived(received);
			break;
		}
	}
}

/* PeriodicObserver::Handler::Protocol */ void RemoteState::Receiver::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), kPanicCorruptedNode);

		Record* r = static_cast<Record*>(p);
		r->handlePeriodicEvent(count, unit);
	}
}

/**	@class	RemoteState::Receiver::Record
*/

//																						 123456789abcdef0
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sStatisticsSyncDuration,	"\x10", " SyncDuration:  ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sStatisticsRecoveryCount,	"\x10", " RecoveryCount: ")

/// Initial Sync Duration in 100 milliseconds
static const uint16_t kSyncDurationInitial	= 4;

RemoteState::Receiver::Record::Record(char category, RemoteState::Receiver::Protocol& protocol)
	: protocol(protocol)
	, category(category)
	, mSequence(0)
	, mSyncDuration(0)
	, mSyncNextCount(0)
	, mStatisticsSyncDuration(ManagedString(category) + ManagedString(sStatisticsSyncDuration))
	, mStatisticsRecoveryCount(ManagedString(category) + ManagedString(sStatisticsSyncDuration))
{
}

void RemoteState::Receiver::Record::requestToSend()
{
	char buf[3] = { category, kMarkerRequest, 0 };
	ManagedString s(buf);
	radio::send(s);
}

void RemoteState::Receiver::Record::handleRadioCommandReceived(ManagedString& received)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "RemoteState::Receiver::Record::handleRadioCommandReceived");

	char marker = received.charAt(1);
	if((marker != kMarkerResponse) && (marker != kMarkerNotification)) {
		return;	// invalid command
	}

	uint8_t sequence = string::numberForHexString(received, 2);
	if(!(mSequence.set(sequence))) {
		uint16_t tmp = mSyncDuration;
		if(tmp < 0x8000) {
			mSyncDuration = tmp + tmp;
			mSyncNextCount = 0;
			Statistics::setItem(mStatisticsSyncDuration, mSyncDuration);
		}
		return;	// sequence number is not changed
	}

	mSyncDuration = kSyncDurationInitial;
	mSyncNextCount = 0;
	Statistics::setItem(mStatisticsSyncDuration, mSyncDuration);

	if(marker == kMarkerResponse) {
		Statistics::incrementItem(mStatisticsRecoveryCount);
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "RemoteState is rocovered by a response");
	}

	protocol.handleRemoteState(received);
}

void RemoteState::Receiver::Record::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit /* unit */)
{
	if(mSyncDuration == 0) {
		return;	// synchronization is not started
	}

	if(mSyncNextCount == 0) {
		mSyncNextCount = count + mSyncDuration;
		return;	// the next count is not set
	}

	uint32_t remainingCount = mSyncNextCount - count;
	if(remainingCount <= (uint32_t) INT32_MAX) {
		return;	// the next count is not reached
	}

	mSyncNextCount = count + mSyncDuration;
	requestToSend();
}

}	// microbit_dal_ext_kit
