/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Radio utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitRadio.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**
	@class	Radio
*/

static const Features kFeature = feature::kRadio;

/* Component */ bool Radio::isConfigured()
{
	return feature::isConfigured(kFeature);
}

Radio::Radio()
	: Component("Radio")
{
	MicroBitRadio* r = ExtKit::global().radio();
	EXT_KIT_ASSERT(r);
}

/* Component */ void Radio::start()
{
	MicroBitRadio* r = ExtKit::global().radio();
	if(r) {
		r->setGroup(EXT_KIT_CONFIG_VALUE(RADIO_GROUP));
		r->enable();
	}
}

void sendToRadio(const ManagedString& radioCmd)
{
	if(radioCmd.length() <= 0) {
		return;
	}

	MicroBitRadio* r = ExtKit::global().radio();
	if(r) {
		r->datagram.send(radioCmd);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Radio Datagram: \'", radioCmd.toCharArray(), "\'");
	}
}

ManagedString /*received */ recvFromRadio()
{
	MicroBitRadio* r = ExtKit::global().radio();
	if(r) {
		ManagedString received = r->datagram.recv(); // return the data received, or an empty PacketBuffer if no data is available.
		//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Radio Datagram: \'", received.toCharArray(), "\'");
		return received;
	}
	else {
		return ManagedString(ManagedString::EmptyString);
	}
}

}	// microbit_dal_ext_kit
