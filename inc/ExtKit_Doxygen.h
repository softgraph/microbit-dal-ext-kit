/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Doxygen Topics
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

namespace microbit_dal_ext_kit {

/**	@page	microbit-dal-ext-kit	microbit-dal-ext-kit
		- @subpage	ExtKit_Device
		- @subpage	ExtKit_Global
		- @subpage	ExtKit_Components
		- @subpage	ExtKit_Headers
*/

/**	@page	ExtKit_Components	Components - the service prviders of microbit-dal-ext-kit

	@section	ExtKit_Components_1	Components dedicated to extensiton boards
		- `JoystickBit` provides the support for ElecFreaks' Joystick:bit
		- `MotoBit` provides the support for SparkFun's moto:bit
		- `TouchPiano` provides the support for Waveshare's Mini Piano Module.
		- `ZipHalo` provides the support for Kitronik's Zip Halo.
		.

	@section	ExtKit_Components_2	Components dedicated to hardware modules
		- `Buzzer` provides the support for a generic Buzzer module.
		- `NeoPixel` provides the support for a generic NeoPixel (WS2812B) LED strip.
		- `Sonar` provides the support for a generic Sonar module (HC-SR04).
		.

	@section	ExtKit_Components_3	Other components
		- `PeriodicObserver` provides the support for periodic listeners.
		- `remoteState::Transmitter` provides the support for sending remote states to the receiver using radio datagrams provided by `MicroBitRadioDatagram`.
		- `remoteState::Receiver` provides the support for receiving remote states from the transmitter using radio datagrams provided by `MicroBitRadioDatagram`.
		- `SerialDebugger` provides the support for the serial debugger.
		.
*/

}	// microbit_dal_ext_kit
