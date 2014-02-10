/* First iteration of code to go with the Gibbot v3 board. This code
 * will be developed to interface with a python controler on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>

#include "library.h"
/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRCPLL)
//Select the internal fast RC oscilator with phase lock loop or as the clock
_FOSC(OSCIOFNC_OFF)
//OSC2 (pin 40) is clock output
_FWDT(FWDTEN_OFF)
//Watchdog timer not automatically enabled
_FICD(ICS_PGD1)
//Communicate on PGEC1 (pin 17) and PGED1 (pin 18)
_FPOR(FPWRT_PWR128)
//Wait 128ms after power on to initialize

int motoron;

int main(void) {
    //Set the calibration bits for phase lock loop
    //Clock frequency is set at 80MHz
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    PLLFBDbits.PLLDIV = 42;  // M = 44
    CLKDIVbits.PLLPOST = 0;  // N2 = 2

    TRISBbits.TRISB2 = 1;    //USER input
    //LED outputs
    TRISDbits.TRISD11 = 0;   //LED1
    TRISDbits.TRISD0 = 0;    //LED2
    TRISCbits.TRISC13 = 0;   //LED3
    TRISCbits.TRISC14 = 0;   //LED4
    //Magnet Control
    TRISDbits.TRISD10 = 0;   //Top Magnet
    TOPMAG = 1;
    
    Initialize_CN();
    Initialize_PWM();
    commutate(0);
    U1TXREG = 12;
    Lights();
    motoron = 1;
    unsigned long long i = 0;
    while (1){
        TRISBbits.TRISB2 = 1;
//        if(i > 1000000){
//            if(direction){
//                direction = 0;
//            } else{
//                direction = 1;
//            }
//            i = 0;
//        } else {
//            i++;
//        }
        if(USER){
            motoron = 1;
            direction = 1;
        }
    }
    return 0;
}
