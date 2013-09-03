#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>


/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF)
_FOSC(OSCIOFNC_OFF)
//_FWDT(FWDTEN_OFF)
//_FPOR(FPWRT_PWR1 & BOREN_OFF & ALTI2C1_OFF)
//_FICD(ICS_PGD1 & JTAGEN_OFF)
//Communicate on PGC1/EMUC1 and PGD1/EMUD1
//JTAG is Disabled

int main(void) {

    //Fsys = Fin * M/ (N1 * N2)
    //Fsys = 7.37 MHz * 44/ (2*2) = 80MHz
    CLKDIVbits.PLLPRE = 0;   //N1 = 2
    PLLFBDbits.PLLDIV = 42; //M = 44
    CLKDIVbits.PLLPOST = 0;  //N2 = 2

    TRISBbits.TRISB15 = 0;

    while (1){
        LATBbits.LATB15 = !LATBbits.LATB15;
    }
    return 0;
}