/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <libpic30.h>
#include <stdio.h>
#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "time.h"
#include "UART.h"
#include "encoder.h"

int main(void) {
    //initialize all peripherals
    initialize();

    unsigned char c='o';
    motoron=0;
    direction = CW;


    while (1) {
        //safety to shut off motor 
        if(USER){
            motoron=0;
        }

        //printf('Hi!');

        c = read_UART();    //read command from UART

        //commands to control specific components
        if (c=='o'){
            TOPMAG=1;
        }
        else if (c=='f'){
            TOPMAG=0;
        }

        else if(c == 'g') {
            //Turn on Bottom Magnet
            write_UART2('1');
        }

        else if(c =='h') {
             //Turn off Bottom Magnet
            write_UART2('2');
        }
        
        else if (c=='u'){
            //Turn on motor
            write_duty(200);
            motoron=1;
            kick();
            // inc duty
            //write_duty(read_duty()+100);
            c = 'x';
        }
        else if (c=='d'){
            // dec duty
            motoron=1;
            write_duty(read_duty()-100);
            c = 'x';
        }
        else if (c=='m'){
            // motor off
            motoron = 0;
        }

        //command to swing robot
        else if (c=='l'){
            //swing left
            TOPMAG=0;
            //delay function in progress
            __delay32(8000000);  //delay 8000000 cycles
            //delay(0.1);
            write_duty(200);
            //delay(0.1);
            write_duty(0);
            //delay(0.1);
            TOPMAG=1;
        }

        //test delay32
        else if (c == 'q'){
            LED1 = 1;
            __delay32(40000000);
            LED1 = 0;
            c = 'x';
        }

        else if (c=='x'){
            // make sure duty is only updated once per call
            continue;
        }
    }
    return 0;
}
