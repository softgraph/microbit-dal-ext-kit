/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Request utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_REQUEST_H
#define EXT_KIT_REQUEST_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Request Token
struct RequestToken
{
	/// Request value and response value
	int	value;
};

/// Request Completion Protocol
/* interface */ class RequestCompletionProtocol
{
public:
	/// Issue a request with a token object. The method returns MICROBIT_OK if the request is accepted. Note that `request` should be retained until `waitForCompletion()` is returned.
	virtual /* to be implemented */ int /* result */ issueRequest(RequestToken& request) = 0;

	/// Wait for the completion of any request. The method returns the requested token object when the request is completed.
	virtual /* to be implemented */ RequestToken& /* response */ waitForCompletion() = 0;
};

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_REQUEST_H
