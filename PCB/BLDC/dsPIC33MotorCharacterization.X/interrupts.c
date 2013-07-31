#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    int store;
    store = POS1CNT;
    while (!U1STAbits.RIDLE){ // If there is data in the recieve register
        char echo = U1RXREG;
        if(echo == 'a'){
            duty(372);
            direction = 0;
        }
        if(echo == 's'){
            duty(186);
            kick();
            direction = 0;
            turncount = 120;
        }
        if(echo == 'd'){
            duty(0);
            direction = 1;
        }
        if(echo == 'f'){
            duty(186);
            kick();
            direction = 1;
            turncount = 120;
        }
        if(echo == 'g'){
            duty(372);
            direction = 1;
        }

        while(U1STAbits.UTXBF){//wait for buffer to not be full
            U1TXREG = 0x00;
        }
        U1TXREG = echo;
    }
	IFS0bits.U1RXIF = 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
	IFS0bits.U1TXIF = 0; //We don't care about a transmit interrupt
}

void __attribute__ ((interrupt, no_auto_psv)) _QEIInterrupt(void) {
	IFS3bits.QEIIF = 0; //We don't care about a transmit interrupt
}


void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void) {
    LATAbits.LATA2 = !LATAbits.LATA2;
    char state = 0;
    static char laststate;
    // Is this a CN interrupt?
    if (IFS1bits.CNIF) {
        if(turncount > 0){
            state = (!S3 << 2) | (!S2 << 1) | !S1;
            commutate(state);
            if(laststate != state){
                turncount = turncount -1;
            }
            laststate = state;
        } else{
            commutate(0);
        }
        // clear mismatch condition
        PORTA;
        PORTB;
        IFS1bits.CNIF = 0;      //Clear int flag
    }
    return;
}
