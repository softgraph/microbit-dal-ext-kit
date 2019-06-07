/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
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

/**	@class	Sonar
	@reference	Microsoft pxt-sonar main.ts (MIT license)
		- https://makecode.microbit.org/pkg/Microsoft/pxt-sonar
		- https://github.com/Microsoft/pxt-sonar
		- https://github.com/Microsoft/pxt-sonar/blob/master/main.ts
	@reference	HC-SR04 Ultrasonic Sensor Module
		- http://www.handsontec.com/pdf_files/hc-sr04-User-Guide.pdf
*/

Sonar::Sonar(const char* name, MicroBitPin& triggerOutput, MicroBitPin& echoInput, uint16_t echoInputEventID, HandlerProtocol& handler, EchoInputStabilizer echoInputStabilizer)
	: Component(name)
	, mTriggerOutput(triggerOutput)
	, mEchoInput(echoInput)
	, mHandler(handler)
	, mPreviousSonarDuration(0)
	, mEchoInputStabilizer(echoInputStabilizer)
{
	ExtKit::global().messageBus().listen(echoInputEventID, MICROBIT_PIN_EVT_PULSE_HI, this, &Sonar::handleEchoInput);
}

void Sonar::trigger()
{
	// Note that the echo input port and the trigger output port might be identical.

	// Configures the trigger output port as a digital output and output a trigger.
	mTriggerOutput.setPull(PullNone);	// may not be required
	mTriggerOutput.setDigitalValue(0);	wait_us(2);
	mTriggerOutput.setDigitalValue(1);	wait_us(10);	// 10 us is required
	mTriggerOutput.setDigitalValue(0);

	// Configures the echo input port as a digital input and generates events where the timestamp is the duration that this pin was HI (MICROBIT_PIN_EVT_PULSE_HI).
	// Note the smallest pulse that was reliably detected was 85us, around 5khz.
	// See also
	//	- https://lancaster-university.github.io/microbit-docs/ubit/io/#eventon
	mEchoInput.eventOn(MICROBIT_PIN_EVENT_ON_PULSE);
}

void Sonar::handleEchoInput(MicroBitEvent event)
{
	const uint32_t kMaxDuration = 36 * 1000;	// 36 ms

	// Apply the upper limit.
	uint32_t duration;	// duration in microseconds
	if(kMaxDuration < event.timestamp) {
		duration = kMaxDuration;
	}
	else {
		duration = (uint32_t) event.timestamp;
	}

	// Stabilize Sonar Duration.
	if((mPreviousSonarDuration != 0) && (0 < mEchoInputStabilizer) && (mEchoInputStabilizer < 8)) {
		duration *= 8 - mEchoInputStabilizer;
		duration += mPreviousSonarDuration * mEchoInputStabilizer;
		duration /= 8;
	}
	mPreviousSonarDuration = duration;

	// Handle Sonar Echo
	mHandler.handleSonarEcho(duration);
}

}	// microbit_dal_ext_kit
