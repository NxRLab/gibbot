/* 
 * File:   motor.h
 * Author: ajgriesemer
 *
 * Created on April 10, 2014, 4:15 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

void High(int pin);
void Low(int pin);
void Float(int pin);
void initialize_PWM(void);
void initialize_CN(void);
void commutate(int state);
void kick(void);

extern char motoron;
extern char state;
extern int direction;

#define CW 0
#define CCW 1

//Rotary encoder outputs from the BLDC motor
#define S3 PORTDbits.RD5
#define S2 PORTDbits.RD4
#define S1 PORTDbits.RD3

#endif	/* MOTOR_H */

