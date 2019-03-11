/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Serial utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitSerial.h"	// self
#include "ExtKit_System.h"

namespace microbit_dal_ext_kit {
namespace serial {

//																	 123456789abcdef012345
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sendError1,	"\x15", "Serial Send Error 1: ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, sendError2,	"\x15", "Serial Send Error 2: ")

static void checkSendError(int ret);
static void dumpHexBlock(const uint8_t* buffer, size_t length);
static void dumpHexLine(const uint8_t* buffer, size_t length);
static void dumpHexByte(uint8_t byte);

void send(char c)
{
	static char s[2] = {};
	s[0] = c;
	send(s);
}

void send(int i)
{
	ManagedString s(i);
	send(s);
}

void send(const char* s)
{
	if(!s) {
		return;
	}

	size_t length = strlen(s);
	if(length <= 0) {
		return;
	}

	int ret;
	while(true) {
		ret = gSerial.send((uint8_t *) s, length);
		if(ret != MICROBIT_SERIAL_IN_USE) {
			break;
		}
		time::sleep(0 /* milliseconds */);
	}
	checkSendError(ret);
}

void send(const ManagedString& s)
{
	const char* p = s.toCharArray();
	if(!*p) {
		return;
	}

	int ret;
	while(true) {
		ret = gSerial.send(s);
		if(ret != MICROBIT_SERIAL_IN_USE) {
			break;
		}
		time::sleep(0 /* milliseconds */);
	}
	checkSendError(ret);
}

void checkSendError(int ret)
{
	if(0 < ret) {
		// nothing to do
	}
	else if(ret == MICROBIT_INVALID_PARAMETER) {
		statistics::incrementItem(&sendError1);
	}
	else {
		statistics::incrementItem(&sendError2);
	}
}

void sendLine(char c, const char* suffix)
{
	send(c);
	send(suffix);
}

void sendLine(int i, const char* suffix)
{
	send(i);
	send(suffix);
}

void sendLine(const char* s, const char* suffix)
{
	send(s);
	send(suffix);
}

void sendLine(const ManagedString& s, const char* suffix)
{
	send(s);
	send(suffix);
}

void sendMemoryDump(const void* buffer, size_t length)
{
	dumpHexBlock((const uint8_t*) buffer, length);
}

void dumpHexBlock(const uint8_t* buffer, size_t length)
{
	while(0x10 <= length) {
		dumpHexLine(buffer, 0x10);
		buffer += 0x10;
		length -= 0x10;
	}
	if(0 < length) {
		dumpHexLine(buffer, length);
	}
}

void dumpHexLine(const uint8_t* buffer, size_t length)
{
	const uint8_t* addr = (const uint8_t*) &buffer;
	for(int i = 0; i < 4; i++) {
		dumpHexByte(*addr++);
	}
	send(":");
	for(size_t i = 0; i < length; i++) {
		if((i & 0x3) == 0) {
			send(" ");
		}
		dumpHexByte(*buffer++);
	}
	send("\r\n");
}

void dumpHexByte(uint8_t byte)
{
	static char buf[4];
	uint8_t hi = byte >> 4;
	uint8_t lo = byte & 0xF;
	buf[0] = ' ';
	buf[1] = (10 <= hi) ? hi - 10 + 'a' : hi + '0';
	buf[2] = (10 <= lo) ? lo - 10 + 'a' : lo + '0';
	buf[3] = 0;
	send(buf);
}

}	// serial
}	// microbit_dal_ext_kit
