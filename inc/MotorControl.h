/*
 * MotorControl.h
 *
 *  Created on: Feb 17, 2021
 *      Author: 1000086162
 */

#ifndef INC_MOTORCONTROL_H_
#define INC_MOTORCONTROL_H_


typedef enum eMotorState
{
	MOTOR_STOP = 0,
	MOTOR_FORWARD,
	MOTOR_BACKWARD,
	MOTOR_LEFT,
	MOTOR_RIGHT,
	MOTOR_END_STATE,
}eMotorDirection;


extern UINT16 MotorControl(eMotorDirection direction, UINT16 speed);
extern void InitMotorDriverPort(void);

#endif /* INC_MOTORCONTROL_H_ */
