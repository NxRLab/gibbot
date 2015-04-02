#ifndef PV6_BOARD_H
#define PV6_BOARD_H
/// @file

#include <brd.h>

#define BOARD_NAME "Primary V6 Board" /// Board name for Primary v6 board

// pins
#define LED1 LATBbits.LATB13
#define LED2 LATBbits.LATB12
#define LED3 LATDbits.LATD11
#define LED4 LATDbits.LATD0
#define USER PORTDbits.RD10
#define MAG LATBbits.LATB14

/// Reads the state of the Hall effect sensor on the BLDC
/** 
    This is a read-only macro.  Writes will lead to compiler errors.  Pins D3-D5
    are wired to the motor's hall effect sensors.  The commutation pattern
    requires D5 to be the MSb and D3 to be the LSb of a 3-bit number.  This
    leads to a shift of 3 bits to the right and a mask of 0b111 = 7 to only keep
    those 3 bits of interest.
*/
#define HALL ((PORTD >> 3) & 7)

// LED on/off
#define LED_ON 0
#define LED_OFF 1

// resolution of various sensors
#define ALLEGRO_ACS716_12CB 37.0 // mV / A
#define US_DIGITAL_E3_1800_750_NE_H_D_B 1800 // counts per rev

extern void pv6_init_pins();
extern void pv6_flash_lights();
extern void pv6_init_periphs();
extern const Board pv6;

#endif /* PV6_BOARD_H */
