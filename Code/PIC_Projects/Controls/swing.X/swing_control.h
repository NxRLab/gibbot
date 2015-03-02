/* 
 * File:   swing_control.h
 * Author: harntson
 *
 * Created on March 2, 2015, 12:47 AM
 */

#ifndef SWING_CONTROL_H
#define	SWING_CONTROL_H

//Arguments to pass to robot, define as struct args[n], with n being
//the number of distinct states
struct args {
    int torque;
    int t_swing;    //miliseconds
    int t_flight;   //miliseconds
};

//global variables
int n;
struct args control_args[n];

void write_swing(void);
void read_swing(char state);

#endif	/* SWING_CONTROL_H */

