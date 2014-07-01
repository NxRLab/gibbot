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
    motoron=1;
    while (1){
        LED1 = !S3;
        LED2 = !S2;
        LED3 = !S1;
        test_MayDay();
    }
    return 0;
}
