#include "LEDControl.h"
#include <iostream>

/**
 * @brief Constructor
 * 
 * Initializes the LEDControl object and the leds_regValue data member to 0.
 */
LEDControl::LEDControl() : leds_regValue(0) {
}

/**
 * @brief Destructor
 * 
 * Prints the message "Closing LEDs, Switches, & Buttons...".
 */
LEDControl::~LEDControl() {
    std::cout << "Closing LEDs, Switches, & Buttons..." << std::endl;
}

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
void LEDControl::Write1Led(DE1& de1, int ledNum, int value) {
    // Read current LED register state
    int current_reg = de1.RegisterRead(LEDR_BASE);
    
    // Calculate the bit mask for the specified LED
    int bit_mask = 1 << ledNum;
    
    int new_reg;
    if (value == 1) {
        // Turn on the LED by setting the bit
        new_reg = current_reg | bit_mask;
    } else {
        // Turn off the LED by clearing the bit
        new_reg = current_reg & ~bit_mask;
    }
    
    // Write the new value to the register
    de1.RegisterWrite(LEDR_BASE, new_reg);
    
    // Update the private data member
    leds_regValue = new_reg;
}

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
void LEDControl::WriteAllLeds(DE1& de1, int value) {
    // Write the value to the LED register
    de1.RegisterWrite(LEDR_BASE, value);
    
    // Update the private data member
    leds_regValue = value;
}

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
int LEDControl::Read1Switches(DE1& de1, int switchNum) {
    // Read all switches
    int all_switches = de1.RegisterRead(SW_BASE);
    
    // Extract the bit for the specified switch
    int bit_value = (all_switches >> switchNum) & 1;
    
    return bit_value;
}

/**
 * @brief Read all slide switch states
 *
 * Returns an integer where each bit represents the state of one switch.
 * Switch positions are mapped to bits (bit 0 = SW0, bit 1 = SW1, etc.).
 *
 * @param de1 DE1 object for register access
 * @return Integer representing all switch states (0-1023)
 */
int LEDControl::ReadAllSwitches(DE1& de1) {
    return de1.RegisterRead(SW_BASE);
}