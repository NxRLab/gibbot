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

struct {
    char start, length;
    short motenc, topmagenc, lowmagenc, current;
    char state, end;
} data;


void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    char state = 0;
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
    //ON FTDI CABLE ORANGE WIRE SHOULD GO TO RX ON PIC.
    while (U1STAbits.URXDA){ // If there is data in the recieve register
        char echo = U1RXREG;
        U1TXREG = echo;
    }
	IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
//    if (index2 > 0){
//
//        data.start = 0x30;
//        data.length = 0x31;
//        data.motenc = 0x3332; //POS1CNTL;
//        data.topmagenc = 0x3534;//POS2CNTL;
//        data.lowmagenc = 0x3736;//0;
//        data.current = 0x3938;//Read_ADC();
//        data.state = 0x41;
//        data.end = 0x42;
//
//        char *s = (char *) &data;
//        int j;
//        static int i = 0;
//        for (j = 0; j < 10; j++) {
//            while (U1STAbits.UTXBF); // wait until tx buffer isn't full
//            U1TXREG = s[i];
//            i++;
//            if (i == 12){
//                i =0;
//            }
//        }
//
//    }
    IFS0bits.T1IF = 0;
}
