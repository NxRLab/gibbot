// JVP002 Board Header

#ifndef __JVP002_H

#define __JVP002_H

#include <p32xxxx.h>
#include <sys/attribs.h>

#define UP		1
#define DOWN	0

#define BUTTON_A	PORTGbits.RG15
#define BUTTON_B	PORTAbits.RA0
#define BUTTON_C	PORTAbits.RA1
#define BUTTON_D	PORTDbits.RD14

#define LED3		PORTDbits.RD15
#define LED2		PORTFbits.RF3
#define LED1		PORTFbits.RF2

#define ADC_COUNTS	1023

#define MAX_PWMT2	0x04E2
#define MAX_PWMT3	0x61A8

#define MOTORR	OC1RS
#define MOTORL	OC2RS

#define PWM0	OC3RS
#define PWM1	OC4RS

#define PWM_ADJ	0.075


#else

#endif