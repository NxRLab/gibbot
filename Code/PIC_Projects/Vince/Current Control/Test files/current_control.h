/*
*File: current_control.h
*Author: Vince Martinez
*V1.1
*/

#ifndef CURRENT_CONTROL_H_
#define CURRENT_CONTROL_H_


int current_amps_get(void); //Detect current
void calc_effort(int desired, short sensed, int kp, int ki); // Calculates effort signal (PWM) from the sensed and desired current
void track_wave(int reference);
void controltune(int i);
void test_output(void);

#endif