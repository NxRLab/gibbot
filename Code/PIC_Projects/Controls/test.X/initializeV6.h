/*
 * QEI Magnet      RP99
 * QEI Magnet      RP98
 * XBee RX         RP71
 * XBee TX         RP70
 * XBee CTS        RP65
 * XBee RTS        RP66
 * IMU SCL         SCL1/RG2
 * IMU SDA         SDA1/RG3
 * IMU Interrupt   RF6
 * dsPIC SCL       SCL2/RF5
 * dsPIC SDA       SDA2/RF4
 * Current Sense   AN8
 * Hall 1          RD3
 * Hall 2          RD4          
 * Hall 3          RD5
 * LED 1           RB13
 * LED 2           RB12
 * LED 3           RD11
 * LED 4           RD0
 * Top Magnet      RB14
 * User            RD10
 */

#ifndef INITIALIZEV6_H
#define	INITIALIZEV6_H

#define LED1 LATBbits.LATB13
#define LED2 LATBbits.LATB12
#define LED3 LATDbits.LATD11
#define LED4 LATDbits.LATD0
#define USER PORTDbits.RD10
#define TOPMAG LATBbits.LATB14

#define RST_POR    (1<<0)
#define RST_BOR    (1<<1)
#define RST_IDLE   (1<<2)
#define RST_SLEEP  (1<<3)
#define RST_WDTO   (1<<4)
#define RST_SWDTEN (1<<5)
#define RST_SWR    (1<<6)
#define RST_EXTR   (1<<7)
#define RST_VREGS  (1<<8)
#define RST_CM     (1<<9)
#define RST_VREGSF (1<<11)
#define RST_SBOREN (1<<13)
#define RST_IOPUWR (1<<14)
#define RST_TRAPR  (1<<15)

void initialize(void);
void lights(void);
extern unsigned short resetStat;
#endif	/* INITIALIZE_H */

