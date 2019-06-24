/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
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
namespace radio {

void prepare()
{
	static bool sPrepared = false;
	if(sPrepared) {
		return;
	}

	MicroBitRadio* r = ExtKit::global().radio();
	if(!r) {
		return;
	}

	sPrepared = true;
	r->setGroup(EXT_KIT_CONFIG_VALUE(RADIO_GROUP));
	r->enable();
}

void send(const ManagedString& command)
{
	if(command.length() <= 0) {
		return;
	}

	MicroBitRadio* r = ExtKit::global().radio();
	if(!r) {
		return;
	}

	r->datagram.send(command);
//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Radio Datagram: \'", command.toCharArray(), "\'");
}

ManagedString /*received */ recv()
{
	MicroBitRadio* r = ExtKit::global().radio();
	if(!r) {
		return ManagedString(ManagedString::EmptyString);
	}

	ManagedString received = r->datagram.recv(); // returns the data received, or an empty PacketBuffer if no data is available.
//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Radio Datagram: \'", received.toCharArray(), "\'");
	return received;
}

}	// radio
}	// microbit_dal_ext_kit
