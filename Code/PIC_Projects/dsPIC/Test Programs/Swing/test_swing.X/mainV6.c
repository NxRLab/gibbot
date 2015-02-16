/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include <stdio.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "time.h"
#include "UART.h"
#include "encoder.h"

int main(void) {
    //initialize all peripherals, encoder values
    initialize();
    initialize_ADC_Offset();
    initialize_QEI();
    initialize_UART();

    unsigned char c='o';
    motoron = 1;
    direction = CW;
    //write_duty(300);
    //timer1_on();

    while (1) {
        c = read_UART();

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
        } else if(c =='h') {
             //Turn off Bottom Magnet
            write_UART2('2');
        }
        else if (c=='u'){
            // inc duty
            // for now, increase the duty by 10% of max duty
            write_duty(read_duty()+100);
            c = 'x';
        }
        else if (c=='d'){
            // dec duty
            write_duty(read_duty()+100);
            c = 'x';
        }
        else if (c=='m'){
            // motor off
            motoron = 0;
        }
        else if (c=='x'){
            // make sure duty is only updated once per call
            continue;
        }

        //command to swing robot
        else if (c=='l'){
            //swing left
            TOPMAG=0;
            //delay function in progress
            //delay(0.1);
            write_duty(200);
            //delay(0.1);
            write_duty(0);
            //delay(0.1);
            TOPMAG=1;
        }
    }
    return 0;
}
