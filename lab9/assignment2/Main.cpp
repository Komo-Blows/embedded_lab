/**
 * @file   Main.cpp
 * @brief  Tests the Spider robot rc servo movements
 */

#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include "MMap.h"
#include "Motor.h"
#include "LEDControl.h"
#include "SpiderLeg.h"

using namespace std;

int main(int argc, char *argv[]){

	cout << "\nProgram Starting...!" << endl;
	// Create necessary class objects
	MMap *m_map = new MMap();
	LEDControl *pio = new LEDControl(m_map);
	
	// Create SpiderLeg object for Right Front leg
    SpiderLeg *rf_leg = new SpiderLeg(m_map, RF_hip, RF_knee, RF_ankle);

    cout << "Starting spider leg walking sequence..." << endl;
    
    // Initialize leg to neutral position
    rf_leg->Reset();
    sleep(1);
    
    // Walking sequence loop
    while (true) {
        cout << "Step 1: Raising knee..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Knee, 45.0);
        sleep(1);
        
        cout << "Step 2: Raising ankle..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Ankle, 30.0);
        sleep(1);
        
        cout << "Step 3: Moving hip forward..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Hip, 30.0);
        sleep(1);
        
        cout << "Step 4: Lowering knee..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Knee, 0.0);
        sleep(1);
        
        cout << "Step 5: Lowering ankle..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Ankle, 0.0);
        sleep(1);
        
        cout << "Step 6: Rotating hip back..." << endl;
        rf_leg->MoveJoint(SpiderLeg::Hip, 0.0);
        sleep(1);
        
        cout << "Walking cycle complete. Starting next cycle..." << endl;
    }

	// delete dynamic objects
	delete rf_leg;
	delete pio;
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}
