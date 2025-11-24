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
	
	
	
	
	
	
	
	
	
	
	// detele dynamic objects
	delete motor;
	delete pio;		
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}	
