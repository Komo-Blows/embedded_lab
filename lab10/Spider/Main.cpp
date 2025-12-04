/**
 * @file   Main.cpp
 * @Author John Kimani (j.kimani@northeastern.edu)
 * @date   November, 2025
 * @brief  Tests the Spider robot rc servo movements
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include "MMap.h"
#include "Spider.h"
#include "LEDControl.h" // Use as needed

using namespace std;

int main(int argc, char *argv[])
{
	cout << "\nProgram Starting...!" << endl; 
	int speed = 0;
	MMap *m_map = new MMap();
    Spider *spider = new Spider(m_map);

	cout << "Spider Init" << endl;
	spider->Init();
	
	cout << "Spider Standup" << endl;	
	spider->Standup();

	cout << "Waiting for Command..." << endl;
	cout << "t (reset), p (speed), q (stop), w (foward), a (left), s (back), d (right) or z (square):" << endl;
	bool done = false;
	while (!done)
	{
		char cmd_chr;
		cout << "Enter Next Command: ";
		cin >> cmd_chr;
		
		switch (cmd_chr)
		{
			case 't':
				cout << "Reset..." << endl;
				spider->Reset();
				break;
			case 'p':
				cout << "Set speed..." << endl;
				cout << "Enter new speed [0 - 100]: ";
				cin >> speed;
				spider->SetSpeed(speed);
				break;
			case 'w':
				cout << "Move Forward..." << endl;
				spider->MoveForward(1);
				break;
			case 'a':
				cout << "Rotate Left..." << endl;
				spider->RotateLeft(1);
				break;
			case 's':
				cout << "Move Backward..." << endl;
				spider->MoveBackward(1);
				break;
			case 'd':
				cout << "Rotate Right..." << endl;
				spider->RotateRight(1);
				break;
			case 'q':
				cout << "STOP Spider" << endl;
				done = true;
				break;		
			case 'z':
				spider->MoveSquare();
				done = true;
				break;		
			default:
				cout << "IDLE or UNKNOWN COMMAND" << endl;
				break;
		}
	}
	cout << "Spider Reset" << endl;	
	spider->Reset();
	delete spider;
	delete m_map;
	return 0;
}

