/* 
 * File:   swing_control.h
 * Author: harntson
 *
 * Created on March 2, 2015, 12:47 AM
 */

#ifndef SWING_CONTROL_H
#define	SWING_CONTROL_H

#define N_MAX 170   //maximum number of states
#define MESSAGE_MAX 50

//Arguments to pass to robot, define as struct args[n], with n being
//the number of distinct states
struct args {
    int torque;
    int t_swing;    //milliseconds
    int t_flight;   //milliseconds
};

void write_swing(int n, struct args* control_args);
void read_swing(char state, int n, struct args* control_args);
void get_input(struct args* control_args, char c, char state, int n, char* buf);

#endif	/* SWING_CONTROL_H */

