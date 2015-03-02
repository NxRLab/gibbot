/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "ControlLib.h"

int main(void) {
    initialize();
    
    //motoron = 1;
    //direction = CW;

    unsigned char c='0';
    unsigned char state='x';

    while (1) {
        //Give control arguments to PIC, check parameters and run swing
        printf('Press w to write, r to read, and x to swing\n');
        c = read_UART();
        if(c=='w'){
            write_swing();
        }
        else if(c=='r'){
            printf('Enter n to print everything, or specify state to check\n');
            state = read_UART();
            read_swing(state);
        }
        else if(c=='x'){
            //swing robot
        }

    }
}
