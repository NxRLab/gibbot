#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

int lastADC = 0; //variable to store last ADC result
int index1 = 0;
int index2 = 0;
char bufferfull = 0;

struct {
    short encoder, i1, i2, i3;
    char state;
} data;

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    while (U1STAbits.URXDA) { // If there is data in the recieve register
        char echo = U1RXREG;
        if (echo == 'a') { //half on direction 1
            //duty(395); //186
            //kick();
           // direction = 1;
            index2=1;
            //turncount = 126;
        }
        if (echo == 'j') { //fully on direction 1
            duty(372);
            kick();
            direction = 1;
            turncount = 126;
        }
        if (echo == 'k') { //half on direction 0
            duty(186);
            kick();
            direction = 0;
            turncount = 126;
        }
        if (echo == 'f') { //fully on direction 0
            duty(372);
            kick();
            direction = 0;
            turncount = 12;
        }

        if (echo == 'g') {
            duty(372);
            direction = 1;
        }
        if (echo == 'd') {
            duty(0);
            direction = 1;
        }
        if (echo == 'q') {
            commutate(0);
            index2=0;
        }
        while (U1STAbits.UTXBF) {//wait for buffer to not be full
            U1TXREG = 0x00;
        }
       // U1TXREG = echo;
      //  LATAbits.LATA2 = 1;
     //   printf("123 1234 123 123 123 1");
     //   LATAbits.LATA2 = 0;
    }
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    LATAbits.LATA2 = 1;
    TMR3 = 0;
    T3CONbits.TON = 1;

    T3CONbits.TON = 0;
    LATAbits.LATA2 = 0;
    if (index2 > 0){    //was turncount
        Read_ADC();
        data.i1 = ADResultAN3_2/2;
        data.i2 = ADResultAN4/2;
        data.i3 = ADResultAN5/2;
        
        printf("%3d %3d %3d \n",data.i1,data.i2,data.i3);
        
    }
        IFS0bits.T1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
//
//    if (1) {//bufferful
//        if (1) {
//            LATAbits.LATA2 = 1;
//            printf("%d", index2);
//            index2++;
//            LATAbits.LATA2 = 0;
//
//        } else {
//            bufferfull = 0;
//            index1 = 0;
//            index2 = 0;
//        }
//    }
    IFS0bits.T2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _QEIInterrupt(void) {
    IFS3bits.QEIIF = 0; //We don't care about a transmit interrupt
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0; //We don't care about a transmit interrupt
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    char state = 0;
    static char laststate;
    // Is this a CN interrupt?
    if (IFS1bits.CNIF) {
        if (turncount > 0) {
            state = (!S3 << 2) | (!S2 << 1) | !S1;
            commutate(state);
            if (laststate != state) {
                turncount = turncount - 1;
            }
            laststate = state;
        } else {
            commutate(0);
        }
        // clear mismatch condition
        PORTA;
        PORTB;
        IFS1bits.CNIF = 0; //Clear int flag
    }
    return;
}
