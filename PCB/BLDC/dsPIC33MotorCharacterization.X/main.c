#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

/* Configuration Bit Settings */
//_FBS(BWRP_WRPROTECT_OFF) //Boot segment is not write protected (for debugging)
//_FGS(GWRP_OFF & GSS_OFF) //general segment is not write protected (for debugging)
_FOSCSEL(FNOSC_FRC) //Use internal FRC Oscillator at 7.37 MHz no PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
//Clock switching is enabled, Fail-Safe Clock Monitor is disabled
//OSC2 pin has digital I/O function
_FWDT(FWDTEN_OFF)
//Watchdog timer enabled/disabled by user software
_FPOR(FPWRT_PWR128 & LPOL_ON & HPOL_OFF)
//Power on Reset Timer is enabled for 128ms to allow system power to stablize
//PWM module low side output pins have active-high output polarity
//PWM module high side output pins have active-low output polarity
_FICD(ICS_PGD2 & JTAGEN_OFF)
//Communicate on PGC1/EMUC1 and PGD1/EMUD1
//JTAG is Disabled

char store;
char array[100];
char direction = 1;
int turncount = 0;

int main(void){
    init_pwm();
    ADC_Init();
    init_cn();
    init_uart();
 //   init_qei();
    commutate(0);
    while(1){
    }
    return 0;
}

void _mon_putc(char c) {
    // echo data
       while (U1STAbits.UTXBF); // wait until tx buffer isn't full
       U1TXREG = c;
  //  PutCharacter(UART1, c);
}