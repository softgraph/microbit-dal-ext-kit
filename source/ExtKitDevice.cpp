/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Device utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitDevice.h"	// self
#include "ExtKit_System.h"

namespace microbit_dal_ext_kit {
namespace device {

static void prepareSerial();

#if EXT_KIT_CONFIG_ENABLED(GLOBAL_UBIT)

void initialize()
{
	uBit.init();

	// Prepare Serial
	prepareSerial();
}

#else	// GLOBAL_UBIT

static void handleMessageBusListenerAdded(MicroBitEvent evt);

void initialize()
{
	static uint8_t sStatus = 0;

	if(sStatus & MICROBIT_INITIALIZED) {
		return;
	}

	// Bring up fiber scheduler.
	scheduler_init(gMessageBus);

	// Prepare Serial
	prepareSerial();

	// Create an event handler to trap any handlers being created.
	 gMessageBus.listen(MICROBIT_ID_MESSAGE_BUS_LISTENER, MICROBIT_EVT_ANY, handleMessageBusListenerAdded);

	sStatus |= MICROBIT_INITIALIZED;

#if CONFIG_ENABLED(MICROBIT_HEAP_REUSE_SD)
#if CONFIG_ENABLED(MICROBIT_BLE_ENABLED) || CONFIG_ENABLED(MICROBIT_BLE_PAIRING_MODE)

#error	GLOBAL_UBIT should not be disabled if MICROBIT_BLE_ENABLED or MICROBIT_BLE_PAIRING_MODE is enabled

#else	// MICROBIT_BLE_ENABLED || MICROBIT_BLE_PAIRING_MODE

	// Attempt to bring up a second heap region, using unused memory normally reserved for Soft Device.
	microbit_create_heap(MICROBIT_SRAM_BASE, MICROBIT_SD_LIMIT);

#endif	// MICROBIT_BLE_ENABLED || MICROBIT_BLE_PAIRING_MODE
#endif	// MICROBIT_HEAP_REUSE_SD
}

void prepareFor(MicroBitMultiButton* buttonAB)
{
	gButtonAB = buttonAB;
}

void prepareFor(MicroBitAccelerometer* accelerometer)
{
	gAccelerometer = accelerometer;
}

void prepareFor(MicroBitCompass *compass)
{
	gCompass = compass;
}

void prepareFor(MicroBitThermometer* thermometer)
{
	gThermometer = thermometer;
}

void handleMessageBusListenerAdded(MicroBitEvent evt)
{
	switch(evt.value)
	{
		case MICROBIT_ID_BUTTON_AB: {
			static bool done = false;
			if(gButtonAB && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Button AB");
				gButtonA.setEventConfiguration(MICROBIT_BUTTON_SIMPLE_EVENTS);	// suppress MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				gButtonB.setEventConfiguration(MICROBIT_BUTTON_SIMPLE_EVENTS);	// suppress MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				gButtonAB->setEventConfiguration(MICROBIT_BUTTON_ALL_EVENTS);	// generate MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				done = true;
			}
			break;
		}

		case MICROBIT_ID_ACCELEROMETER:
		case MICROBIT_ID_GESTURE: {
			static bool done = false;
			if(gAccelerometer && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Accelerometer");
				gAccelerometer->getSample();
				done = true;
			}
			break;
		}

		case MICROBIT_ID_COMPASS: {
			static bool done = false;
			if(gCompass && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Compass");
				gCompass->getSample();
				done = true;
			}
			break;
		}

		case MICROBIT_ID_THERMOMETER: {
			static bool done = false;
			if(gThermometer && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Thermometer");
				gThermometer->updateSample();
				done = true;
			}
			break;
		}
	}
}

#endif	// GLOBAL_UBIT

void prepareSerial()
{
	gSerial.setRxBufferSize(EXT_KIT_CONFIG_VALUE(SERIAL_RXBUF));
	gSerial.setTxBufferSize(EXT_KIT_CONFIG_VALUE(SERIAL_TXBUF));
}

static bool sIsUpsideDown = false;

void setUpsideDown()
{
	sIsUpsideDown = true;
	gDisplay.rotateTo(MICROBIT_DISPLAY_ROTATION_180);
}

bool isUpsideDown()
{
	return sIsUpsideDown;
}

}	// device
}	// microbit_dal_ext_kit
