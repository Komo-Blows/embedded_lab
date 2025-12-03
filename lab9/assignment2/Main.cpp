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

using namespace std;

int main(int argc, char *argv[]){

	cout << "\nProgram Starting...!" << endl;
	// Create necessary class objects
	MMap *m_map = new MMap();
	LEDControl *pio = new LEDControl(m_map);
	
	// Create three Motor objects for Right Front leg
    Motor *rf_hip = new Motor(m_map, RF_hip);
    Motor *rf_knee = new Motor(m_map, RF_knee);
    Motor *rf_ankle = new Motor(m_map, RF_ankle);

	// TO DO: Write code to test your program below....
    float angle = 0.0;
    
    // Initialize all three motors to 0 degrees
    rf_hip->Move(angle);
    rf_knee->Move(angle);
    rf_ankle->Move(angle);

    cout << "Controlling Right Front leg (hip, knee, ankle simultaneously)" << endl;
    cout << "Press KEY0 to decrement angle, KEY1 to increment angle. Ctrl+C to exit." << endl;

    int prev_key0 = 0, prev_key1 = 0;

    while (true) {
        int key0_pressed = pio->ReadButton(0);
        int key1_pressed = pio->ReadButton(1);

        // Only act on rising edge (button press)
        if (key0_pressed && !prev_key0) {
            angle -= 15.0;
            if (angle < DEGREE_MIN) angle = DEGREE_MIN;
            
            // Move all three motors simultaneously
            rf_hip->Move(angle);
            rf_knee->Move(angle);
            rf_ankle->Move(angle);
            
            cout << "All motors angle: " << angle << endl;
        }
        if (key1_pressed && !prev_key1) {
            angle += 15.0;
            if (angle > DEGREE_MAX) angle = DEGREE_MAX;
            
            // Move all three motors simultaneously
            rf_hip->Move(angle);
            rf_knee->Move(angle);
            rf_ankle->Move(angle);
            
            cout << "All motors angle: " << angle << endl;
        }

        prev_key0 = key0_pressed;
        prev_key1 = key1_pressed;

        usleep(1000); // Polling delay
    }

	// delete dynamic objects
	delete rf_hip;
	delete rf_knee;
	delete rf_ankle;
	delete pio;
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}
