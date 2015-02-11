/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "time.h"
#include "UART.h"

int main(void) {
    initialize();
    //initialize_ADC_Offset();
    //initialize_UART();
    TOPMAG=1;
    unsigned char c='o';
    motoron = 1;
    direction = CW;
    //write_duty(300);
    //timer1_on();
    while (1){
        //c = read_UART();
        if (c=='o'){
            TOPMAG=1;
        }
        else if (c=='f'){
            TOPMAG=0;
        }
        else if (c=='u'){
            //inc duty
        }
        else if (c=='d'){
            //dec duty
        }
        else if (c=='m'){
            //motor off
        }
    }
    return 0;
}
