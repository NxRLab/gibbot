/* 
 * File:   gibbot.h
 * Author: ajgriesemer
 *
 * Created on July 30, 2013, 10:39 AM
 */

#ifndef GIBBOT_H
#define	GIBBOT_H

#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>

#define SYSFREQ 7370000
#define S3 PORTBbits.RB7
#define S2 PORTBbits.RB8
#define S1 PORTBbits.RB9


void init_pwm(void);
void init_cn(void);
void init_uart (void);
void init_qei(void);
void ADC_Init(void);

void duty(int duty);
void High(int pin);
void Float(int pin);
void Low(int pin);
void commutate(int state);
void kick(void);
void Read_ADC(void);

void state0(void);
void state1(void);
void state2(void);
void state3(void);
void state4(void);
void state5(void);
void state6(void);

extern char store;
extern char array[100];
extern char direction;
extern int turncount;
extern int ADResultAN3_1;
extern int ADResultAN3_2;
extern int ADResultAN4;
extern int ADResultAN5;


#endif	/* GIBBOT_H */

