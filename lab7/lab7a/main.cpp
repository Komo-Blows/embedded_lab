/**
* Main operates the DE1-SoC 7-Segment Displays
* This program writes an integer number on the 7-Segment Displays
*/
#include <iostream>
using namespace std;
#include "SevenSegment.h"
#include <unistd.h>

int main(void) {
int count = -25;
    // Create a pointer object of the SevenSegment class
    SevenSegment *display = new SevenSegment(0x0, 0x0);
    cout << "Program Starting...!" << endl;
    // Update the display every second
    while( count <= 25 ) {
        int hex_value = count*count*count; // Value to display
        cout << "Count: " << count << ", Value = " << hex_value << endl;
        display->Hex_WriteNumber(hex_value); // display value
        sleep(1); // wait for 1 second
        count++; // increment count
    }
    delete display; // delete class object
    cout << "Terminating...!" << endl;
    return 0;
}
