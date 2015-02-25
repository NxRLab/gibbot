/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "ControlLib.lib"

int main(void) {
    initialize();
    //initialize_ADC_Offset();
    //initialize_UART();
    //TOPMAG=1;
    unsigned char c=0;
    motoron = 1;
    direction = CW;
    kick();
    write_duty(512);
    //write_duty(0);
    //timer1_on();

    printf("hello world!\n");
    while (1) {
        c = read_UART();
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
    }
    return 0;
}
