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
            duty(1);
        }
        if(echo == 's'){
            duty(163);
        }
        if(echo == 'd'){
            duty(245);
        }
        if(echo == 'f'){
            duty(372);
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

//void __attribute__ ((interrupt, no_auto_psv)) _PWMInterrupt(void) {
//    IFS3bits.PWM1IF = 0;
//}


void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void) {
    LATAbits.LATA2 = !LATAbits.LATA2;
    char state = 0;
    static char laststate;
    // Is this a CN interrupt?
    if (IFS1bits.CNIF) {
        if(turncount > 0){
            state = (!S3 << 2) | (!S2 << 1) | !S1;

            switch(state) {
                case 1:
                    state1();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
                case 2:
                    state2();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
                case 3:
                    state3();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
                case 4:
                    state4();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
                case 5:
                    state5();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
                case 6:
                    state6();
                    if(laststate != state){
                        turncount = turncount -1;
                    }
                    laststate = state;
                    break;
            }
            turncount = turncount -1;
        }
        // clear mismatch condition
        PORTA;
        PORTB;
        IFS1bits.CNIF = 0;      //Clear int flag
    }
    return;
}
