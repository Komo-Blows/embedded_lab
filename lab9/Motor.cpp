 /**
 * @file   Motor.cpp
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process an RC Serco motor in the Terasic Spider
 *
 * Implements the Motor class that provides functions to operate
 * on the various rc servos on the Terasic Spider robot
 */

#include "Motor.h"
#include "RegisterMap.h"
#include <math.h>
#include <iostream>
using namespace std;

/*
*	Constructor initializes the specified servo
*	with defualt values
*/
Motor::Motor(MMap* mio, int MonotrID)
{
	m_nMotorID = MonotrID;		// Motor ID (0-17) specifies rc servo to test
	motor_angle = 0.0;			// Angle [-90 to 90] degrees. 0.0 is the defualt
	motor_speed = DELAY_MAX; 	// Actual delay in cycles. Higher delay ==> slow speed
	mmio = mio;					// Memory map object for register access

	uint32_t duty_cycle = 75000;	// Neutral 0.0 degrees
	// 	Setup the PWM period, default (duty cycle=75000), default speed=1700 cycles
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_TOTAL_DUR), PWM_PERIOD);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_HIGH_DUR), duty_cycle);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ADJ_SPEED), motor_speed);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ABORT), 0);	// wake up mode
}

/**
*	Destructor
*/
Motor::~Motor() {
	// Stop sending PWM
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ABORT), 1);	// Disable PWM signal
}

/**
 * Puts the motor into the neutral, angle 0 position by
 * calling the specific function Move(...).
 */
void Motor::Reset(void){
	// TO DO: Write code to reset motor to 0.0 degrees


}

/**
 * @return true when this motor is prepared to receive
 * a new SetSpeed or Move method call; otherwise false.
*/
bool Motor::IsReady(void)
{
	// TO DO: Write code below ...



	return false; // change as needed
}

/**
 *	Check the current motor angle
 */
float Motor::GetfAngle(void)
{
	// TO DO: Write code below ...



	return 0.0; // change as needed
}

/**
 * Compute an appropriate delay value based on the given speed.
 * @param speed - a number between SPEED_MIN and SPEED_MAX,
 * Limit the speed to SPEED_MAX or SPEED_MIN if out of bounds
 * Compute motor_speed with your algorithm before writing to register
 */
void Motor::SetSpeed(int speed)
{
    // limit the speed if it is in or out of bounds
    if (speed < SPEED_MIN) {
        speed = SPEED_MIN;
    }

    if (speed > SPEED_MAX) {
        speed = SPEED_MAX;
    }

	// compute delay value using speed
	int delayValue = (speed * 7) + 1000;

	// compute the motor speed before before writing to the register
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ADJ_SPEED), delayValue);
}

/**
 *	Return the current motor speed
 */
uint32_t Motor::GetSpeed(void)
{
	// TO DO: Write code below ...



	return 0; // change as needed
}

/**
 *	Move motor to the specified angle. First...
 * @param fAngle - a number between DEGREE_MIN and DEGREE_MAX,
 *  Limit the angle to DEGREE_MAX or DEGREE_MIN if out of bounds
 *  If angle = -0.0 then set it to 0.0
 *  If controlling right side motors, set fAngle = -fAngle
 *  Compute PWM duty cycle with your algorithm before writing to register
 */
void Motor::Move(float fAngle) {
	// TO DO: Write code below ...
	// convert motor ID to a negative or positive number
	float angleConverstion_factor = 0;
	if (m_nMotorID < 9) {
	    angleConverstion_factor--;
	} else {
	    angleConverstion_factor++;
	}

	// limit the angle
	if (fAngle < DEGREE_MIN) {
	    fAngle = DEGREE_MIN;
	}

	if (fAngle > DEGREE_MAX) {
	    fAngle = DEGREE_MAX;
	}

	// compute register value
	int registerValue = 25000 + (1250* (fAngle+90));

	// set register value
	mmio->RegisterWrite((szPWM_Base[m_nMotorID]+REG_HIGH_DUR), registerValue);

	// set the attribute value
	motor_angle = fAngle;
}
