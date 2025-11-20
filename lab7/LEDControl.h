#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include "DE1.h"

/**
 * @class LEDControl
 * @brief Controls LEDs and reads switches on the DE1-SoC board
 *
 * This class provides a high-level interface for controlling the red LEDs
 * and reading the slide switches on the DE1-SoC FPGA board.
 * It uses the DE1 base class for memory-mapped I/O register access.
 */
class LEDControl {
private:
    // Cyclone V FPGA device addresses
    static const unsigned int LEDR_BASE = 0x00000000;  ///< Red LEDs register offset
    static const unsigned int SW_BASE   = 0x00000040;  ///< Slide switches register offset
    
    unsigned int leds_regValue; ///< State of the ten LEDs register

public:
    /**
     * @brief Constructor
     * 
     * Initializes the LEDControl object and the leds_regValue data member.
     */
    LEDControl();
    
    /**
     * @brief Destructor
     * 
     * Prints the message "Closing LEDs, Switches, & Buttons...".
     */
    ~LEDControl();
    
    /**
     * @brief Write a value to a single LED
     *
     * Turns a specific LED on (value=1) or off (value=0) without affecting other LEDs.
     * Updates the leds_regValue private data member.
     *
     * @param de1 DE1 object for register access
     * @param ledNum LED number to control (0-9)
     * @param value State to set (0=off, 1=on)
     */
    void Write1Led(DE1& de1, int ledNum, int value);
    
    /**
     * @brief Write a value to all LEDs simultaneously
     *
     * Sets all red LEDs based on the binary representation of the value.
     * Each bit in the value corresponds to one LED (bit 0 = LED0, etc.).
     * Updates the leds_regValue private data member.
     *
     * @param de1 DE1 object for register access
     * @param value Integer value to display on LEDs (0-1023)
     */
    void WriteAllLeds(DE1& de1, int value);
    
    /**
     * @brief Read a single slide switch state
     *
     * Returns the state of a specific switch by reading all switches
     * and extracting the bit corresponding to the requested switch number.
     *
     * @param de1 DE1 object for register access
     * @param switchNum Switch number to read (0-9)
     * @return State of the switch (0=down/off, 1=up/on)
     */
    int Read1Switches(DE1& de1, int switchNum);
    
    /**
     * @brief Read all slide switch states
     *
     * Returns an integer where each bit represents the state of one switch.
     * Switch positions are mapped to bits (bit 0 = SW0, bit 1 = SW1, etc.).
     *
     * @param de1 DE1 object for register access
     * @return Integer representing all switch states (0-1023)
     */
    int ReadAllSwitches(DE1& de1);
};

#endif