/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Device utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitDevice.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

MicroBitExtKit::MicroBitExtKit()
	: MicroBit()
	, mExtKit(
		"MicroBitExtKit",
		buttonA,
		buttonB,
		buttonAB,
		display,
		i2c,
		messageBus,
		io,
		resetButton,
		serial,
		&accelerometer,
		&compass,
		&radio,
		&thermometer
	)
{
}

void MicroBitExtKit::init()
{
	MicroBit::init();
	mExtKit.init();		// required before calling serial::initializeTx()
	serial::initializeTx();
}

PrimitiveExtKit::PrimitiveExtKit()
	: serial(USBTX, USBRX)
	, resetButton(MICROBIT_PIN_BUTTON_RESET)
	, i2c(I2C_SDA0, I2C_SCL0)
	, messageBus()
	, display()
	, buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A)
	, buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B)
	, buttonAB(MICROBIT_ID_BUTTON_A,MICROBIT_ID_BUTTON_B, MICROBIT_ID_BUTTON_AB)
	, io(
		MICROBIT_ID_IO_P0,
		MICROBIT_ID_IO_P1,
		MICROBIT_ID_IO_P2,
		MICROBIT_ID_IO_P3,
		MICROBIT_ID_IO_P4,
		MICROBIT_ID_IO_P5,
		MICROBIT_ID_IO_P6,
		MICROBIT_ID_IO_P7,
		MICROBIT_ID_IO_P8,
		MICROBIT_ID_IO_P9,
		MICROBIT_ID_IO_P10,
		MICROBIT_ID_IO_P11,
		MICROBIT_ID_IO_P12,
		MICROBIT_ID_IO_P13,
		MICROBIT_ID_IO_P14,
		MICROBIT_ID_IO_P15,
		MICROBIT_ID_IO_P16,
	//	MICROBIT_ID_IO_P17,
	//	MICROBIT_ID_IO_P18,
		MICROBIT_ID_IO_P19,
		MICROBIT_ID_IO_P20
	)
	, mExtKit(
		"PrimitiveExtKit",
		buttonA,
		buttonB,
		buttonAB,
		display,
		i2c,
		messageBus,
		io,
		resetButton,
		serial,
		0,	// accelerometer
		0,	// compass
		0,	// radio
		0	// thermometer
	)
	, status(0)
{
}

void PrimitiveExtKit::init()
{
	if(status & MICROBIT_INITIALIZED) {
		return;
	}

	status |= MICROBIT_INITIALIZED;

	// Bring up soft reset functionality.
	resetButton.mode(PullUp);
	resetButton.fall(microbit_reset);

	// Bring up fiber scheduler.
	scheduler_init(messageBus);

	// Create an event handler to trap any handlers being created.
	 messageBus.listen(MICROBIT_ID_MESSAGE_BUS_LISTENER, MICROBIT_EVT_ANY, this, &PrimitiveExtKit::handleMessageBusListenerAdded);

#if CONFIG_ENABLED(MICROBIT_HEAP_REUSE_SD)

	// Attempt to bring up a second heap region, using unused memory normally reserved for Soft Device.
	microbit_create_heap(MICROBIT_SRAM_BASE, MICROBIT_SD_LIMIT);

#endif	// MICROBIT_HEAP_REUSE_SD

	mExtKit.init();		// required before calling serial::initializeTx()
	serial::initializeTx();

#if CONFIG_ENABLED(MICROBIT_BLE_ENABLED) || CONFIG_ENABLED(MICROBIT_BLE_PAIRING_MODE)

	EXT_KIT_ASSERT_OR_PANIC(!"Use MicroBitExtKit insted of PrimitiveExtKit if BLE is required. Note MICROBIT_BLE_ENABLED and MICROBIT_BLE_PAIRING_MODE are enabled by default in `MicroBitConfig.h`.", panic::kNotSupported);

#endif	// MICROBIT_BLE_ENABLED || MICROBIT_BLE_PAIRING_MODE
}

void PrimitiveExtKit::handleMessageBusListenerAdded(MicroBitEvent evt)
{
	switch(evt.value)
	{
		case MICROBIT_ID_BUTTON_AB: {
			static bool done = false;
			ExtKit& g = ExtKit::global();
			if(!done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Button AB");
				g.buttonA().setEventConfiguration(MICROBIT_BUTTON_SIMPLE_EVENTS);	// suppress MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				g.buttonB().setEventConfiguration(MICROBIT_BUTTON_SIMPLE_EVENTS);	// suppress MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				g.buttonAB().setEventConfiguration(MICROBIT_BUTTON_ALL_EVENTS);		// generate MICROBIT_BUTTON_EVT_CLICK/LONG_CLICK
				done = true;
			}
			break;
		}

		case MICROBIT_ID_ACCELEROMETER:
		case MICROBIT_ID_GESTURE: {
			static bool done = false;
			ExtKit& g = ExtKit::global();
			MicroBitAccelerometer* accelerometer = g.accelerometer();
			if(accelerometer && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Accelerometer");
				accelerometer->getSample();
				done = true;
			}
			break;
		}

		case MICROBIT_ID_COMPASS: {
			static bool done = false;
			ExtKit& g = ExtKit::global();
			MicroBitCompass* compass = g.compass();
			if(compass && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Compass");
				compass->getSample();
				done = true;
			}
			break;
		}

		case MICROBIT_ID_THERMOMETER: {
			static bool done = false;
			ExtKit& g = ExtKit::global();
			MicroBitThermometer* thermometer = g.thermometer();
			if(thermometer && !done) {
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Listener added: Thermometer");
				thermometer->updateSample();
				done = true;
			}
			break;
		}
	}
}

}	// microbit_dal_ext_kit
