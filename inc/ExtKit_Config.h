/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Module configration using Yotta
/**	@file
	@sa	Yotta config file and an example.
		- `config.json` in the project root
		- `config.example.json` in the project root
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT__CONFIG_H
#define EXT_KIT__CONFIG_H

#include "MicroBitConfig.h"	// CONFIG_ENABLED, MICROBIT_BLE_ENABLED

/// Ensure that the config feature for using Assert is defined. The valid value is 1 (enabled) or 0 (disabled).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT			1
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_ASSERT

/// Ensure that the config feature for using uBit gloval variable is defined. The valid value is 1 (enabled) or 0 (disabled). Currently, uBit gloval variable is automatically enabled if MICROBIT_BLE_ENABLED or MICROBIT_BLE_PAIRING_MODE is requested.
#if			CONFIG_ENABLED(MICROBIT_BLE_ENABLED)	\
		||	CONFIG_ENABLED(MICROBIT_BLE_PAIRING_MODE)
#undef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_GLOBAL_UBIT
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_GLOBAL_UBIT		1
#else	//	MICROBIT_BLE_ENABLED || MICROBIT_BLE_PAIRING_MODE

#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_GLOBAL_UBIT
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_GLOBAL_UBIT		0
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_GLOBAL_UBIT

#endif	//	MICROBIT_BLE_ENABLED || MICROBIT_BLE_PAIRING_MODE

/// Ensure that the config value for radio group is defined. The valid value is a number available for MicroBitRadio::setGroup(uint8_t group).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP		0
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_RADIO_GROUP

/// Ensure that the config feature for usig the serial debugger is defined. The valid value is 1 (enabled) or 0 (disabled).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_DEBUGGER
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_DEBUGGER	1
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_DEBUGGER

/// Ensure that the config value for the buffer size for serial rx is defined. The valid value is a number available for MicroBitSerial::setRxBufferSize(uint8_t size).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF	20
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_RXBUF

/// Ensure that the config value for the buffer size for serial tx is defined. The valid value is a number available for MicroBitSerial::setTxBufferSize(uint8_t size).
#ifndef		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF
#define		YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF	80
#endif	//	YOTTA_CFG_MICROBIT_DAL__EXT_KIT_SERIAL_TXBUF

/// Check that the config feature is enabled.
#define EXT_KIT_CONFIG_ENABLED(xxx)		(YOTTA_CFG_MICROBIT_DAL__EXT_KIT_##xxx == 1)	// expects 0 or 1

/// Check that the config port is valid.
#define EXT_KIT_CONFIG_PORT_VALID(xxx)	(YOTTA_CFG_MICROBIT_DAL__EXT_KIT_##xxx >= 0)	// expects -1, 0, 1, 2, ...

/// Read the config value.
#define EXT_KIT_CONFIG_VALUE(xxx)		(YOTTA_CFG_MICROBIT_DAL__EXT_KIT_##xxx)

#endif	// EXT_KIT__CONFIG_H