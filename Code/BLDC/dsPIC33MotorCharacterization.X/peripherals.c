#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

//int ADResultAN3_1;  //variables to store ADC results
int ADResultAN3;
int ADResultAN4;
int ADResultAN5;

void init_pwm(void){
    P1DC1 = 396; //Set initial duty cycle as 50% on pin 1
    P1DC2 = 396; //Set initial duty cycle as 50% on pin 2
    P1DC3 = 396; //Set initial duty cycle as 50% on pin 2
    P1TPER = 396;//Set PWM freq as 20kHz 186
    P1TCONbits.PTCKPS = 1; //1:4 prescaler
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
    //Setup Peripheral Pin Select, RP5->RX,  RP6->TX
    RPINR18bits.U1RXR = 5; //UART1 RX Tied to RP5  datasheet p122
    RPOR3bits.RP6R = 3;    //RP6 tied to UART1 TX datasheet p123

    /* For Baud Rate of 230400 to connect to NU32 Utility*/
    U1MODEbits.BRGH = 0; // Turn off High Baud Rate Mode
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (31.7962MHz/(16*230400)) - 1
    U1BRG = 8; //Baud Rate = 220806

    /* For Baud Rate of 38400 */
    //U1MODEbits.BRGH = 0; // Turn off High Baud Rate Mode
    // U1BRG = (Fcy/(4*Baud Rate)) - 1
    // U1BRG = (31.7962MHz/(4*38400)) - 1
    //U1BRG = 68;

    U1MODEbits.PDSEL = 0; //8 bits no parity
    U1MODEbits.STSEL = 0; //1 stop selection bit
    IPC2bits.U1RXIP = 7;  //Set priority level of RX interrupt
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;	// Enable Recieve Interrupts
    
    U1MODEbits.UARTEN = 1; //enable the UART
    U1STAbits.UTXEN = 1;   //Enable UART transmit
}

void init_cn(void){
    //Change Notification
    //Enable Change Notification pins
    CNEN2bits.CN21IE = 1;
    CNEN2bits.CN22IE = 1;
    CNEN2bits.CN23IE = 1;
    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 6;      //Set interrupt priority to 7
    IEC1bits.CNIE = 1;      //Enable interrupts
}

void init_ADC(void) {        // Initialize analog-digital voltage converter
    AD1CON1bits.FORM    = 0; // UnSigned Integer Output
    AD1CON1bits.AD12B   = 0; // Select 10-bit mode
    AD1CON2bits.CHPS    = 3; // Select 4-channel mode
    AD1CON1bits.SIMSAM  = 1; // Enable Simultaneous Sampling (all channels)
    AD1CON2bits.ALTS    = 0; // Disable Alternate Input Selection
    AD1CON1bits.ASAM    = 0; // Use manual sampling
    AD1CON1bits.SSRC    = 0b111; // Use an automatic trigger
    AD1CON3bits.SAMC    = 31;// Use longest sampling time of 1us
    AD1CON2bits.VCFG    = 0; // Ensure AVDD and AVSS are used as Vref+ and Vref-
    AD1CON3bits.ADCS = 2;    // Tad = 93ns = 3*Tcy,  Tcy = 31ns
    AD1PCFGLbits.PCFG3 = 0;  //Ensure AN3 is set as analog input
    AD1PCFGLbits.PCFG4 = 0;  //Ensure AN4 is set as analog input
    AD1PCFGLbits.PCFG5 = 0;  //Ensure AN5 is set as analog input

    // Initialize MUXA Input Selection
    AD1CHS123bits.CH123SA   = 1; // Select CH1 +ve = AN3, CH2 +ve = AN4, CH3 +ve = AN5
    AD1CHS123bits.CH123NA   = 0; // Select VREF- for CH1/CH2/CH3 -ve inputs
    AD1CON1bits.SAMP        = 0; // Ensure sampling is turned off
    AD1CON1bits.ADON        = 1; //Turn on the ADC converter
}

void Read_ADC(void) { //manual sampling and conversion function
    AD1CON1bits.SAMP = 1; //Start sampling, sampling is stopped after 1us
    while (!AD1CON1bits.DONE); //wait for sampling and conversion to finish
    ADResultAN3 = ADC1BUF1; //Store AN3
    ADResultAN4 = ADC1BUF2; //Store AN4
    ADResultAN5 = ADC1BUF3; //Store AN5
}

void init_qei(void){
    //Turn on QEI
    TRISBbits.TRISB0 = 1;  //Set B0 as input
    TRISBbits.TRISB4 = 1;  //Set B4 as input
    RPINR14bits.QEA1R = 0; //Set RP0 (B0) as QEI A
    RPINR14bits.QEB1R = 4; //Set RP4 (B4) as QEI B
    AD1PCFGLbits.PCFG2 = 1;//Set B0 as a digital input
    IPC14bits.QEIIP = 5;   //SEt QEI interrupt priority level
    IFS3bits.QEIIF = 0;    //Clear QEI Interrupt flag
    IEC3bits.QEIIE = 1;    //Enable QEI Interrupt
    
    QEI1CONbits.QEIM = 0b101; //QEI x2 mode with reset at MAXxCNT
    MAX1CNT = 0xFFFF; //Set Reset value to maximum
}

void init_timer1(void){
    T1CONbits.TON = 0; //Turn off Timer1
    T1CONbits.TCKPS = 0b11; //Set prescaler as 64:1
    T1CONbits.TCS = 0b00; //Select internal clock
    TMR1 = 0; //Clear Timer1
    PR1 = 1439; //Load Timer1 period value 1439

    IPC0bits.T1IP = 0x02; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt

    T1CONbits.TON = 1; //Turn on Timer1
}
