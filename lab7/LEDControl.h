#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include "DE1.h"

class LedControl {
private:
    // Cyclone V FPGA device addresses
    static const unsigned int LEDR_BASE = 0x00000000;  // Leds offset
    static const unsigned int SW_BASE   = 0x00000040;  // Switches offset
    static const unsigned int KEY_BASE  = 0x00000050;  // Push buttons offset

public:
    LedControl();
    
    /**
     * Show the input integer value on LEDs
     * 
     * @param de1   DE1 object for register access
     * @param value Value to show on LEDs
     */
    void WriteAllLeds(DE1 de1, int value);
    
    /**
     * Write to a single LED
     * 
     * @param de1     DE1 object for register access
     * @param LedNum  LED number to control
     * @param state   State to set (0 or 1)
     */
    void WriteOneLed(DE1 de1, int LedNum, int state);
    
    /**
     * Read all switch values
     * 
     * @param de1 DE1 object for register access
     * @return    Integer representing all switch states
     */
    int ReadAllSwitches(DE1 de1);
    
    /**
     * Read a single switch value
     * 
     * @param de1 DE1 object for register access
     * @param k   Switch number to read
     * @return    State of the switch (0 or 1)
     */
    int ReadOneSwitch(DE1 de1, int k);
};

#endif