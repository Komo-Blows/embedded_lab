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

    while (true) {
        uint32_t key_val = m_map->RegisterRead(0x00000050); // this is the push button base I think

        bool key0_pressed = key_val & 0x1;
        bool key1_pressed = key_val & 0x2;

        if (key0_pressed) {
            angle -= 15.0;
            if (angle < DEGREE_MIN) angle = DEGREE_MIN;
            motor->Move(angle);
            cout << "Angle: " << angle << endl;
            usleep(300000); // Debounce delay
        }
        if (key1_pressed) {
            angle += 15.0;
            if (angle > DEGREE_MAX) angle = DEGREE_MAX;
            motor->Move(angle);
            cout << "Angle: " << angle << endl;
            usleep(300000); // Debounce delay
        }
        usleep(10000); // Polling delay
    }

	// detele dynamic objects
	delete motor;
	delete pio;
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}
