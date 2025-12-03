 /**
 * @file   Spider.cpp
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process Spider robot with coordinated leg movements
 *
 * Contains a Spider class that provides functions to operate
 * on the six spider legs on the Terasic Spider robot
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "Spider.h"

// Some neutral positions for some of the joints
#define Knee_Up_Base    60   //Raised legs knee position
#define Knee_Down_Base  45 	//Lowered legs knee position (neutral once standing up)
#define HipF_Base 	   -20	//Neutral hip position for front legs
#define HipM_Base  		0	//Neutral hip position for mid legs
#define HipB_Base  		20	//Neutral hip position for back legs
#define Ankle_Base  	45	//Neutral ankle position
#define Dance_Angle 	20
#define Body_Up_Base   -45
#define Body_Down_Base  45

/*
*	Class Spider
*/
Spider::Spider(MMap* mmio)
{
	// Initialize the memory map object
	m_map = mmio;

	// An array of the Motor IDs
	int szMotorID[] = {
	 /* LEG_RF */ 0,  1,  2,
	 /* LEG_RM */ 3,  4,  5,
	 /* LEG_RB */ 6,  7,  8,
	 /* LEG_LF */ 9,  10, 11,
	 /* LEG_LM */ 12, 13, 14,
	 /* LEG_LB */ 15, 16, 17
	};

	// Initialize/create the 6 legs with their Motor IDs
	for(int i=0;i<LEG_NUM;i++){
		m_szLeg[i] = new SpiderLeg(m_map, szMotorID[i*3], szMotorID[i*3+1], szMotorID[i*3+2]);
	}
	lastStep = TRIPOD2;
	lastDir = FWD;
}

Spider::~Spider() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<LEG_NUM;i++){
		delete m_szLeg[i];
	}
}

bool Spider::Init(){

	//// Init -- The servo angle needs to be explicitly set to 0.0 to enable.
	for (int i = 0; i < LEG_NUM; i++){
		m_szLeg[i]->MoveJoint(SpiderLeg::Hip, 0.0);
		m_szLeg[i]->MoveJoint(SpiderLeg::Knee, 0.0);
		m_szLeg[i]->MoveJoint(SpiderLeg::Ankle, 0.0);
	}
	return WaitReady();	
}

bool Spider::WaitReady(){
	bool bReady = false;
	while (!bReady) 
		bReady = IsReady();
	return bReady;
}

bool Spider::IsReady(){
	bool bReady = true;

	for(int i=0;i<LEG_NUM && bReady;i++){
		if (!m_szLeg[i]->IsReady())
			bReady = false;
	}
	return bReady;
}

void Spider::Reset()
{
	float fszJoin0Angle[] = {HipF_Base, 0, HipB_Base, HipF_Base, 0, HipB_Base};

	////Reset Hip Knee ankle
	for(int i = 0; i < LEG_NUM-3; i++)
	{
		m_szLeg[i]->MoveJoint(SpiderLeg::Knee, Knee_Up_Base);
		m_szLeg[LEG_NUM-i-1]->MoveJoint(SpiderLeg::Knee, Knee_Up_Base);
		m_szLeg[i]->MoveJoint(SpiderLeg::Hip, fszJoin0Angle[i]);
		m_szLeg[LEG_NUM-i-1]->MoveJoint(SpiderLeg::Hip, fszJoin0Angle[LEG_NUM-i-1]);
		m_szLeg[i]->MoveJoint(SpiderLeg::Ankle, Ankle_Base);
		m_szLeg[LEG_NUM-i-1]->MoveJoint(SpiderLeg::Ankle, Ankle_Base);
		WaitReady();
		m_szLeg[i]->MoveJoint(SpiderLeg::Knee, Knee_Down_Base);
		m_szLeg[LEG_NUM-i-1]->MoveJoint(SpiderLeg::Knee, Knee_Down_Base);
		WaitReady();
	}
}

bool Spider::Standup(){
	bool bSuccess;
	//// Stand up  -- Adjust Hip
	float fszJoin0Angle[] = {HipF_Base, 0, HipB_Base, HipF_Base, 0, HipB_Base};
	
	for(int i = 0; i < LEG_NUM; i++)
	  m_szLeg[i]->MoveJoint(SpiderLeg::Hip, fszJoin0Angle[i]);
	bSuccess = WaitReady();

	//// Stand up  -- Adjust Knee ankle
	float KneeAngle = 90;
	const float AnkleAngle = 45.0;
	while(bSuccess && KneeAngle >= 45.0) {
		for(int i = 0; i < LEG_NUM; i++) {
			m_szLeg[i]->MoveJoint(SpiderLeg::Knee, KneeAngle);
			m_szLeg[i]->MoveJoint(SpiderLeg::Ankle,AnkleAngle);
		}// for
		bSuccess = WaitReady();
		KneeAngle -= 5.0;
	}
	if (bSuccess)
		Reset();

	return bSuccess;
}
	
