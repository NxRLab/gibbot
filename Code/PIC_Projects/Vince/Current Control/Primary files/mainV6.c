/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
//#include "core.h"
#include "menu.h"

int main(void) {
    
    initialize();
    unsigned char b = 'x';

    write_duty(0);
    motoron=0;
    direction = CW;

    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;

    printf("Hi! %s %s\n", __DATE__, __TIME__);


    while(1){


        if (USER){
            motoron=0;
            LED1=!LED1;
        }
        b = read_UART();    //read command from UART

        if (b=='1'){
            //Turn on motor
            //motoron=1;
            // write duty
            //write_duty(100);
            //kick();
            //int read = read_duty();
            //printf("Duty Cycle: %d, Motor status (1 = on, 0 = off):%d\r\n", read, motoron);
            printf("you pressed 1 wooooo. welcome to the motor options. choose an option.\r1 = test, 2 = idle, 3 = PWM, 4 = tuning");
            timer1_on();
            while(1);
        }

        else if (b=='x'){
          // make sure duty is only updated once per call
          //clear interrupt flag
            LED4=!LED4;
            continue;
          //IFS0bits.T1IF = 0;
}
    }
    







    /*initialize();
    write_string_UART("Hello world\r\n",100);
    __delay32(40000000);
    initialize_CurrentControl();
    while (1){
        if(USER){
            LED1 = !LED1;
            LED2 = !LED2;
            LED3 = !LED3;
            LED4 = !LED4;
            //TOPMAG = !TOPMAG;
            //commutate(7);
        }
       //test_MayDay();
    }
    return 0;
    */
}
