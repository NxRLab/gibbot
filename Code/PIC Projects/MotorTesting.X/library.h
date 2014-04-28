/* 
 * File:   library.h
 * Author: ajgriesemer
 *
 * Created on January 14, 2014, 10:03 AM
 */

#ifndef LIBRARY_H
#define	LIBRARY_H

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


void Initialize_CN(void);
void Initialize_PWM(void);
void High(int pin);
void Low(int pin);
void Float(int pin);
void commutate(int state);
void kick(void);
void Lights(void);

extern int direction;
#endif	/* LIBRARY_H */

