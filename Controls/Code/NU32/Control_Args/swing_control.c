#include "NU32.h"

#include "swing_control.h"

/* File: swing_control.c
   Author: Hannah Arntson

   Send control parameters to PIC and swing the robot */

/* Function: write_swing
   Writes an array of control parameters to the PIC
   args[n] = {{torque, t_swing, t_flight}...}  */

void write_swing(int n, struct args* control_args){
    //Note: this function will be condensed after testing
    //get input from user and send to the PIC
    int torque, t_swing, t_flight;

    char torque_buf[10], swing_buf[10], fly_buf[10];
    char message[MESSAGE_MAX];
    //struct args control_args[n];

    int i;
    for (i=0; i<n; i++){
        sprintf(message, "Enter data for set %d\r\n", i+1);
        NU32_WriteUART1(message);

        //Torque
        NU32_WriteUART1("Torque: ");
        NU32_ReadUART1(torque_buf, 10);
        sscanf(torque_buf, "%d", &torque);
        sprintf(message, "%d \r\n", torque);
        NU32_WriteUART1(message);
        control_args[i].torque = torque;   

        //Time swinging
        NU32_WriteUART1("Time to swing: ");
        NU32_ReadUART1(swing_buf, 10);
        sscanf(swing_buf, "%d", &t_swing);
        sprintf(message, "%d \r\n", t_swing);
        NU32_WriteUART1(message);
        control_args[i].t_swing = t_swing;
        
        //Time in flight
        NU32_WriteUART1("Time to fly: ");
        NU32_ReadUART1(fly_buf,10);
        sscanf(fly_buf, "%d", &t_flight);
        sprintf(message, "%d \r\n\n", t_flight);
        NU32_WriteUART1(message);
        control_args[i].t_flight = t_flight;
    }
    return 0;
}


/* Function: read_swing
   Reads back the control parameters loaded onto the PIC */

void read_swing(int n, struct args* control_args){
    char message[MESSAGE_MAX];
    int i;

    sprintf(message, "       Torque  Swing(ms)  Fly(ms)\r\n");
    NU32_WriteUART1(message);

    //print entire struct array
    for (i=0; i<n; i++){
        sprintf(message, "Set %d: %6d %9d %8d \r\n",i+1,control_args[i].torque,control_args[i].t_swing,control_args[i].t_flight);
        NU32_WriteUART1(message);
    }
    NU32_WriteUART1("\r\n");
}



