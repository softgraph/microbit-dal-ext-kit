/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// String utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitString.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {
namespace string {

int16_t seek(const ManagedString& s, int16_t start, char prefix)	// returns MICROBIT_NO_DATA or the next position on s
{
	ManagedString t(s);
	int16_t length = t.length();
	for(int16_t i = start; i < length; i++) {
		char c = t.charAt(i) /* !const */;
		if(c == prefix) {
			return i + 1;
		}
	}
	return MICROBIT_NO_DATA;
}

int16_t beginsWith(const ManagedString& s, int16_t start, const char* prefix)	// returns MICROBIT_NO_DATA or the next position on s
{
	ManagedString t(s);
	int16_t length = t.length();
	for(int16_t i = start; i < length; i++) {
		if(*prefix == 0) {
			return i;
		}
		char c = t.charAt(i) /* !const */;
		if(c != *prefix++) {
			return MICROBIT_NO_DATA;	// does not meet the prefix
		}
	}
	return MICROBIT_NO_DATA;	// too short for the prefix
}

uint32_t numberForHexString(const ManagedString& s, int16_t start)
{
	ManagedString t(s);
	uint32_t number = 0;
	int16_t length = t.length();
	for(int16_t i = start; i < length; i++) {
		char c = t.charAt(i) /* !const */;
		if('0' <= c && c <= '9') {
			c -= '0';
		}
		else if('A' <= c && c <= 'F') {
			c -= 'A' - 10;
		}
		else if('a' <= c && c <= 'f') {
			c -= 'a' - 10;
		}
		else {
			break;
		}
		number <<= 4;
		number += c;
	}
	return number;
}

ManagedString hex(uint32_t number, char prefix)
{
	const int kMaxDigits	= 8;	// 8 hex digits
	char buf[kMaxDigits + 2] = {};	// max: prefix + digits + NUL

	if(number == 0) {
		if(prefix) {
			buf[0] = prefix;
			buf[1] = '0';
		}
		else {
			buf[0] = '0';
		}
		return ManagedString(buf);
	}

	for(char* p = &buf[kMaxDigits]; &buf[1] <= p; p--) {
		uint8_t hex = number & 0xF;
		if(hex < 10) {
			*p = hex + '0';
		}
		else {
			*p = hex + 'a' - 10;
		}
		number >>= 4;
	}

	int leadingZeros = 0;
	for(char* p = &buf[1]; *p == '0'; p++) {
		leadingZeros++;
	}
	EXT_KIT_ASSERT(leadingZeros < kMaxDigits);

	if(prefix) {
		buf[leadingZeros] = prefix;
		return ManagedString(&buf[leadingZeros]);
	}
	else {
		return ManagedString(&buf[leadingZeros + 1]);
	}
}

}	// string
}	// microbit_dal_ext_kit
