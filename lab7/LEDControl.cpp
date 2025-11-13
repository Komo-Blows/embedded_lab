#include "LEDControl.h"

LedControl::LedControl() {}

/**
 * Show the input integer value on LEDs
 *
 * - Calls RegisterWrite to set all LEDs
 * @param de1   DE1 object for register access
 * @param value Value to show on LEDs
 */
void LedControl::WriteAllLeds(DE1 de1, int value) {
    de1.RegisterWrite(LEDR_BASE, value);
}

/**
 * Write to a single LED
 *
 * @param de1     DE1 object for register access
 * @param LedNum  LED number to control
 * @param state   State to set (0 or 1)
 */
void LedControl::WriteOneLed(DE1 de1, int LedNum, int state) {
    int current_reg = de1.RegisterRead(LEDR_BASE);
    int two_pow_lednum = 2;
    for (int i = 1; i < LedNum; i += 1) {
        two_pow_lednum *= 2;
    } // exponentiation
    int new_reg = current_reg & two_pow_lednum;
    de1.RegisterWrite(LEDR_BASE, current_reg);
}

/**
 * Read all switch values
 *
 * @param de1 DE1 object for register access
 * @return    Integer representing all switch states
 */
int LedControl::ReadAllSwitches(DE1 de1) {
    return de1.RegisterRead(SW_BASE);
}

/**
 * Read a single switch value
 *
 * @param de1 DE1 object for register access
 * @param k   Switch number to read
 * @return    State of the switch (0 or 1)
 */
int LedControl::ReadOneSwitch(DE1 de1, int k) {
    int j = de1.RegisterRead(SW_BASE);
    int bit_value = (j >> k) & 1;
    return bit_value;
}