
#ifndef GIBBOT_H
#define	GIBBOT_H

/*
 * QEI Motor A     RP69/RD5
 * QEI Motor B     RP68/RD4
 * QEI TopMag A    RPI32/RB0
 * QEI TopMag B    RPI33/RB1
 * QEI BotMag A    RPI120/RG8
 * QEI BotMag B    RPI119/RG7
 * XBee RX         RP118/RG6
 * XBee TX         RP87/RE7
 * XBee CTS        RP97/RF1
 * XBee RTS        RP96/RF0
 * IMU SCL         SCL1/RG2
 * IMU SDA         SDA1/RG3
 * IMU Interrupt   RF6
 * dsPIC SCL       SCL2/RF5
 * dsPIC SDA       SDA2/RF4
 * Current Sense   AN30/RE6
 * Hall 1          RD1
 * Hall 2          RD2          
 * Hall 3          RD3
 * LED 1           RD11
 * LED 2           RD0
 * LED 3           RC13
 * LED 4           RC14
 * Top Magnet      RD10
 * Low Magnet      RB15
 * User            RB2
 */

//Rotary encoder outputs from the BLDC motor
#define S1 PORTDbits.RD3
#define S2 PORTDbits.RD2
#define S3 PORTDbits.RD1

//Switches and outputs
#define USER PORTBbits.RB2
#define TOPMAG LATDbits.LATD10
#define LED1 LATDbits.LATD11
#define LED2 LATDbits.LATD0
#define LED3 LATCbits.LATC13
#define LED4 LATCbits.LATC14
#endif	/* GIBBOT_H */

