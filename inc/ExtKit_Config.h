/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Module configration using Yotta config system
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT__CONFIG_H
#define EXT_KIT__CONFIG_H

namespace microbit_dal_ext_kit {

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
		These default values are defined in <a href=_ext_kit___config_8h_source.html>ExtKit_Config.h</a>.

	# Compile Time Options with Yotta
		These values can be changed through the configuration system provided by Yotta.
		Here is an example for `config.json` file.
		@include	config.example.json
		@reference
			- <a href="http://docs.yottabuild.org/reference/config.html"><b>Configuration System Reference</b> (yottabuild.org)</a>
			- <a href="https://lancaster-university.github.io/microbit-docs/advanced/#compile-time-configuration-options"><b>Compile Time Configuration Options</b> (lancaster-university.github.io)</a>
*/

}	// microbit_dal_ext_kit

/// Ensure that the config feature for using Assert is defined. The valid value is 1 (enabled) or 0 (disabled).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT				1
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT

/// Ensure that the config value for radio group is defined. The valid value is a number available for MicroBitRadio::setGroup(uint8_t group).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP			0
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP

/// Ensure that the config feature for usig the serial external debugger is defined. The valid value is 1 (enabled) or 0 (disabled).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_EXT_DEBUG
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_EXT_DEBUG	1
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_EXT_DEBUG

/// Ensure that the config value for the buffer size for serial rx is defined. The valid value is a number available for MicroBitSerial::setRxBufferSize(uint8_t size).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF		20
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF

/// Ensure that the config value for the buffer size for serial tx is defined. The valid value is a number available for MicroBitSerial::setTxBufferSize(uint8_t size).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF		80
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF

/// Check that the config feature is enabled
#define EXT_KIT_CONFIG_ENABLED(xxx)		(YOTTA_CFG_MICROBIT_DAL__EXT_KIT_##xxx == 1)	// expects 0 or 1

/// Read the config value
#define EXT_KIT_CONFIG_VALUE(xxx)		(YOTTA_CFG_MICROBIT_DAL__EXT_KIT_##xxx)

#endif	// EXT_KIT__CONFIG_H
