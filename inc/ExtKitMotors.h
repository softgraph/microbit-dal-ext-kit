/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Motors component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_MOTORS_H
#define EXT_KIT_MOTORS_H

#include "ExtKitComponent.h"

namespace microbit_dal_ext_kit {

/// An abstract ext-kit Component which provides any number of motors. A motor can set either speed or angle.
/**	For example: <br>
	- two speed motors for left and right <br>
	- three angle motors for yaw, pitch and roll
*/
/* abstract */ class Motors : public Component
{
public:
	/// motor index
	typedef int Motor;

	/// motor direction for speed motor
	enum MotorDirection {
		kBrake,		// braked
		kForward,	// driven forward
		kBackward	// driven backward
	};

	/// update motor power
	int /* ErrorCode */ updateMotorPower(bool power);

	/// update motor speed
	int /* ErrorCode */ updateMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent);

	/// update motor angle
	int /* ErrorCode */ updateMotorAngle(Motor motor, int angleInDegree);

protected:
	/// motor device
	struct MotorDevice {
		/// motor type
		enum MotorType {
			kSpeedMotor,	/// speed motor (default)
			kAngleMotor		/// angle motor
		};

		/// motor type
		MotorType type;

		/// union
		union {
			/// speed motor parameters
			struct {
				int scale;		/// speed scale in percent (range: 0 - 100, default: 100)
				int current;	/// current speed in percent (range: 0 - 100, default: 0)
				MotorDirection direction;	// motor direction (default: kBrake)
			} speed;

			/// angle motor parameters
			struct {
				int min;		/// min angle in degree (range: 0 - 180, default: 0)
				int max;		/// max angle in degree (range: 0 - 180, default: 180)
				int center;		/// center angle in degree (range: 0 - 180, default: 90)
				int current;	/// current angle in degree (range: 0 - 180, default: 90)
			} angle;
		} u;

		/// constructor
		MotorDevice()
		{
			clear(kSpeedMotor);
		}

		/// clear
		void clear(MotorType type)
		{
			switch(type) {
				default:
				case kSpeedMotor: {
					this->type = kSpeedMotor;
					u.speed.scale = 100;
					u.speed.current = 0;
					u.speed.direction = kBrake;
					break;
				}
				case kAngleMotor: {
					this->type = kAngleMotor;
					u.angle.min = 0;
					u.angle.max = 180;
					u.angle.center = 90;
					u.angle.current = 90;
					break;
				}
			}
		}
	};

	/// constructor
	Motors(const char* name, int motorCount);

	/// inherited
	/* Component */ void doHandleComponentAction(Action action);

	/// configure motors
	/** should be overridden */
	virtual /* Motors */ void configureMotors();

	/// configure speed motor
	void configureSpeedMotor(Motor motor, int scaleInPercent = 100);

	/// configure angle motor
	void configureAngleMotor(Motor motor, int minAngleInDegree = 0, int maxAngleInDegree = 180, int centerAngleInDegree = 90);

	/// reset all motors
	void resetAllMotors();

	/// reset motor
	void resetMotor(Motor motor, MotorDevice& motorDevice);

	/// set motor power
	virtual /* Motors */ int /* ErrorCode */ setMotorPower(bool power);

	/// set motor speed
	/** should be overridden if the class supports any speed motor */
	virtual /* Motors */ int /* ErrorCode */ setMotorSpeed(Motor motor, MotorDirection direction, int speedInPercent);

	/// set motor angle
	/** should be overridden if the class supports any angle motor */
	virtual /* Motors */ int /* ErrorCode */ setMotorAngle(Motor motor, int angleInDegree);

protected:
	/// motor count
	int mMotorCount;

	/// motor power
	bool mMotorPower;

	/// motor devices
	MotorDevice** mMotorDevices;
};	// Motors

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_MOTORS_H
