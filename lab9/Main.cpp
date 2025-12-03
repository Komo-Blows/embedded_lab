/**
 * @file   Main.cpp
 * @brief  Tests the Spider robot rc servo movements
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
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
    Motor *motor = new Motor(m_map, RF_ankle);

	// TO DO: Write code to test your program below....
    float angle = 0.0;
    motor->Move(angle); // Ensure initial position

    cout << "Press KEY0 to decrement angle, KEY1 to increment angle. Ctrl+C to exit." << endl;

    int prev_key0 = 0, prev_key1 = 0;

    while (true) {
        int key0_pressed = pio->ReadButton(0);
        int key1_pressed = pio->ReadButton(1);

        // Only act on rising edge (button press)
        if (key0_pressed && !prev_key0) {
            angle -= 15.0;
            if (angle < DEGREE_MIN) angle = DEGREE_MIN;
            motor->Move(angle);
            cout << "Angle: " << angle << endl;
        }
        if (key1_pressed && !prev_key1) {
            angle += 15.0;
            if (angle > DEGREE_MAX) angle = DEGREE_MAX;
            motor->Move(angle);
            cout << "Angle: " << angle << endl;
        }

        prev_key0 = key0_pressed;
        prev_key1 = key1_pressed;

        usleep(10000); // Polling delay
    }

	// detele dynamic objects
	delete motor;
	delete pio;
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}
