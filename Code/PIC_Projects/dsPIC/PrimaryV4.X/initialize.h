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
 * LED 1           RD9
 * LED 2           RD10
 * LED 3           RD11
 * LED 4           RD0
 * Top Magnet      RF0
 * User            RD8
 */

#ifndef INITIALIZE_H
#define	INITIALIZE_H

#define LED1 LATDbits.LATD9
#define LED2 LATDbits.LATD10
#define LED3 LATDbits.LATD11
#define LED4 LATDbits.LATD0
#define USER PORTDbits.RD8

void initialize(void);
void lights(void);
void resetTest(void);

#endif	/* INITIALIZE_H */

