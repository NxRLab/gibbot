#ifndef BREAKOUT_BOARD_H
#define BREAKOUT_BOARD_H
/// @file

#include <xc.h>
#include <brd.h>

/// @TODO figure out order of includes for boards

#define BOARD_NAME "Breakout Board" /// Board name for Breakout board

// pins
#define LED1 LATCbits.LATC14
#define LED2 LATCbits.LATC13
#define LED3 LATDbits.LATD0
#define LED4 LATDbits.LATD11
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
#define HALL(x) ((PORTD >> 3) & 7)

// LED on/off
#define LED_ON 1
#define LED_OFF 0

extern void breakout_init_pins();
extern void breakout_flash_lights();
extern void breakout_init_periphs();
extern const Board breakout;

#endif /* BREAKOUT_BOARD_H */
