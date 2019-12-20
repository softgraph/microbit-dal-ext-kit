/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Remote State components
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitRemoteState.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace remoteState {

/**	@class	Transmitter
*/

Transmitter* Transmitter::sGlobal = 0;

Transmitter& Transmitter::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

Transmitter::Transmitter()
	: Component("Transmitter")
{
	MicroBitRadio* r = ExtKit::global().radio();
	EXT_KIT_ASSERT(r);

	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

Transmitter::~Transmitter()
{
	if(sGlobal == this) {
		sGlobal = 0;
	}
}

/* Component */ void Transmitter::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		radio::prepare();

		// Listen to radio datagrams from the receiver
		MicroBitMessageBus& mb = ExtKit::global().messageBus();
		mb.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &Transmitter::handleRadioDatagramReceived);
	}
	else if(action == kStop) {
		// Ignore radio datagrams from the receiver
		MicroBitMessageBus& mb = ExtKit::global().messageBus();
		mb.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &Transmitter::handleRadioDatagramReceived);
	}

	Component::doHandleComponentAction(action);
}

void Transmitter::listen(char category, CategoryProtocol& protocol)
{
	Node* p = new CategoryRecord(category, protocol);
	EXT_KIT_ASSERT_OR_PANIC(p, panic::kOutOfMemory);

	p->linkBefore(mRoot);
}

void Transmitter::ignore(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		if(r->category == category) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

void Transmitter::requestToSend(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		if(r->category == category) {
			r->requestToSend(/* asResponse*/ false);
			break;
		}
	}
}

void Transmitter::handleRadioDatagramReceived(MicroBitEvent /* event */)
{
	ManagedString received = radio::recv();
	if(received.length() <= 1) {
		return;
	}

	char category = received.charAt(0);
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		if(r->category == category) {
			r->handleRadioCommandReceived(received);
			break;
		}
	}
}

/**	@class	Transmitter::CategoryBase
*/

Transmitter::CategoryBase::CategoryBase(char category)
	: mTransmitter(remoteState::Transmitter::global())
	, mCategory(category)
{
	mTransmitter.listen(mCategory, *this);
}

/**	@class	Transmitter::CategoryRecord
*/

Transmitter::CategoryRecord::CategoryRecord(char category, Transmitter::CategoryProtocol& protocol)
	: protocol(protocol)
	, category(category)
	, mSequence(0)
{
}

void Transmitter::CategoryRecord::requestToSend(bool asResponse)
{
	ManagedString s = protocol.remoteState();
	send(s, asResponse);
}

void Transmitter::CategoryRecord::send(const ManagedString& remoteState, bool asResponse)
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

void Transmitter::CategoryRecord::handleRadioCommandReceived(ManagedString& received)
{
	char marker = received.charAt(1);
	if(marker != kMarkerRequest) {
		return;
	}

	requestToSend(/* asResponse*/ true);
}

/**	@class	Receiver
*/

Receiver* Receiver::sGlobal = 0;

Receiver& Receiver::global()
{
	EXT_KIT_ASSERT(sGlobal);

	return *sGlobal;
}

Receiver::Receiver()
	: Component("Receiver")
{
	MicroBitRadio* r = ExtKit::global().radio();
	EXT_KIT_ASSERT(r);

	EXT_KIT_ASSERT(!sGlobal);

	sGlobal = this;
}

Receiver::~Receiver()
{
	if(sGlobal == this) {
		sGlobal = 0;
	}
}

/* Component */ void Receiver::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		radio::prepare();

		// Listen to radio datagrams from the transmitter
		MicroBitMessageBus& mb = ExtKit::global().messageBus();
		mb.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &Receiver::handleRadioDatagramReceived);

		// Listen Periodic Observer
		PeriodicObserver::listen(PeriodicObserver::kUnit100ms, *this, PeriodicObserver::kPriorityLow);
	}
	else if(action == kStop) {
		// Ignore Periodic Observer
		PeriodicObserver::ignore(PeriodicObserver::kUnit100ms, *this);

		// Ignore radio datagrams from the transmitter
		MicroBitMessageBus& mb = ExtKit::global().messageBus();
		mb.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &Receiver::handleRadioDatagramReceived);
	}

	Component::doHandleComponentAction(action);
}

void Receiver::listen(char category, CategoryProtocol& protocol)
{
	Node* p = new CategoryRecord(category, protocol);
	EXT_KIT_ASSERT_OR_PANIC(p, panic::kOutOfMemory);

	p->linkBefore(mRoot);
}

void Receiver::ignore(char category)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		if(r->category == category) {
			p = r->prev;	// rewind p
			r->unlink();	// unlink and delete r
			delete r;
		}
	}
}

void Receiver::handleRadioDatagramReceived(MicroBitEvent /* event */)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "Receiver::handleRadioDatagramReceived");

	ManagedString received = radio::recv();
	if(received.length() <= 1) {
		return;
	}

	char category = received.charAt(0);
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		if(r->category == category) {
			r->handleRadioCommandReceived(received);
			break;
		}
	}
}

/* PeriodicObserver::HandlerProtocol */ void Receiver::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit)
{
	Node* p = &mRoot;
	while((p = p->next) != &mRoot) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		CategoryRecord* r = static_cast<CategoryRecord*>(p);
		r->handlePeriodicEvent(count, unit);
	}
}

/**	@class	Receiver::CategoryBase
*/

Receiver::CategoryBase::CategoryBase(char category)
	: mReceiver(remoteState::Receiver::global())
	, mCategory(category)
{
	mReceiver.listen(mCategory, *this);
}

/**	@class	Receiver::CategoryRecord
*/

//																						 123456789abcdef0
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sStatisticsSyncDuration,	"\x10", " SyncDuration:  ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sStatisticsRecoveryCount,	"\x10", " RecoveryCount: ")

/// Initial Sync Duration in 100 milliseconds
static const uint16_t kSyncDurationInitial	= 4;

Receiver::CategoryRecord::CategoryRecord(char category, Receiver::CategoryProtocol& protocol)
	: protocol(protocol)
	, category(category)
	, mSequence(0)
	, mSyncDuration(0)
	, mSyncNextCount(0)
	, mStatisticsSyncDuration(ManagedString(category) + ManagedString(sStatisticsSyncDuration))
	, mStatisticsRecoveryCount(ManagedString(category) + ManagedString(sStatisticsSyncDuration))
{
}

void Receiver::CategoryRecord::requestToSend()
{
	char buf[3] = { category, kMarkerRequest, 0 };
	ManagedString s(buf);
	radio::send(s);
}

void Receiver::CategoryRecord::handleRadioCommandReceived(ManagedString& received)
{
//	debug_sendLine(EXT_KIT_DEBUG_TRACE "Receiver::Record::handleRadioCommandReceived");

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

void Receiver::CategoryRecord::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit /* unit */)
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

}	// remoteState
}	// microbit_dal_ext_kit
