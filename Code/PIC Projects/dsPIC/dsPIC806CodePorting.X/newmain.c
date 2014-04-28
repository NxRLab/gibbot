#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>
#include "gibbot.h"


/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
//Use internal fast RC oscillator at 8 MHz
_FOSC(FCKSM_CSECMD & POSCMD_XT & OSCIOFNC_OFF)
//Clock switching is enabled, Fail-Safe Clock Monitor is disabled
_FWDT(FWDTEN_OFF)
//Watchdog timer enabled/disabled by user software
_FPOR(FPWRT_PWR128)
//Power on Reset Timer is enabled for 128ms to allow system power to stablize
_FICD(ICS_PGD1 & JTAGEN_OFF)
//Communicate on PGC1/EMUC1 and PGD1/EMUD1
//JTAG is Disabled

int main(void) {

//    //Fsys = Fin * M/ (N1 * N2)
//    //Fsys = 7.37 MHz * 44/ (2*2) = 80MHz
//    CLKDIVbits.PLLPRE = 0;   //N1 = 2
//    PLLFBDbits.PLLDIV = 42; //M = 44
//    CLKDIVbits.PLLPOST = 0;  //N2 = 2

    TRISBbits.TRISB15 = 0;

    while (1){
        LATBbits.LATB15 = !LATBbits.LATB15;
    }
    return 0;
}