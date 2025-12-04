 /**
 * @file   Spider.h
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process Spider robot with coordinated leg movements
 *
 * Contains a Spider class that provides functions to operate
 * on the six spider legs on the Terasic Spider robot
 */

#ifndef SPIDER_H_
#define SPIDER_H_

#include "MMap.h"
#include "SpiderLeg.h"

/*
*	Class Spider
*/
class Spider{
private:
	// Define an enumertion for the 6 legs
	typedef enum{
		LEG_RF,
		LEG_RM,
		LEG_RB,
		LEG_LF,
		LEG_LM,
		LEG_LB,
		LEG_NUM
	}LEG_ID;

	// Define the two tripods
	typedef enum{
		TRIPOD1,    //RF LM RB
		TRIPOD2,	//LF RM LB
		TRIPOD_NUM
	}TRIPOD_ID;
	
	typedef enum{
		FWD,
		BACK
	} DIR;

	// A SpiderLeg array of the six legs
	SpiderLeg *m_szLeg[LEG_NUM];
	MMap* m_map;		// Memory map object
	TRIPOD_ID lastStep;
	DIR lastDir;

public:
	Spider(MMap* mmio);		// Constructor
	~Spider();				// Destructor

	bool IsReady(void);
	bool WaitReady(void);
	void MoveTripod(TRIPOD_ID Tripod,SpiderLeg::JOINT_ID Joint,float AngleF,float AngleM,float AngleB);
	//Action
	bool Init(void);
	void Reset(void);
	bool Standup(void);
	void SetSpeed(int Speed);
	void MoveForward(uint8_t Repeat_Num);
	void MoveBackward(uint8_t Repeat_Num);
	void RotateRight(uint8_t Repeat_Num);
	void RotateLeft(uint8_t Repeat_Num);
	void MoveSquare();
};

#endif /* CSPIDER_H_ */
