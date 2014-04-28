#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "peripherals.h"
#include "interrupts.h"

int error = 0;

void Startup(void){
    //Set the calibration bits for phase lock loop
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    PLLFBDbits.PLLDIV = 42;  // M = 44
    CLKDIVbits.PLLPOST = 0;  // N2 = 2
    TRISBbits.TRISB2 = 1;    //USER input
    //LED outputs
    TRISDbits.TRISD11 = 0;   //LED1
    TRISDbits.TRISD0 = 0;    //LED2
    TRISCbits.TRISC13 = 0;   //LED3
    TRISCbits.TRISC14 = 0;   //LED4
    //Magnet Control
    TRISBbits.TRISB15 = 0;   //Low Magnet
    LOWMAG = 0;
    
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
}

void Initialize_QEI(void){
    //Turn on QEI
    RPINR14bits.QEA1R = 69; //Set RP69 (D5) as QEI1 A
    RPINR14bits.QEB1R = 68; //Set RP68 (D4) as QEI1 B
    RPINR16bits.QEA2R = 120; //Set RP120 (G8) as QEI2 A
    RPINR16bits.QEB2R = 119; //Set RP119 (G7) as QEI2 B
    ANSELBbits.ANSB0 = 0;   //Set B0 as a digital input
    ANSELBbits.ANSB1 = 0;   //Set B1 as a digital input
    POS1CNTL = 1800;
    POS2CNTL = 0;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1
    QEI2CONbits.QEIEN = 1; //Turn on QEI 2
}

void Initialize_I2C_Slave(void){
    //Fcy = 40 MHz
    //F SCL = 400kHz
    I2C2BRG = 95;
    //I2C module ignores the last three bits when recognizing it's slave address
    //allowing those bits to be used as command bits
    I2C2MSK = 0b0001111;
    //The slave address of the secondary board
    I2C2ADD = 0b1101000;

    IFS3bits.SI2C2IF = 0;      //Clear interrupt flag
    IPC12bits.SI2C2IP = 7;  //Set priority to 6
    IEC3bits.SI2C2IE = 1;      //Enable I2C 2 Slave interrupt

    I2C2CONbits.I2CEN = 1;

}

int sendandwait(char send){
    long int i = 0;
    I2C2TRN = send;
    I2C2CONbits.SCLREL = 1;
    while(I2C2STATbits.TBF && (i < 4000000)){
        i++;
    }
    if(i >= 4000000){
        LED3 = 0;
        I2C2CONbits.I2CEN = 0;
        I2C2CONbits.I2CEN = 1;
        return 1;
    } else {
        return 0;
    }
}

void AllOfTheLights(void){
    LED1 = 0;
    __delay32(8000000);
    LED1 = 1;
    LED2 = 0;
    __delay32(8000000);
    LED2 = 1;
    LED3 = 0;
    __delay32(8000000);
    LED3 = 1;
    LED4 = 0;
    __delay32(8000000);
    LED4 = 1;
    __delay32(2500000);
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    __delay32(10000000);
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
}