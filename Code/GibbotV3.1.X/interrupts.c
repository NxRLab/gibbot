#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"

int lastADC = 0; //variable to store last ADC result
int index1 = 0;
int index2 = 0;
char bufferfull = 0;
int motoron = 0;
int qei1;
int qei2;

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    static char state = 0;
    if (IFS1bits.CNIF) {
        state = (!S3 << 2) | (!S2 << 1) | !S1;
        if(motoron == 1){
            commutate(state);

            LED1 = !S1;
            LED2 = !S2;
            LED3 = !S3;
        }
        LED4 = !LED4;
        // clear mismatch condition
        PORTD;
    }
    IFS1bits.CNIF = 0; //Clear int flag
    return;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    while (U1STAbits.URXDA){ // If there is data in the recieve register
        char echo = U1RXREG;
        U1TXREG = echo;
    }
	IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    static int i;
    if(i == 500){
    printf("%d\r", POS2CNTL);
    i=0;
    } else {
        i++;
    }
    IFS0bits.T1IF = 0;
}
