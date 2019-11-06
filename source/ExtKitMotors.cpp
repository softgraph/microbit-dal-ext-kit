/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// MotorsLR component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitMotors.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@class	Motors
*/

Motors::Motors(const char* name, int motorCount)
	: Component(name)
	, mMotorCount(motorCount)
	, mMotorPower(false)
{
	mMotorDevices = new MotorDevice*[mMotorCount];
	for(int i = 0; i < mMotorCount; i++) {
		mMotorDevices[i] = new MotorDevice();
	}
}

/* Component */ void Motors::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		resetAllMotors();
		updateMotorPower(true);
	}
	else if(action == kStop) {
		updateMotorPower(false);
		resetAllMotors();
	}
	/* super */ Component::doHandleComponentAction(action);
}

void Motors::configureSpeedMotor(Motor motor, int scaleInPercent)
{
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::configureSpeedMotor");
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(scaleInPercent >= 0);
	EXT_KIT_ASSERT(scaleInPercent <= 100);
	MotorDevice& md = *mMotorDevices[motor];
	md.clear(MotorDevice::kSpeedMotor);
	md.u.speed.scale = scaleInPercent;
	if(mMotorPower) {
		resetMotor(motor, md);
	}
}

void Motors::configureAngleMotor(Motor motor, int minAngleInDegree, int maxAngleInDegree, int centerAngleInDegree)
{
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::configureAngleMotor");
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(minAngleInDegree >= 0);
	EXT_KIT_ASSERT(minAngleInDegree <= 180);
	EXT_KIT_ASSERT(maxAngleInDegree >= 0);
	EXT_KIT_ASSERT(maxAngleInDegree <= 180);
	EXT_KIT_ASSERT(centerAngleInDegree >= 0);
	EXT_KIT_ASSERT(centerAngleInDegree <= 180);
	EXT_KIT_ASSERT(minAngleInDegree <= centerAngleInDegree);
	EXT_KIT_ASSERT(centerAngleInDegree <= maxAngleInDegree);
	MotorDevice& md = *mMotorDevices[motor];
	md.clear(MotorDevice::kAngleMotor);
	md.u.angle.min = minAngleInDegree;
	md.u.angle.max = maxAngleInDegree;
	md.u.angle.center = numeric::clamp(minAngleInDegree, maxAngleInDegree, centerAngleInDegree);
	md.u.angle.current = md.u.angle.center;
	if(mMotorPower) {
		resetMotor(motor, md);
	}
}

int /* ErrorCode */ Motors::updateMotorPower(bool power)
{
	if(mMotorPower == power) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorPower: MICROBIT_OK");
		return MICROBIT_OK;
	}
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorPower: setMotorPower()");
	mMotorPower = power;
	return setMotorPower(power);
}

int /* ErrorCode */ Motors::updateMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent /* 0 ... 100 */)
{
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(speedInPercent >= 0);
	EXT_KIT_ASSERT(speedInPercent <= 100);
	MotorDevice& md = *mMotorDevices[motor];
	if(md.type != MotorDevice::kSpeedMotor) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorSpeed: MICROBIT_INVALID_PARAMETER");
		return MICROBIT_INVALID_PARAMETER;
	}
	md.u.speed.direction = direction;
	md.u.speed.current = speedInPercent;
	if(!mMotorPower) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorSpeed: MICROBIT_OK");
		return MICROBIT_OK;
	}
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorSpeed: setMotorSpeed()");
	int speed = md.u.speed.current * md.u.speed.scale / 100;
	return setMotorSpeed(motor, direction, speed);
}

int /* ErrorCode */ Motors::incrementMotorSpeed(Motor motor, MotorDirection direction, int relativeSpeedInPercent /* -100 ... 100 */)
{
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(relativeSpeedInPercent >= -100);
	EXT_KIT_ASSERT(relativeSpeedInPercent <= 100);
	MotorDevice& md = *mMotorDevices[motor];
	if(md.type != MotorDevice::kSpeedMotor) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorSpeed: MICROBIT_INVALID_PARAMETER");
		return MICROBIT_INVALID_PARAMETER;
	}
	md.u.speed.direction = direction;
	md.u.speed.current = numeric::clamp(0, 100, md.u.speed.current + relativeSpeedInPercent);
	if(!mMotorPower) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorSpeed: MICROBIT_OK");
		return MICROBIT_OK;
	}
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorSpeed: setMotorSpeed()");
	int speed = md.u.speed.current * md.u.speed.scale / 100;
	return setMotorSpeed(motor, direction, speed);
}

int /* ErrorCode */ Motors::updateMotorAngle(Motor motor, int angleInDegree /* 0 ... 180 */)
{
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(angleInDegree >= 0);
	EXT_KIT_ASSERT(angleInDegree <= 180);
	MotorDevice& md = *mMotorDevices[motor];
	if(md.type != MotorDevice::kAngleMotor) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorAngle: MICROBIT_INVALID_PARAMETER");
		return MICROBIT_INVALID_PARAMETER;
	}
	md.u.angle.current = numeric::clamp(md.u.angle.min, md.u.angle.max, angleInDegree);
	if(!mMotorPower) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorAngle: MICROBIT_OK");
		return MICROBIT_OK;
	}
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::updateMotorAngle: setMotorAngle()");
	return setMotorAngle(motor, md.u.angle.current);
}

int /* ErrorCode */ Motors::incrementMotorAngle(Motor motor, int relativeAngleInDegree /* -180 ... 180 */)
{
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	EXT_KIT_ASSERT(relativeAngleInDegree >= -180);
	EXT_KIT_ASSERT(relativeAngleInDegree <= 180);
	MotorDevice& md = *mMotorDevices[motor];
	if(md.type != MotorDevice::kAngleMotor) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorAngle: MICROBIT_INVALID_PARAMETER");
		return MICROBIT_INVALID_PARAMETER;
	}
	md.u.angle.current = numeric::clamp(md.u.angle.min, md.u.angle.max, md.u.angle.current + relativeAngleInDegree);
	if(!mMotorPower) {
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorAngle: MICROBIT_OK");
		return MICROBIT_OK;
	}
	//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Motors::incrementMotorAngle: setMotorAngle()");
	return setMotorAngle(motor, md.u.angle.current);
}

void Motors::resetAllMotors()
{
	for(int i = 0; i < mMotorCount; i++) {
		MotorDevice& md = *mMotorDevices[i];
		resetMotor(i, md);
	}
}

void Motors::resetMotor(Motor motor, MotorDevice& motorDevice)
{
	EXT_KIT_ASSERT(motor >= 0);
	EXT_KIT_ASSERT(motor < mMotorCount);
	switch(motorDevice.type) {
		default:
		case MotorDevice::kSpeedMotor: {
			updateMotorSpeed(motor, kBrake, 0);
			break;
		}
		case MotorDevice::kAngleMotor: {
			updateMotorAngle(motor, motorDevice.u.angle.center);
			break;
		}
	}
}

/* Motors */ int /* ErrorCode */ Motors::setMotorPower(bool /* power */)
{
	// to be overridden
	return MICROBIT_OK;
}

/* Motors */ int /* ErrorCode */ Motors::setMotorSpeed(Motor /* motor */, MotorDirection /* direction */, int /* speedInPercent */)
{
	// to be overridden
	return MICROBIT_NOT_SUPPORTED;
}

/* Motors */ int /* ErrorCode */ Motors::setMotorAngle(Motor /* motor */, int /* angleInDegree */)
{
	// to be overridden
	return MICROBIT_NOT_SUPPORTED;
}

}	// microbit_dal_ext_kit
