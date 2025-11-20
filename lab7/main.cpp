#include <iostream>
using namespace std;
#include "SevenSegment.h"
#include "LEDControl.h"
#include <unistd.h>

int main(void) {
    cout << "Program Starting...!" << endl;

    SevenSegment *display = new SevenSegment(0x0, 0x0);
    DE1 *de1 = new DE1();
    LEDControl *ledControl = new LEDControl();

    int previousValue = -1;

    while(true) {
        int switchValue = ledControl->ReadAllSwitches(*de1);

        if (switchValue != previousValue) {
            ledControl->WriteAllLeds(*de1, switchValue);

            int digit0 = switchValue & 0xF;
            int digit1 = (switchValue >> 4) & 0xF;
            int digit2 = (switchValue >> 8) & 0xF;

            display->Hex_WriteSpecific(0, digit0);
            display->Hex_WriteSpecific(1, digit1);
            display->Hex_WriteSpecific(2, digit2);

            cout << "Value: 0x" << hex << switchValue << dec << endl;

            previousValue = switchValue;
        }

        usleep(50000);
    }

    delete display;
    delete ledControl;
    delete de1;
    cout << "Terminating...!" << endl;

    return 0;
}
