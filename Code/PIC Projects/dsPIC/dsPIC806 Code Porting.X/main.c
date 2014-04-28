#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "peripherals.h"
#include "gibbot.h"
#include "motorcontrol.h"

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF)
_FOSC(OSCIOFNC_OFF)
_FWDT(FWDTEN_OFF)
_FICD(ICS_PGD1)
_FPOR(FPWRT_PWR128)

extern int motoron;
extern int direction; 
int main(void) {

    startup();
    initialize_cn();
    initialize_pwm();
    //initialize_uart();
    //initialize_qei();
    initialize_timer1();
    commutate(0);
    direction = 1;
    //initialize_adc();
    while (1){
        if(USER){
            motoron = 1;
            LOWMAG = 1;
        } else {
            motoron = 0;
            LOWMAG = 0;
            commutate(0);
        }

    }
    return 0;
}
