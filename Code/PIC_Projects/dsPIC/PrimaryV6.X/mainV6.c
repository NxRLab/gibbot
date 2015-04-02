/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#define FCY 40000000UL
#include <libpic30.h>

#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"

extern volatile char last_state;

int main(void) {
    initialize();
    initialize_ADC_Offset();
    printf("hello world!\n");

    last_state = -1;
    motoron = 0;

    do {
        if(!motoron) {
            __delay_ms(1000);
            printf("ready when you are...press USER button\n");
            while (!USER);
            printf("running\n");
            __delay_ms(1000);

            motoron = 1;
            write_duty(60);
            kick();
        }
    } while (1);

    while(1);

    while (1){
        /*
        if(USER){
            LED1 = !LED1;
            LED2 = !LED2;
            LED3 = !LED3;
            LED4 = !LED4;
            //TOPMAG = !TOPMAG;
            //commutate(7);
        }
        */

       //test_MayDay();
    }

    return 0;
}
