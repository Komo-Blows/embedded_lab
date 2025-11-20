#include <iostream>
using namespace std;
#include "SevenSegment.h"
#include "LEDControl.h"
#include "DE1.h"
#include <unistd.h>

const unsigned int KEY_BASE = 0x00000050;

int PushButtonGet(DE1 *de1){
    int i = de1->RegisterRead(KEY_BASE);
    switch (i){
        case 0: return -1;
        case 1: return 0;
        case 2: return 1;
        case 4: return 2;
        case 8: return 3;
        default: return 4;
    }
}

int main(void) {
    cout << "Program Starting...!" << endl;

    SevenSegment *display = new SevenSegment(0x0, 0x0);
    DE1 *de1 = new DE1();
    LEDControl *ledControl = new LEDControl();

    int i = ledControl->ReadAllSwitches(*de1);
    int save = -1;
    ledControl->WriteAllLeds(*de1, i);

    int digit0 = i & 0xF;
    int digit1 = (i >> 4) & 0xF;
    int digit2 = (i >> 8) & 0xF;
    display->Hex_WriteSpecific(0, digit0);
    display->Hex_WriteSpecific(1, digit1);
    display->Hex_WriteSpecific(2, digit2);

    while(true) {
        int newin = PushButtonGet(de1);
        if (newin != save){
            if (save == 4) {save = newin; continue;}
            save = newin;
            switch (save){
                case -1: break;
                case 0: i += 1; break;
                case 1: i -= 1; break;
                case 2: i >>= 1; break;
                case 3: i <<= 1; break;
                case 4: i = ledControl->ReadAllSwitches(*de1); break;
            }

            ledControl->WriteAllLeds(*de1, i);

            digit0 = i & 0xF;
            digit1 = (i >> 4) & 0xF;
            digit2 = (i >> 8) & 0xF;
            display->Hex_WriteSpecific(0, digit0);
            display->Hex_WriteSpecific(1, digit1);
            display->Hex_WriteSpecific(2, digit2);

            cout << "Value: 0x" << hex << i << dec << endl;
        }
    }

    delete display;
    delete ledControl;
    delete de1;
    cout << "Terminating...!" << endl;

    return 0;
}
