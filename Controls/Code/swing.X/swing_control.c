#include <libpic30.h>
#include <p33EP512MC806.h>
#include "time.h"
#include "stdio.h"
#include "ControlLib.h"

#include "swing_control.h"

/* File: swing_control.c
   Author: Hannah Arntson

   Send control parameters to PIC and swing the robot */


/* Function: write_swing
   Writes an array of control parameters to the PIC
   args[n] = {{torque, t_swing, t_flight}...}  */

void write_swing(){
    //Note: this function will be condensed after testing
    //get input from user and send to the PIC
    int torque, t_swing, t_flight;
    printf("Input n: ");
    scanf("%d",&n);

    unsigned char torque_buf[4], swing_buf[4], flight_buf[4];
    //struct args control_args[n];

    for (int i=0; i<n; i++){
        //Torque
        printf("Torque: \n");
        read_string_UART(torque_buf,4);
        sscanf(torque_buf, '%i', &torque);
        control_args[i].torque = torque;
        //Time swinging
        printf("Time to swing: \n");
        read_string_UART(swing_buf,4);
        scanf(swing_buf, '%i', &t_swing);
        control_args[i].t_swing = t_swing;
        //Time in flight
        printf("Time to fly: \n");
        read_string_UART(flight_buf,4);
        scanf(flight_buf, '%i',&t_flight);
        control_args[i].t_flight = t_flight;
    }
}


/* Function: read_swing
   Reads back the control parameters loaded onto the PIC */

void read_swing(char state){
    //read args from PIC and print to screen
    if (state='n'){
        //print entire struct array
        for (int i=0; i<n; i++){
            printf("%i %i %i /n",control_args[i].torque, control_args[i].t_swing, control_args[i].t_flight);
        }
    }
    else{
        //print specified state parameters
        printf("%i %i %i /n",control_args[(int)state].torque, control_args[(int)state].t_swing, control_args[(int)state].t_flight);
    }
}


