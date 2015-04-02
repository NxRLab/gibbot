#ifndef PV7_BOARD_H
#define PV7_BOARD_H
/// @file

// inherit values from V6 board
#include <boards/pv6.h>

// except for board name
#undef BOARD_NAME

/// Board name for Primary v7 board
#define BOARD_NAME "Primary V7 Board" 

/// Current sensor resolution in mV per A
/**
    The ACS716KLATR-12CB has a sensing resolution of 37 mV/A.  While the sensor
    can safely read currents of up to +/- 37.5 A, it is "optimized" (i.e., most
    linear) for readings between +/- 12.5 A (it's 12CB part number denotes this
    optimized sensing range).  The amount of noise in a sensor reading at 0 A
    can be as much as +/- 11 mV (typical, 25 C - 125 C) and 1 mV (typical, 1
    standard deviation) otherwise.

    Given these noise characterstics 0 A can be anywhere between +/- 11 mV and 1
    A can be anywhere between 37 mV +/- 1 mV.  These are typical values measured
    by the manufacturer's test circuit and operating conditions.

    Assuming a 3.3 V PIC power supply and a 12-bit sensor, we have

    ADC counts per A =  2^12 (ADC counts) / 3.3 (V) * 37 (mV/A) / 1000 (mV/V),
                     =  45 (ADC counts / A)

    where the units of each value is in parentheses and the final value was
    computed using integer division.  Therefore, the ADC can resolve changes in
    current as small as 22 mA.

    @warning The chip soldered onto the v7 board is Allegro's ACS716...12CB
    chip.  This is not what is stated on the corresponding Eagle PCB, which
    states a different version of the ACS716 family of chips (each one differs
    in optimized sensing range).
*/

#define pv7_init_pins pv6_init_pins
#define pv7_init_periphs pv6_init_periphs
#define pv7_flash_lights pv6_flash_lights

extern const Board pv7;

#endif /* PV7_BOARD_H */
