/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Sonar component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitSonar.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**
	@class	Sonar
	@sa	Microsoft pxt-sonar main.ts (MIT license)
		- https://makecode.microbit.org/pkg/Microsoft/pxt-sonar
		- https://github.com/Microsoft/pxt-sonar
		- https://github.com/Microsoft/pxt-sonar/blob/master/main.ts
*/

static const Features kFeature = feature::kSonar;

/* Component */ bool Sonar::isConfigured()
{
	return feature::isConfigured(kFeature);
}

Sonar::Sonar(MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler)
	: Component("Sonar")
	, mTriggerOutputPort(triggerOutput)
	, mHandler(handler)
{
	ExtKit::global().messageBus().listen(echoInputEventID, MICROBIT_PIN_EVT_PULSE_HI, this, &Sonar::handleEchoInput);

	echoInput.eventOn(MICROBIT_PIN_EVENT_ON_PULSE);
}

void Sonar::trigger()
{
	mTriggerOutputPort.setPull(PullNone);
	mTriggerOutputPort.setDigitalValue(0);	wait_us(2);
	mTriggerOutputPort.setDigitalValue(1);	wait_us(10);
	mTriggerOutputPort.setDigitalValue(0);
}

void Sonar::handleEchoInput(MicroBitEvent event)
{
	uint64_t durationInMs = event.timestamp;
	mHandler.handleSonarEcho(durationInMs);
}

}	// microbit_dal_ext_kit
