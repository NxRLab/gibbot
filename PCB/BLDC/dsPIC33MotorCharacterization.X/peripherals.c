#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

void init_pwm(void){
    P1DC1 = 186; //Set initial duty cycle as 50% on pin 1
    P1DC2 = 186; //Set initial duty cycle as 50% on pin 2
    P1DC3 = 186; //Set initial duty cycle as 50% on pin 2
    P1TPER = 186;//Set PWM freq as 20kHz

    IEC3bits.PWM1IE = 1;

    P1DTCON1bits.DTAPS = 0b00; //Set deadtime prescaler as 8:1
    P1DTCON1bits.DTA = 2;

    P1DTCON2bits.DTS1A = 0; //Deadtime before PWM1H1 is active
    P1DTCON2bits.DTS1I = 0; //Deadtime before PWM1L1 is active
    P1DTCON2bits.DTS2A = 0; //Deadtime before PWM1H2 is active
    P1DTCON2bits.DTS2I = 0; //Deadtime before PWM1L2 is active
    P1DTCON2bits.DTS3A = 0; //Deadtime before PWM1H2 is active
    P1DTCON2bits.DTS3I = 0; //Deadtime before PWM1L2 is active

    PWM1CON1bits.PEN1H = 1;
    PWM1CON1bits.PEN1L = 1;
    PWM1CON1bits.PEN2H = 1;
    PWM1CON1bits.PEN2L = 1;
    PWM1CON1bits.PEN3H = 1;
    PWM1CON1bits.PEN3L = 1;
    P1TCONbits.PTEN = 1;
}

void init_uart (void){
    //Setup Peripheral Pin Select
    //RP5->RX  RP6->TX
    RPINR18bits.U1RXR = 5; //UART1 RX Tied to RP5  datasheet p122
    RPOR3bits.RP6R = 3;    //RP6 tied to UART1 TX datasheet p123
    //Setup UART

    /* For Baud Rate of 9600 */
    //U1MODEbits.BRGH = 0; // Turn off High Baud Rate Mode
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (3.685MHz/(16*9600)) - 1
    // U1BRG = 23

    /* For Baud Rate of 38400 */
    U1MODEbits.BRGH = 0; //High Baud Rate Mode
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (3.685MHz/(4*38400)) - 1
    // U1BRG = 25

    U1BRG = 23; //Baud rate ~38400
    U1MODEbits.PDSEL = 0; //8 bits no parity
    U1MODEbits.STSEL = 0; //1 stop selection bit
    IPC3bits.U1TXIP = 5;
    IPC2bits.U1RXIP = 5;

    IFS0bits.U1TXIF = 0;	// Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 1;	// Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;	// Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1; //enable the UART
    U1STAbits.UTXEN = 1;
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

void init_qei(void){
    //Turn on QEI
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB4 = 1;
    RPINR14bits.QEA1R = 0; //QEI A
    RPINR14bits.QEB1R = 4; //QEI B
    IEC3bits.QEIIE = 1;
    IPC14bits.QEIIP = 7;
    QEI1CONbits.QEIM = 0b101; //QEI x2 with reset at MAXxCNT
    MAX1CNT = 0xFFFF; //Set Reset value to maximum


}
