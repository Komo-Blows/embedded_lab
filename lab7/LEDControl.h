#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include "DE1.h"

/**
 * @class LedControl
 * @brief Controls LEDs and reads switches/buttons on the DE1-SoC board
 * 
 * This class provides a high-level interface for controlling the red LEDs
 * and reading the slide switches and push buttons on the DE1-SoC FPGA board.
 * It uses the DE1 base class for memory-mapped I/O register access.
 */
class LedControl {
private:
    // Cyclone V FPGA device addresses
    static const unsigned int LEDR_BASE = 0x00000000;  ///< Red LEDs register offset
    static const unsigned int SW_BASE   = 0x00000040;  ///< Slide switches register offset
    static const unsigned int KEY_BASE  = 0x00000050;  ///< Push buttons register offset

public:
    /**
     * @brief Default constructor
     * 
     * Initializes the LedControl object. No special initialization
     * is required as hardware access is handled through the DE1 object.
     */
    LedControl();
    
    /**
     * @brief Write a value to all LEDs simultaneously
     * 
     * Sets all red LEDs based on the binary representation of the value.
     * Each bit in the value corresponds to one LED:
     * - Bit 0 controls LED0
     * - Bit 1 controls LED1
     * - etc.
     * 
     * @param de1 DE1 object for register access
     * @param value Integer value to display on LEDs (bit pattern)
     * 
     * @example
     * WriteAllLeds(de1, 0b1010); // Turns on LED1 and LED3, others off
     * WriteAllLeds(de1, 1023);   // Turns on all 10 LEDs (0x3FF)
     */
    void WriteAllLeds(DE1 de1, int value);
    
    /**
     * @brief Control a single LED
     * 
     * Turns a specific LED on or off without affecting other LEDs.
     * Reads the current LED state, modifies the specified bit, and writes back.
     * 
     * @param de1 DE1 object for register access
     * @param LedNum LED number to control (0-9)
     * @param state State to set (0=off, 1=on)
     * 
     * @note Current implementation may have a bug in the bit manipulation logic
     */
    void WriteOneLed(DE1 de1, int LedNum, int state);
    
    /**
     * @brief Read all slide switch states
     * 
     * Returns an integer where each bit represents the state of one switch.
     * Switch positions are mapped to bits:
     * - Bit 0 = SW0
     * - Bit 1 = SW1
     * - etc.
     * 
     * @param de1 DE1 object for register access
     * @return Integer representing all switch states as a bit pattern
     * 
     * @example
     * int switches = ReadAllSwitches(de1);
     * if (switches & 0x01) { // Check if SW0 is up }
     */
    int ReadAllSwitches(DE1 de1);
    
    /**
     * @brief Read a single slide switch state
     * 
     * Returns the state of a specific switch by reading all switches
     * and extracting the bit corresponding to the requested switch number.
     * 
     * @param de1 DE1 object for register access
     * @param k Switch number to read (0-9)
     * @return State of the switch (0=down/off, 1=up/on)
     * 
     * @example
     * if (ReadOneSwitch(de1, 0) == 1) {
     *     // Switch 0 is in the up position
     * }
     */
    int ReadOneSwitch(DE1 de1, int k);
};

#endif