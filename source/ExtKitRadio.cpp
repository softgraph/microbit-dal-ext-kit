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
#include "ExtKit_System.h"

namespace microbit_dal_ext_kit {

void sendToRadio(const ManagedString& radioCmd)
{
	if(radioCmd.length() <= 0) {
		return;
	}

	MicroBitRadioDatagram& rd = gRadio.datagram;
	rd.send(radioCmd);
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Radio Datagram: \'", radioCmd.toCharArray(), "\'");
}

ManagedString /*received */ recvFromRadio()
{
	MicroBitRadioDatagram& rd = gRadio.datagram;
	ManagedString received = rd.recv(); // return the data received, or an empty PacketBuffer if no data is available.
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Radio Datagram: \'", received.toCharArray(), "\'");
	return received;
}

}	// microbit_dal_ext_kit
