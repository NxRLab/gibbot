/* First iteration of code to go with the Gibbot v4 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "initialize.h"
#include "motor.h"
#include "test.h"

int main(void) {
    initialize();
        write_duty(500); //apply duty cycle change
        motoron = 1;//turn motor on
        kick();//kick start commutation
    //motoron=1;
    while (1){
        LED1 = !S3;
        LED2 = !S2;
        LED3 = !S1;
        //test_MayDay(); commented out for motor test
    }
    return 0;
}
