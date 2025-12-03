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
#include <math.h>
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
	Move(0.0);
}

/**
 * @return true when this motor is prepared to receive
 * a new SetSpeed or Move method call; otherwise false.
*/
bool Motor::IsReady(void)
{
	// read ready section of register
	uint32_t status = mmio ->RegisterRead(szPWM_Base[m_nMotorID] + REG_ADJ_STATUS);

	// return ready bit
	return (status & 0x1) != 0;
}

/**
 *	Check the current motor angle
 */
float Motor::GetfAngle(void)
{
	// TO DO: Write code below ...
    return motor_angle;
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
	// Speed 0 -> delay 1700 (slowest), Speed 100 -> delay 1000 (fastest)
	int delayValue = DELAY_MAX - ((speed * (DELAY_MAX - DELAY_MIN)) / SPEED_MAX);

	// write delay value to register
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ADJ_SPEED), delayValue);

	// update class attribute
	motor_speed = delayValue;
}

/**
 *	Return the current motor speed
 */
uint32_t Motor::GetSpeed(void)
{
	// Convert current motor_speed (delay) back to user speed (0-100)
	// Reverse the SetSpeed calculation: speed = (DELAY_MAX - motor_speed) * SPEED_MAX / (DELAY_MAX - DELAY_MIN)
	uint32_t speed = ((DELAY_MAX - motor_speed) * SPEED_MAX) / (DELAY_MAX - DELAY_MIN);
	return speed;
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
	// Handle the special case where angle = -0.0
	if (fAngle == -0.0) {
		fAngle = 0.0;
	}
	
	// For right-side motors (ID 0-8), invert the angle
	if (m_nMotorID < 9) {
		fAngle = -fAngle;
	}

	// Limit the angle to valid range
	if (fAngle < DEGREE_MIN) {
		fAngle = DEGREE_MIN;
	}
	if (fAngle > DEGREE_MAX) {
		fAngle = DEGREE_MAX;
	}

	// Update the class attribute with the original angle (before inversion)
	motor_angle = (m_nMotorID < 9) ? -fAngle : fAngle;

	// Convert angle (-90 to +90) to PWM duty cycle (25000 to 125000 cycles)
	// Formula: duty_cycle = PWM_MIN + ((angle + 90) / 180) * (PWM_MAX - PWM_MIN)
	uint32_t duty_cycle = PWM_MIN + (uint32_t)(((fAngle + 90.0) / 180.0) * (PWM_MAX - PWM_MIN));

	// Write duty cycle to register
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_HIGH_DUR), duty_cycle);
}
