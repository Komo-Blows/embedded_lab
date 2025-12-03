 /**
 * @file   SpiderLeg.cpp
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process a spider leg with 3 joints: Hip, Knee, and Ankle
 *
 * Contains a SpiderLeg class that provides functions to operate
 * on the various legs on the Terasic Spider robot
 */
#include <cassert>
#include "SpiderLeg.h"

/**
 *  Constructor initializes 3 dynamic motor objects for the Leg
 */
SpiderLeg::SpiderLeg(MMap* mmio, int Joint0_MotorID,int Joint1_MotorID,int Joint2_MotorID)
{
	m_szMotor[0] = new Motor(mmio, Joint0_MotorID);
	m_szMotor[1] = new Motor(mmio, Joint1_MotorID);
	m_szMotor[2] = new Motor(mmio, Joint2_MotorID);
}

/**
 * Delete the 3 dynamic motor objects for the Leg
 */
SpiderLeg::~SpiderLeg() {
	for(int i=0;i<JOINT_NUM;i++){
		delete m_szMotor[i];
	}
}

/**
 * Reset the 3 joints on the Leg
 */
void SpiderLeg::Reset(void) {
	// Reset all three joints on the leg to 0 degrees
	for(int i = 0; i < JOINT_NUM; i++) {
		m_szMotor[i]->Reset();
	}
}

/**
 * Move the specified joint to the specified angle
 */
void SpiderLeg::MoveJoint(JOINT_ID JointID, float fAngle){
	// TO DO: Write code below ...
	m_szMotor[JointID]->Move(fAngle);
}

/**
 *  Check if all the joints on the Leg are ready
 */
bool SpiderLeg::IsReady(void){
	// TO DO: Write code below ...
	for (int i=0; i<JOINT_NUM; i++){
	    if (m_szMotor[i]->IsReady() == false) {
			return false;
		}
	}
	return true;
}

/**
 *  Get the angle for the specified joint
 */
float SpiderLeg::GetfAngle(JOINT_ID JointID)
{
	// TO DO: Write code below ...

	return m_szMotor[JointID]->GetfAngle(); // change as needed
}

/**
 *  Set the speed for the specified joint
 */
void SpiderLeg::SetSpeed(JOINT_ID JointID, int Speed)
{
	// TO DO: Write code below ...
	m_szMotor[JointID]->SetSpeed(Speed);
}

/**
 *  Return the speed for the specified joint
 */
uint32_t SpiderLeg::GetSpeed(JOINT_ID JointID)
{
	return m_szMotor[JointID]->GetSpeed();
}
