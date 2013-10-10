#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "interrupts.h"

int lastADC = 0; //variable to store last ADC result
int index1 = 0;
int index2 = 0;
char bufferfull = 0;
int motoron = 0;
int qei1;
int qei2;
int transmit;

struct I2C_CONTROL_t I2C_CONTROL; 

//Interrupt vector names are in Table 7-4 p101 of the MPLAB C30 User's Guide
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

void __attribute__((interrupt, no_auto_psv)) _MI2C2Interrupt(void) {
    /* As laid out in the dsPIC33EP512MC806 User Manual Section 19
     * Table 19-2 the states of the I2C transmission progress as follows
     * Modified for no repeat start event
     * ________________________________________________
     * State Number | I2C2CON<4:0> | TRSTAT | State
     *       0      |    00000     |   0    | Bus Idle
     *       1      |    00001     |  N/A   | Sending Start Event
     *       2      |    00000     |   1    | Master Transmitting
     *       3      |    00100     |  N/A   | Sending Stop Event
     *       4      |    01000     |  N/A   | Master Reception
     *       5      |    10000     |  N/A   | Master Acknowledgement
     * 
     */
    static int I2C_state = 0;
    if(transmit==1){
        switch(I2C_state){
            case 0:
                //If a read or write sequence has been initiated
                if (I2C_CONTROL.cmd == I2C_WRITE || I2C_CONTROL.cmd ==I2C_READ)
                //Change Transmission state to signify sending start event
                I2C_CONTROL.state= 1;
                //Initiate start event
                I2C2CONbits.SEN = 1;
                break;
            case 1:
                //If start has completed
                if(I2C2STATbits.S && !I2C2CONbits.SEN){
                    //If transmission buffer is not already full
                    if(!I2C2STATbits.TBF){
                        //Change Transmission state to signify transmission
                        I2C_CONTROL.state = 2;
                        //Transmit slave address + R/W bit
                        I2C2TRN = ((I2C_CONTROL.slaveaddr)<<1) | I2C_CONTROL.cmd;
                        error = 0;
                        break;
                    } else {
                        //Generate an error and repeat
                        error = 1;
                    }

                } else{
                    //If start event has not completed return to
                    //start condition and generate an error
                    I2C_CONTROL.state = 0;
                    error = 1;
                }
            case 2:
                //If address not acknowledged try again
                if(I2C2STATbits.ACKSTAT){
                    //If more than three attempts exit with an error
                    if(I2C_CONTROL.repeatcount >= 3){
                        I2C_CONTROL.state = 0;
                        error = 1;
                        break;
                    }
                    //Try sending address again
                    I2C_CONTROL.repeatcount++;
                    I2C_CONTROL.state = 1;
                    //If address was acknowledged send data
                } else {
                    I2C_CONTROL.repeatcount = 0;
                    //If no data remaining
                    if(I2C_CONTROL.numbytes == 0){
                        I2C_CONTROL.state = 3;
                        break;
                    }
                    //If transmission buffer is not already full
                    if(!I2C2STATbits.TBF){
                        //Transmit slave last data byte
                        I2C2TRN = I2C_CONTROL.data[I2C_CONTROL.numbytes];
                        I2C_CONTROL.numbytes--;
                        error = 0;
                        //repeat until no data remaining
                    } else {
                        //Generate an error and repeat
                        error = 1;
                    }

                }

                



        }

    }
    IFS3bits.MI2C2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {

    IFS3bits.SI2C2IF = 0;
}

