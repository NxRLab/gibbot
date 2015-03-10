/*
*File: current_control.h
*Author: Vince Martinez
*V1.1
*/

#ifndef CURRENT_CONTROL_H_
#define CURRENT_CONTROL_H_

void initialize_CurrentControl(void); //Initialize dsPIC bits (timer and PWM)
//short current_amps_get(); //Detect current
void current_pwm_set(int duty_percent); //Converts a duty cycle percentage (0-100) to a PWM value
void calc_effort(int desired, short sensed, int kp, int ki); // Calculates error signal (PWM) from the sensed and desired current
void current_gains_sprintf(char * buffer);
void current_gains_sscanf(const char * buffer);

#endif