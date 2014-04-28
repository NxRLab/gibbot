/* First iteration of code to go with the Gibbot v4 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "initialize.h"
int send;

int main(void) {
    //Set the calibration bits for phase lock loop
    //Clock frequency is set at 80MHz
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    PLLFBDbits.PLLDIV = 42;  // M = 44
    CLKDIVbits.PLLPOST = 0;  // N2 = 2
    initialize();
    BOTMAG = 0;
    while (1){
        if(USER){
            BOTMAG = 1;
            LED4 = 0;
            long i;
            for(i = 0; i < 100000; i++);
        }
    }
    return 0;
}

