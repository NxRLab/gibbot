#ifndef SV6_BOARD_H
#define SV6_BOARD_H
/// @file

#include <brd.h>

#define BOARD_NAME "Secondary V6 Board" /// Board name for Secondary v6 board

// pins
#define LED1 LATDbits.LATD9
#define LED2 LATDbits.LATD10
#define LED3 LATDbits.LATD11
#define LED4 LATDbits.LATD0
#define USER PORTDbits.RD8
#define MAG LATBbits.LATB15

// LED on/off
#define LED_ON 0
#define LED_OFF 1

// resolution of sensors
#define US_DIGITAL_E3_1800_750_NE_H_D_B 1800

extern void sv6_init_pins();
extern void sv6_flash_lights();
extern void sv6_init_periphs();
extern const Board sv6;

#endif /* SV6_BOARD_H */
