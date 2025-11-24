#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "DE1.h"

/**
 * @class SevenSegment
 * @brief Controls the six 7-segment displays (HEX0-HEX5) on the DE1-SoC FPGA board using memory-mapped I/O registers to display hexadecimal digits organized into two register groups
 */
class SevenSegment: DE1 {
    private:
        unsigned int reg0_hexValue;  ///< Register value for HEX0-HEX3 displays
        unsigned int reg1_hexValue;  ///< Register value for HEX4-HEX5 displays
        static const unsigned int SEGMENT_MAP[16]; ///< 7-seg patterns for 0-F
        
    public:
        /**
         * @brief Default constructor that initializes a SevenSegment object with all display registers set to 0x0 resulting in blank displays
         */
        SevenSegment();
        
        /**
         * @brief Parameterized constructor that initializes a SevenSegment object with specified initial values for the display registers
         * @param regHexVal0 Initial value for HEX0-HEX3 register
         * @param regHexVal1 Initial value for HEX4-HEX5 register
         */
        SevenSegment(unsigned int regHexVal0, unsigned int regHexVal1);
        
        /**
         * @brief Destructor that cleans up the SevenSegment object by clearing all displays before destruction
         */
        ~SevenSegment();
        
        /**
         * @brief Clear all six 7-segment displays by setting all display registers to 0x0 and turning off all segments on HEX0-HEX5
         */
        void Hex_ClearAll();
        
        /**
         * @brief Clear a specific 7-segment display by turning off all segments of a single display without affecting other displays using bit masking
         * @param index Display number to clear (0-5 where 0-3 are HEX0-HEX3 and 4-5 are HEX4-HEX5)
         */
        void Hex_ClearSpecific(int index);
        
        /**
         * @brief Write a hexadecimal digit to a specific display where the hardware decoder automatically converts the value to the appropriate segment pattern
         * @param display_id Display number (0-5 where 0-3 use HEX3_HEX0_BASE register and 4-5 use HEX5_HEX4_BASE register)
         * @param value Hexadecimal digit to display (0-15 / 0x0-0xF)
         */
        void Hex_WriteSpecific(int display_id, int value);
        
        /**
         * @brief Display a signed 5-digit number across multiple displays breaking the number into individual digits shown from right to left (HEX0 = ones, HEX1 = tens, etc.) with optional minus sign on HEX5 for negative numbers, handling range -99999 to 99999 with leading zeros displayed
         * @param number Integer number to display (-99999 to 99999)
         */
        void Hex_WriteNumber(int number);
};

#endif