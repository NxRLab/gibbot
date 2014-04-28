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
            duty(791); //186
            kick();
            direction = 1;
            index2=1;
            turncount = 12600;
        }
        if (echo == 's') { //half on direction 1
            duty(791); //186
            kick();
            direction = 0;
            index2=1;
            turncount = 12600;
        }
        if (echo == 'd') { //half on direction 1
            index2=1;
        }
        if (echo == 'f') { //half on direction 1
            duty(791); //186
            kick();
            direction = 0;
            index2=1;
            turncount = 12600;
        }
        if (echo == 'q') {
            turncount = 0;
            commutate(0);
            index1 = 0;
            index2=0;
        }
        while (U1STAbits.UTXBF);//wait for buffer to not be full
    }
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    if (index2 > 0){    //was turncount?
        Read_ADC();
        data.i1 = ADResultAN3;
        data.i2 = ADResultAN4;
        data.i3 = ADResultAN5;
        data.encoder = POS1CNT+1700;    //add 1700 to prevent from being negative
        data.state = 1;
        //printf("%d \n",data.encoder);

        char *s=(char *)&data;
        int j;
        for (j=0;j<10;j++)
        {
        _mon_putc(s[j]);
        }
        
        //printf("\r");
    }
    if (index1 != 0){
        printf("Test \n");
    }
        IFS0bits.T1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _QEIInterrupt(void) {
    IFS3bits.QEIIF = 0; //We don't care about a qei interrupt
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
