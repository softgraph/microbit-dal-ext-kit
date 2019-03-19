/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Assert utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_ASSERT_H
#define EXT_KIT_ASSERT_H

#include "MicroBitDevice.h"	// microbit_panic()
#include "ExtKit_Common.h"
#include "ExtKitError.h"	// error

namespace microbit_dal_ext_kit {

#if EXT_KIT_CONFIG_ENABLED(ASSERT)

/// Assert the condition. Trigger a panic if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_OR_PANIC(expr, panic_code)	\
	do {	\
		if(!(expr)) {	\
			microbit_dal_ext_kit::error::raise("Assertation failed: (" #expr ")", __FILE__, __LINE__, panic_code);	\
		}	\
	} while (0)

/// Assert the condition. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT(expr)	\
	do {	\
		if(!(expr)) {	\
			microbit_dal_ext_kit::error::raise("Assertation failed: (" #expr ")", __FILE__, __LINE__);	\
		}	\
	} while (0)

/// Assert that the object is not placed on the stack. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_SAFE_OBJECT(object)	\
	do {	\
		if(((object) >= ((void*) (MICROBIT_HEAP_END)))	\
		&& ((object) <  ((void*) (CORTEX_M0_STACK_BASE))))	\
		{	\
			microbit_dal_ext_kit::error::raise("Assertation failed: '" #object "' may not be safe because it is placed on the stack" , __FILE__, __LINE__);	\
		}	\
	} while (0)

/// Assert that the object of the class is not placed on the stack. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_SAFE_CLASS_OBJECT(class, object)	\
	do {	\
		if(((object) >= ((void*) (MICROBIT_HEAP_END)))	\
		&& ((object) <  ((void*) (CORTEX_M0_STACK_BASE))))	\
		{	\
			microbit_dal_ext_kit::error::raise("Assertation failed: The object may not be safe because it is placed on the stack" , class, object);	\
		}	\
	} while (0)

#else	// ASSERT

/// Assert the condition. Trigger a panic if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_OR_PANIC(expr, panic_code)	\
	do {	\
		if(!(expr)) {	\
			microbit_panic(panic_code);	\
		}	\
	} while (0)

/// Assert the condition. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT(expr)	((void)0)

/// Assert that the object is not placed on the stack. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_SAFE_OBJECT(object)	((void)0)

/// Assert that the object of the class is not placed on the stack. Do nothing if EXT_KIT_CONFIG_ENABLED(ASSERT) is not true.
#define EXT_KIT_ASSERT_SAFE_CLASS_OBJECT(class, object)	((void)0)

#endif	// ASSERT

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_ASSERT_H
