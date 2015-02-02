/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "time.h"

int main(void) {
    initialize();
    initialize_ADC_Offset();
    while (1){
        if(USER){
            motoron = 0;    //emergency stop if USER button pressed
            write_duty = 0;
        }
       
       //timer1_on();
       //timer2_on();

    }
    return 0;
}
