#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "DE1.h"

/**
 * @class SevenSegment
 * @brief Controls the six 7-segment displays on the DE1-SoC board
 * 
 * This class provides an interface to control the HEX displays (HEX0-HEX5)
 * on the DE1-SoC FPGA board. It inherits from DE1 to access memory-mapped
 * I/O registers for the displays. The displays can show hexadecimal digits
 * (0-F) and are organized into two register groups:
 * - HEX3_HEX0_BASE: Controls displays 0, 1, 2, 3
 * - HEX5_HEX4_BASE: Controls displays 4, 5
 */
class SevenSegment: DE1 {
    private:
        unsigned int reg0_hexValue;  ///< Register value for HEX0-HEX3 displays
        unsigned int reg1_hexValue;  ///< Register value for HEX4-HEX5 displays
        
    public:
        /**
         * @brief Default constructor
         * 
         * Initializes a SevenSegment object with all display registers set to 0x0.
         * All displays will be blank after construction.
         */
        SevenSegment();
        
        /**
         * @brief Parameterized constructor
         * 
         * Initializes a SevenSegment object with specified initial values for
         * the display registers.
         * 
         * @param regHexVal0 Initial value for HEX0-HEX3 register
         * @param regHexVal1 Initial value for HEX4-HEX5 register
         */
        SevenSegment(unsigned int regHexVal0, unsigned int regHexVal1);
        
        /**
         * @brief Destructor
         * 
         * Cleans up the SevenSegment object by clearing all displays
         * before destruction.
         */
        ~SevenSegment();
        
        /**
         * @brief Clear all six 7-segment displays
         * 
         * Sets all display registers to 0x0, turning off all segments
         * on all six displays (HEX0-HEX5).
         */
        void Hex_ClearAll();
        
        /**
         * @brief Clear a specific 7-segment display
         * 
         * Clears (turns off) all segments of a single display without
         * affecting the other displays. Uses bit masking to preserve
         * the state of other displays in the same register.
         * 
         * @param index Display number to clear (0-5)
         *              - 0-3: HEX0-HEX3
         *              - 4-5: HEX4-HEX5
         * 
         * @note Prints error message if index is out of valid range [0,5]
         */
        void Hex_ClearSpecific(int index);
        
        /**
         * @brief Write a hexadecimal digit to a specific display
         * 
         * Displays a hexadecimal digit (0-F) on a specific 7-segment display.
         * The hardware decoder automatically converts the value to the
         * appropriate segment pattern.
         * 
         * @param display_id Display number (0-5)
         *                   - 0-3: Uses HEX3_HEX0_BASE register
         *                   - 4-5: Uses HEX5_HEX4_BASE register
         * @param value Hexadecimal digit to display (0-15 / 0x0-0xF)
         * 
         * @note Prints error message if display_id is out of range [0,5]
         * @note Prints error message if value is out of range [0,15]
         */
        void Hex_WriteSpecific(int display_id, int value);
        
        /**
         * @brief Display a signed 5-digit number across multiple displays
         * 
         * Displays a signed integer number on the 7-segment displays.
         * The number is broken into individual digits and shown from right
         * to left (HEX0 = ones place, HEX1 = tens, etc.). If the number is
         * negative, a minus sign is displayed on HEX5.
         * 
         * Features:
         * - Handles both positive and negative numbers
         * - Displays up to 5 digits (range: -99999 to 99999)
         * - Numbers > 99999 are clamped to 99999
         * - Leading zeros are displayed
         * - Minus sign shown on leftmost display (HEX5) for negative numbers
         * 
         * @param number Integer number to display (-99999 to 99999)
         * 
         * @example
         * Hex_WriteNumber(12345);  // Displays "012345" (HEX5 blank)
         * Hex_WriteNumber(-9876);  // Displays "-09876"
         * Hex_WriteNumber(42);     // Displays "000042"
         * 
         * Display layout:
         * [HEX5][HEX4][HEX3][HEX2][HEX1][HEX0]
         * [ -  ][10k ][1k  ][100 ][ 10 ][ 1  ]
         */
        void Hex_WriteNumber(int number);
};

#endif