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
        printf(message);

        //Torque
        printf("Torque: ");
        read_string_UART(torque_buf, 10);
        sscanf(torque_buf, "%d", &torque);
        printf("%d \r\n", torque);
        //NU32_WriteUART1(message);
        control_args[i].torque = torque;

        //Time swinging
        printf("Time to swing: ");
        read_string_UART(swing_buf, 10);
        sscanf(swing_buf, "%d", &t_swing);
        printf("%d \r\n", t_swing);
        //NU32_WriteUART1(message);
        control_args[i].t_swing = t_swing;

        //Time in flight
        printf("Time to fly: ");
        read_string_UART(fly_buf,10);
        sscanf(fly_buf, "%d", &t_flight);
        printf("%d \r\n\n", t_flight);
        //NU32_WriteUART1(message);
        control_args[i].t_flight = t_flight;
    }
    return 0;
}


/* Function: read_swing
   Reads back the control parameters loaded onto the PIC */

void read_swing(int n, struct args* control_args){
    char message[MESSAGE_MAX];
    int i;

    printf(message, "       Torque  Swing(ms)  Fly(ms)\r\n");
    //NU32_WriteUART1(message);

    //print entire struct array
    for (i=0; i<n; i++){
        printf("Set %d: %6d %9d %8d \r\n",i+1,control_args[i].torque,control_args[i].t_swing,control_args[i].t_flight);
        //NU32_WriteUART1(message);
    }
    printf("\r\n");
}



