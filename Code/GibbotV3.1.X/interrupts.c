#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "peripherals.h"

int motoron = 0;
int senddata = 0;
int lowmagon = 0;

struct {
    unsigned short topmagenc, motorenc, lowmagenc;
    char state;
} data;

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
        char data = U1RXREG;
        if (data == 'o'){
            senddata = 1;
        } else if (data == 'p'){
            senddata = 1;
        } else if (data == 'w'){
            lowmagon = 1;
        } else if (data == 'q'){
            lowmagon = 0;
        }
    }
	IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    
    if (senddata == 1){    //was turncount?
        data.topmagenc = POS1CNTL;
        data.motorenc = MOTCNT;
        data.lowmagenc = LOWMAGCNT;

        printf("%5d,%5d,%6d", data.topmagenc, data.motorenc, data.lowmagenc);
//        data.state = 1; //7;
        //printf("%d \n",data.encoder);

//        char *s = (char *) &data;
//        int j;
//        for (j = 0; j < 7; j++) {
//            while (U1STAbits.UTXBF); // wait until tx buffer isn't full
//            if(s[j] == 0){
//                U1TXREG = 0x01;
//            } else{
//            U1TXREG = s[j];
//            }
//        }
        senddata = 0;
    }
    if(USER){
        if(lowmagon){
            I2C_Write(READ_MOTOR | READ_LOWMAG | MAGNET_ON);
        } else {
            I2C_Write(READ_MOTOR | READ_LOWMAG);
        }
    } else {
        if(lowmagon){
            I2C_Read(READ_MOTOR | READ_LOWMAG | MAGNET_ON);
        } else {
            I2C_Read(READ_MOTOR | READ_LOWMAG);
        }
    }
    IFS0bits.T1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _MI2C2Interrupt(void) {
    int switchexit = 0;
    while(switchexit < 1){
        switch(I2C_CONTROL.state){
            case 0:
                //Change Transmission state to signify sending start event
                I2C_CONTROL.state= 1;
                //Initiate start event
                I2C2CONbits.SEN = 1;
                switchexit = 1;
                break;
            case 1:
                //If start has completed
                if(I2C2STATbits.S && !I2C2CONbits.SEN){
                    //If transmission buffer is not already full
                    if(!I2C2STATbits.TBF){
                        //Change State depending on reading or writing status;
                        I2C_CONTROL.state = 2 + I2C_CONTROL.cmd;
                        //Transmit slave address + R/W bit
                        I2C2TRN = ((I2C_CONTROL.slaveaddr)<<1) | I2C_CONTROL.cmd;
                        switchexit = 1;
                        error = 0;
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
                break;
            case 2: //Writing data
                //If address not acknowledged try again
                if(0){//if(I2C2STATbits.ACKSTAT){
                    //If more than three attempts exit with an error
                    if(I2C_CONTROL.repeatcount >= 3){
                        I2C_CONTROL.state = 0;
                        error = 1;
                        LED3 = 1;
                        switchexit = 1;
                    }
                    //Try sending address again
                    I2C_CONTROL.repeatcount++;
                    I2C_CONTROL.state = 1;
                    //If address was acknowledged send data
                } else {
                    I2C_CONTROL.repeatcount = 0;
                    //If no data remaining in a write operation, move to stop condition
                    if(I2C_CONTROL.numbytes == 0){
                        //Move to stop condition
                        I2C_CONTROL.state = 4;
                        switchexit = 1;
                        //If transmission buffer is not already full
                    } else if(!I2C2STATbits.TBF){
                        //Transmit last data byte
                        I2C_CONTROL.numbytes--;
                        I2C2TRN = I2C_CONTROL.trndata[I2C_CONTROL.numbytes];
                        LED3 = 0;
                        error = 0;
                        //repeat until no data remaining
                    } else {
                        //Generate an error and repeat
                        LED3 = 1;
                        error = 1;
                    }
                }
                break;
            case 3: //Reading Data
                //If address not acknowledged try again
                if(I2C2STATbits.ACKSTAT && !I2C2STATbits.D_A){
                    //If more than three attempts exit with an error
                    if(I2C_CONTROL.repeatcount >= 3){
                        I2C_CONTROL.state = 0;
                        LED3 = 1;
                        error = 1;
                        switchexit = 1;
                    }
                    //Try sending address again
                    I2C_CONTROL.repeatcount++;
                    I2C_CONTROL.state = 1;
                    //If address was acknowledged send data
                } else {
                    I2C_CONTROL.state = 6;
                    switchexit = 1;
                    I2C2CONbits.RCEN = 1;
                    break;
                }
            case 4:
                //If data was not acknowledged exit with an error
                if(0){//if(I2C2STATbits.ACKSTAT){
                    I2C_CONTROL.state = 0;
                    LED3 = 1;
                    error = 1;
                    break;
                }
                //Stop Condition
                //Change Transmission state to signify end of message
                I2C_CONTROL.state= 5;
                //Initiate stop event
                I2C2CONbits.PEN = 1;
                switchexit = 1;
                break;
            case 5:
                //Message sent clear variables
                I2C_CONTROL.cmd = I2C_IDLE;
                I2C_CONTROL.repeatcount = 0;
                I2C_CONTROL.state= 0;
                switchexit = 1;
                break;
            //Reading data
            case 6:
                //If the data recive buffer is full read data
                if(I2C2STATbits.RBF){
                    //Store recieved data in recieve buffer
                    I2C_CONTROL.numbytes--;
                    I2C_CONTROL.rcvdata[I2C_CONTROL.numbytes] = I2C2RCV;
                    I2C2CONbits.ACKDT = 0;
                    I2C_CONTROL.state = 3;
                    if(I2C_CONTROL.numbytes==0){
                        if((I2C_CONTROL.slaveaddr & 0b0000011) == 3){
                            MOTCNT = (I2C_CONTROL.rcvdata[5]<<8) + I2C_CONTROL.rcvdata[4];
                            LOWMAGCNT = (I2C_CONTROL.rcvdata[3]<<8) + (I2C_CONTROL.rcvdata[2]);
                            LOWMAGCNT = (LOWMAGCNT<<16) + (I2C_CONTROL.rcvdata[1]<<8)
                                + I2C_CONTROL.rcvdata[0];
                        } else if(I2C_CONTROL.slaveaddr & 0b0000010){
                            MOTCNT = (I2C_CONTROL.rcvdata[1]<<8) + I2C_CONTROL.rcvdata[0];
                        } else if(I2C_CONTROL.slaveaddr & 0b0000001){
                            LOWMAGCNT = (I2C_CONTROL.rcvdata[3]<<8) + (I2C_CONTROL.rcvdata[2]);
                            LOWMAGCNT = (LOWMAGCNT<<16) + (I2C_CONTROL.rcvdata[1]<<8) + I2C_CONTROL.rcvdata[0];
                        }
                        I2C_CONTROL.state = 7;
                        //Send Nack to indicate all data has been recieved
                        I2C2CONbits.ACKDT = 1;
                    }
                    switchexit = 1;
                    //Acknowledge data
                    I2C2CONbits.ACKEN = 1;
                    break;
                //Otherwise no data was sent, set error and exit
                } else {
                    switchexit = 1;
                    I2C_CONTROL.state = 0;
                    LED3 = 1;
                    error = 1;
                    break;
                }
            case 7:
                //Stop Condition
                //Change Transmission state to signify end of message
                I2C_CONTROL.state= 8;
                //Initiate stop event
                I2C2CONbits.PEN = 1;
                switchexit = 1;
                break;
            case 8:
                //Message sent clear variables
                I2C_CONTROL.cmd = I2C_IDLE;
                I2C_CONTROL.repeatcount = 0;
                I2C_CONTROL.state= 0;
                switchexit = 1;
                break;
        }
    }
    IFS3bits.MI2C2IF = 0;
}