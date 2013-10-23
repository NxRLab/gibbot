/*
 * File:   motorcontrol.h
 * Author: ajgriesemer
 *
 * Created on September 3, 2013, 12:34 PM
 */

#ifndef MOTORCONTROL_H
#define	MOTORCONTROL_H

//Functions for driving the motor
void High(int pin);
void Low(int pin);
void Float(int pin);
void commutate(int state);
void kick(void);

//Variable that determines which direction the motor is spinning
// 1 is clockwise and 0 is counter-clockwise
extern int direction;

#endif	/* MOTORCONTROL_H */

