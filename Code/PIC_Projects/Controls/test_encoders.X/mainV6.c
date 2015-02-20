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

#define TOPMAG_ON (TOPMAG = 1)
#define BOTMAG_ON (write_UART2('1'))

#define TOPMAG_OFF (TOPMAG = 0)
#define BOTMAG_OFF (write_UART2('2'))

int main(void) {
    //initialize all peripherals, encoder values
    initialize();

    TOPMAG_OFF;
    BOTMAG_OFF;

    printf("hello world!\n");
    while (1) {
        if (USER){
            TOPMAG_ON;
            BOTMAG_ON;
            timer1_on();    //encoder reading is in ISR in time.c
        }
       
        //press reset to end code
    }
    return 0;
}
