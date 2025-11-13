#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "DE1.h"

class SevenSegment: DE1 {
    private:
        unsigned int reg0_hexValue;
        unsigned int reg1_hexValue;
    public:
        SevenSegment(unsigned int regHex, unsigned int regHexVal);
        ~SevenSegment();
        void Hex_ClearAll();
        void Hex_ClearSpecific(int index);
        void Hex_WriteSpecific(int displayID, int value);
        void Hex_WriteNumber(int number);
};

#endif
