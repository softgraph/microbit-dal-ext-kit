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

/**	@page	microbit-dal-ext-kit	Topics - microbit-dal-ext-kit
		- @subpage	ExtKit_Device
		- @subpage	ExtKit_Global
		- @subpage	ExtKit_Components
		- @subpage	ExtKit_Config
		- @subpage	ExtKit_Headers
*/

/**	@page	ExtKit_Components	Components - the service prviders of microbit-dal-ext-kit

	# Components dedicated to extensiton boards
		- `JoystickBit` provides the support for ElecFreaks' Joystick:bit
		- `MotoBit` provides the support for SparkFun's moto:bit
		- `TouchPiano` provides the support for Waveshare's Mini Piano Module.
		- `ZipHalo` provides the support for Kitronik's Zip Halo.

	# Components dedicated to hardware modules
		- `Buzzer` provides the support for a generic Buzzer module.
		- `NeoPixel` provides the support for a generic NeoPixel (WS2812B) LED strip.
		- `Sonar` provides the support for a generic Sonar module (HC-SR04).

	# Other components
		- `PeriodicObserver` provides the support for periodic listeners.
		- `remoteState::Transmitter` provides the support for sending remote states to the receiver using radio datagrams provided by `MicroBitRadioDatagram`.
		- `remoteState::Receiver` provides the support for receiving remote states from the transmitter using radio datagrams provided by `MicroBitRadioDatagram`.
		- `SerialDebugger` provides the support for the serial debugger.
*/

/**	@page	ExtKit_Config	Compile Time Configuration Options for microbit-dal-ext-kit

	# List of Compile Time Options
		<table>
			<tr>
				<td><b>Symbol</b></td>
				<td><b>Description</b></td>
				<td><b>Default Value</b></td>
			</tr>
			<tr>
				<td>YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT</td>
				<td>EXT_KIT_ASSERT and other assertion macros are enabled if the value is 1</td>
				<td>1</td>
			</tr>
			<tr>
				<td>YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP</td>
				<td>The value is used for MicroBitRadio.setGroup()</td>
				<td>0</td>
			</tr>
			<tr>
				<td>YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_EXT_DEBUG</td>
				<td>Serial Debugger is enabled if the value is 1</td>
				<td>1</td>
			</tr>
			<tr>
				<td>YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF</td>
				<td>The value is used for MicroBitSerial.setRxBufferSize()</td>
				<td>20</td>
			</tr>
			<tr>
				<td>YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF</td>
				<td>The value is used for MicroBitSerial.setTxBufferSize()</td>
				<td>80</td>
			</tr>
		</table>
		These values are defined in <a href=_ext_kit___config_8h_source.html>ExtKit_Config.h</a>.

	# Compile Time Options with Yotta
		The above values can be changed through the configuration system provided by Yotta.
		Here is an example for `config.json` file.
		@include	config.example.json
		@reference
			- <a href="http://docs.yottabuild.org/reference/config.html"><b>Configuration System Reference</b> (yottabuild.org)</a>
			- <a href="https://lancaster-university.github.io/microbit-docs/advanced/#compile-time-configuration-options"><b>Compile Time Configuration Options</b> (lancaster-university.github.io)</a>
*/

}	// microbit_dal_ext_kit
