#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "DE1.h"

class SevenSegment: DE1 {
    private:
        unsigned int reg0_hexValue;
        unsigned int reg1_hexValue;
    public:
        SevenSegment(unsigned int regHexVal0, unsigned int regHexVal1);
        ~SevenSegment();
        void Hex_ClearAll();
        void Hex_ClearSpecific(int index);
        void Hex_WriteSpecific(int display_id, int value);
        void Hex_WriteNumber(int number);
};

#endif
