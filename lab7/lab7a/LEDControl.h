#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include "DE1.h"

/**
 * @class LedControl
 * @brief Controls LEDs and reads switches/buttons on the DE1-SoC board through memory-mapped I/O register access
 */
class LedControl {
private:
    // Cyclone V FPGA device addresses
    static const unsigned int LEDR_BASE = 0x00000000;  ///< Red LEDs register offset
    static const unsigned int SW_BASE   = 0x00000040;  ///< Slide switches register offset
    static const unsigned int KEY_BASE  = 0x00000050;  ///< Push buttons register offset

public:
    /**
     * @brief Default constructor that initializes the LedControl object with no special initialization required as hardware access is handled through the DE1 object
     */
    LedControl();
    
    /**
     * @brief Write a value to all LEDs simultaneously where each bit in the value corresponds to one LED (bit 0 controls LED0, bit 1 controls LED1, etc.)
     * @param de1 DE1 object for register access
     * @param value Integer value to display on LEDs (bit pattern)
     */
    void WriteAllLeds(DE1 de1, int value);
    
    /**
     * @brief Control a single LED by turning it on or off without affecting other LEDs using read-modify-write operations
     * @param de1 DE1 object for register access
     * @param LedNum LED number to control (0-9)
     * @param state State to set (0=off, 1=on)
     */
    void WriteOneLed(DE1 de1, int LedNum, int state);
    
    /**
     * @brief Read all slide switch states where each bit represents the state of one switch (bit 0 = SW0, bit 1 = SW1, etc.)
     * @param de1 DE1 object for register access
     * @return Integer representing all switch states as a bit pattern
     */
    int ReadAllSwitches(DE1 de1);
    
    /**
     * @brief Read a single slide switch state by reading all switches and extracting the bit corresponding to the requested switch number
     * @param de1 DE1 object for register access
     * @param k Switch number to read (0-9)
     * @return State of the switch (0=down/off, 1=up/on)
     */
    int ReadOneSwitch(DE1 de1, int k);
};

#endif