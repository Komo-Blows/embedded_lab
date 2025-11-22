#include "SevenSegment.h"
#include <iostream>

// Segment patterns for characters 0-9, A-F (from lab7table.md)
const unsigned int SevenSegment::SEGMENT_MAP[16] = {
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0x77, // A
    0x7c, // b
    0x39, // C
    0x5e, // d
    0x79, // E
    0x71  // f
};

SevenSegment::SevenSegment(unsigned int regHexVal0, unsigned int regHexVal1): DE1() {
    reg0_hexValue = regHexVal0;
    reg1_hexValue = regHexVal1;
}

SevenSegment::~SevenSegment() {
    SevenSegment::Hex_ClearAll();
}

void SevenSegment::Hex_ClearAll() {
    reg0_hexValue = 0x0;
    reg1_hexValue = 0x0;
    RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
    RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);
}

void SevenSegment::Hex_ClearSpecific(int index) {
    if (index < 0 || index > 5) {
        std::cout << "Thats not a good number for this ([0,5] range)" << std::endl;
        return;
    }

    if (index <= 3) {
        unsigned int mask = ~(0xFF << (index * 8));
        reg0_hexValue = reg0_hexValue & mask;
        RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
    } else {
        int adjustedIndex = index - 4;
        unsigned int mask = ~(0xFF << (adjustedIndex * 8));
        reg1_hexValue = reg1_hexValue & mask;
        RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);
    }
}

void SevenSegment::Hex_WriteSpecific(int display_id, int value) {
    if (display_id < 0 || display_id > 5) {
        std::cout << "That's a bad number for the display_id ([0,5] range)" << std::endl;
        return;
    }

    if (value < 0 || value > 15) {
        std::cout << "That's a bad number for the value ([0, 15] range)" << std::endl;
        return;
    }

    if (display_id <= 3) {
        unsigned int pattern = SEGMENT_MAP[value];
        unsigned int clearMask = 0xFFu << (display_id * 8);
        unsigned int newValue = pattern << (display_id * 8);
        reg0_hexValue = (reg0_hexValue & ~clearMask) | newValue;
        RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
    } else {
        int adjusted_id = display_id - 4;
        unsigned int pattern = SEGMENT_MAP[value];
        unsigned int clearMask = 0xFFu << (adjusted_id * 8);
        unsigned int newValue = pattern << (adjusted_id * 8);
        reg1_hexValue = (reg1_hexValue & ~clearMask) | newValue;
        RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);
    }
}

void SevenSegment::Hex_WriteNumber(int number) {
    // Clear all displays first
    Hex_ClearAll();
    
    // Handle negative numbers
    bool isNegative = false;
    if (number < 0) {
        isNegative = true;
        number = -number;
    }
    
    // Limit to 5 digits (0-99999)
    if (number > 99999) {
        number = 99999;
    }
    
    // Extract individual digits
    int digit0 = number % 10;           // Ones place
    int digit1 = (number / 10) % 10;    // Tens place
    int digit2 = (number / 100) % 10;   // Hundreds place
    int digit3 = (number / 1000) % 10;  // Thousands place
    int digit4 = (number / 10000) % 10; // Ten-thousands place
    
    // Write digits to displays (right to left: display 0 through 4)
    Hex_WriteSpecific(0, digit0);
    Hex_WriteSpecific(1, digit1);
    Hex_WriteSpecific(2, digit2);
    Hex_WriteSpecific(3, digit3);
    Hex_WriteSpecific(4, digit4);
    
    // If negative, display minus sign on display 5
    // Minus sign on 7-segment: 0x40 (middle horizontal segment)
    if (isNegative) {
        int adjusted_id = 5 - 4;  // Display 5 is in reg1
        unsigned int clearMask = 0xFF << (adjusted_id * 8);
        unsigned int newValue = 0x40 << (adjusted_id * 8);  // Minus sign pattern
        reg1_hexValue = (reg1_hexValue & ~clearMask) | newValue;
        RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);
    }
}