void Spider::SetSpeed(int Speed)
{
	for (int i = 0; i < LEG_NUM; i++){
		m_szLeg[i]->SetSpeed(SpiderLeg::Hip, Speed);
		m_szLeg[i]->SetSpeed(SpiderLeg::Knee, Speed);
		m_szLeg[i]->SetSpeed(SpiderLeg::Ankle, Speed);
	}
}

void Spider::MoveTripod(TRIPOD_ID Tripod,SpiderLeg::JOINT_ID Joint,float AngleF,float AngleM,float AngleB)
{
	if(Tripod == 0)
	{
		m_szLeg[LEG_RF]->MoveJoint(Joint,AngleF);
		m_szLeg[LEG_LM]->MoveJoint(Joint,AngleM);
		m_szLeg[LEG_RB]->MoveJoint(Joint,AngleB);
	}
	else
	{
		m_szLeg[LEG_LF]->MoveJoint(Joint,AngleF);
		m_szLeg[LEG_RM]->MoveJoint(Joint,AngleM);
		m_szLeg[LEG_LB]->MoveJoint(Joint,AngleB);
	}
}

void Spider::MoveForward(uint8_t Repeat_Num)
{
	for(int num=0; num<Repeat_Num; num++)
	{
		if ((lastStep == TRIPOD2 && lastDir == FWD) || (lastStep == TRIPOD1 && lastDir == BACK)){ // if the last step ended in tripod 2 forward
			MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 1
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base + 20, HipM_Base + 20, HipB_Base + 20); // Move Tripod 1 forward
			MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base - 20, HipM_Base - 20, HipB_Base - 20); // Move Tripod 2 Backwards (it's on the ground)
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 1
			WaitReady();
			lastStep = TRIPOD1; // tripod 1 is forwards
		}else{ // next step (tripod 1 forwards)
			MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 2
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base - 20, HipM_Base - 20, HipB_Base - 20); //move tripod 1 backwards
			MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base + 20, HipM_Base + 20, HipB_Base + 20); // move tripod 2 forwards
			WaitReady();
			MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
			WaitReady();
			lastStep = TRIPOD2; // tripod 2 is forwards
		}
		lastDir = FWD;
	}
}

void Spider::MoveBackward(uint8_t Repeat_Num)
{
	for(int num=0; num<Repeat_Num; num++)
	{
		if ((lastStep == TRIPOD2 && lastDir == FWD) || (lastStep == TRIPOD1 && lastDir == BACK)){ // if the last step ended in tripod 2 forward
			MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 2
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base + 20, HipM_Base + 20, HipB_Base + 20); // move tripod 1 forwards
			MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base - 20, HipM_Base - 20, HipB_Base - 20); // move tripod 2 backwards
			WaitReady();
			MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
			WaitReady();
			lastStep = TRIPOD1;
		}else{ // tripod 1 is forwards
			MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 1
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base - 20, HipM_Base - 20, HipB_Base - 20); // trip 1 backwards
			MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base + 20, HipM_Base + 20, HipB_Base + 20); // trip2 forwards
			WaitReady();
			MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 1
			WaitReady();
			lastStep = TRIPOD2;
		}
		lastDir = BACK;
	}
}

void Spider::RotateLeft()
{
	// lift all legs
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
	MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
	WaitReady();
	// reset to neutral angles
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base);
	MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base);
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base + 20, HipM_Base - 20, HipB_Base - 20); // tripod 2 rotate right
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 2
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base); // tripod 2 to neutral angle
	WaitReady();
	// drop all legs
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
	MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 1
	WaitReady();
}

void Spider::RotateRight()
{
	// lift all legs
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
	MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
	WaitReady();
	// reset to neutral angles
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base);
	MoveTripod(TRIPOD1, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base);
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base - 20, HipM_Base + 20, HipB_Base + 20); // tripod 2 rotate left
	WaitReady();
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base); // lift tripod 2
	MoveTripod(TRIPOD2, SpiderLeg::Hip, HipF_Base, HipM_Base, HipB_Base); // tripod 2 to neutral angle
	WaitReady();
	// drop all legs
	MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 2
	MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base); // drop tripod 1
	WaitReady();
}