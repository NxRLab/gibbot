#include "changenotification.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>

#define S3 PORTBbits.RB7
#define S2 PORTBbits.RB8
#define S1 PORTBbits.RB9

void _ISR _CNInterrupt(void) {
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

void init_cn(void){
    //Change Notification
    // Turn change notification on
    CNEN2bits.CN21IE = 1;
    CNEN2bits.CN22IE = 1;
    CNEN2bits.CN23IE = 1;
    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 0b111;  //Set priority to 7
    IEC1bits.CNIE = 1;      //Enable interrupts
}