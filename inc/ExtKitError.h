/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Error utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_ERROR_H
#define EXT_KIT_ERROR_H

#include "ErrorNo.h"	// ErrorCode, PanicCode
#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Panic Code
enum PanicCode {
	/// Out Of Memory
	kPanicOutOfMemory	= 200,

	/// Unexpected Error
	kPanicUnexpectedError,
};

///	Error utility.
namespace error {

/// Raise an error.
void raise(const char *desc, const char* file, int line);

/// Raise an error.
void raise(const char *desc, const char* name, const void* object);

}	// error
}	// microbit_dal_ext_kit

#endif	// EXT_KIT_ERROR_H
