/*
 * CMotorControl.hpp
 *
 *  Created on: Feb 27, 2021
 *      Author: 1000086162
 */

#ifndef CMOTORCONTROL_HPP_
#define CMOTORCONTROL_HPP_

typedef enum eMotorState
{
	MOTOR_STOP = 0,
	MOTOR_FORWARD,
	MOTOR_BACKWARD,
	MOTOR_LEFT,
	MOTOR_RIGHT,
	MOTOR_END_STATE,
}eMotorDirection;

class CMotorControl
{
public:
	CMotorControl(){}
	~CMotorControl(){}
	void InitMotorDriverPort(void);
	UINT16 RunMotorControl(eMotorDirection direction, UINT16 speed);
};


#endif /* CMOTORCONTROL_HPP_ */
