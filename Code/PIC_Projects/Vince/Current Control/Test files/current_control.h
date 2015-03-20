/*
*File: current_control.h
*Author: Vince Martinez
*V1.1
*/

#ifndef CURRENT_CONTROL_H_
#define CURRENT_CONTROL_H_


int current_amps_get(void); //Detect and output current from ADC
void calc_effort(int desired, short sensed, int kp, int ki); // Calculates effort signal "u" (PWM signal) from the sensed and desired current
void track_wave(int reference);
void control_tune(int i); //
void test_output(void);

#endif