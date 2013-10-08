#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "peripherals.h"

void lights(void){
    int i=0;
    LED1 = 0;
    while(i<100){
        i++;
        LED3 = !LED3;
    }
    LED1 = 1;
}

void initialize_cn(void) {
    //Change Notification
    CNENDbits.CNIED1 = 1; //Turn on CN for RD1
    CNENDbits.CNIED2 = 1; //Turn on CN for RD2
    CNENDbits.CNIED3 = 1; //Turn on CN for RD3
    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 0b111;  //Set priority to 7
    IEC1bits.CNIE = 1;      //Enable CN interrupts
}

void startup(void){
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
    TRISDbits.TRISD10 = 0;   //Top Magnet
    TRISBbits.TRISB15 = 0;   //Low Magnet
}

void initialize_pwm(void){
    PTCON2bits.PCLKDIV = 0b010; //PWM input clock prescaled by 1:4
    //Period = 80 MHz / (PTPER * Prescaler)
    //Period = 80 MHz / (20kHz * 4) = 1000
    PTPER = 1000;
    IOCON1bits.PMOD = 00; //Set PWM1 to Complementary Mode
    IOCON2bits.PMOD = 00; //Set PWM2 to Complementary Mode
    IOCON3bits.PMOD = 00; //Set PWM3 to Complementary Mode

    DTR1 = DTR2 = DTR3 = 10;
    //DTR = Fosc * Deadtime / Prescaler
    //DTR = 80MHz * 0.7us / 4
    ALTDTR1 = ALTDTR2 = ALTDTR3 = 10;
    //Enable PWM registers
    IOCON1bits.PENH = 1;
    IOCON1bits.PENL = 1;
    IOCON2bits.PENH = 1;
    IOCON2bits.PENL = 1;
    IOCON3bits.PENH = 1;
    IOCON3bits.PENL = 1;
    //Set polarity of PWM registers
    IOCON1bits.POLH = 1;
    IOCON2bits.POLH = 1;
    IOCON3bits.POLH = 1;
    IOCON1bits.POLL = 0;
    IOCON2bits.POLL = 0;
    IOCON3bits.POLL = 0;

    //MDC register provides duty cycle information
    PWMCON1bits.MDCS = 1;
    PWMCON2bits.MDCS = 1;
    PWMCON3bits.MDCS = 1;

    MDC = 100; // Sets master duty cycle at 10%

    commutate(0); //Set all motor outputs to float

    PTCONbits.PTEN = 1;
}

void initialize_adc(void) {        // Initialize analog-digital voltage converter
    AD1CON1bits.FORM    = 0;  // UnSigned Integer Output
    AD1CON1bits.AD12B   = 1;  // Select 12-bit mode
    AD1CON2bits.ALTS    = 0;  // Disable Alternate Input Selection
    AD1CON1bits.ASAM    = 0;  // Use manual sampling
    AD1CON1bits.SSRC    = 0b111; // Use an automatic trigger
    AD1CON1bits.SSRCG    = 0; // Use an automatic trigger
    AD1CON2bits.VCFG    = 0;  // Ensure AVDD and AVSS are used as Vref+ and Vref-
    AD1CON3bits.SAMC    = 15; //
    AD1CON3bits.ADCS = 9;     // Tad = 117.6ns = 10*Tcy,  Tcy = 12.5ns
    ANSELEbits.ANSE6 = 1;

    // Initialize MUXA Input Selection
    AD1CHS0bits.CH0SA = 30;
    AD1CON1bits.SAMP        = 0; // Ensure sampling is turned off
    AD1CON1bits.ADON        = 1; //Turn on the ADC converter
}

short Read_ADC(void) { //manual sampling and conversion function
    AD1CON1bits.SAMP = 1; //Start sampling, sampling is stopped after 1us
    while (!AD1CON1bits.DONE); //wait for sampling and conversion to finish
    return ADC1BUF0; //Return AN3
}

void initialize_uart (void){
    //Setup Peripheral Pin Select
    TRISEbits.TRISE7 = 0;
    ANSELEbits.ANSE7 = 0;
    //RP5->RX  RP6->TX
    RPINR18bits.U1RXR = 118; //UART1 RX Tied to R118
    RPOR6bits.RP87R = 1;     //RP87 tied to UART1 TX
    //RP91->CTS RP96->RTS
    RPINR18bits.U1CTSR = 96; //UART1 CTS tied to R91
    RPOR7bits.RP97R = 2;     //RP96 tied to UART1 RTS

    /* For Baud Rate of 115200 */
    U1MODEbits.BRGH = 0; //Turn High Baud Rate Mode off
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (40MHz/(16*115200)) - 1
    U1BRG = 21; //Baud rate 118694

    U1MODEbits.UEN = 0b00; //Turn on RX, TX, RTS and CTS
    IPC2bits.U1RXIP = 5;
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;	// Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1; //enable the UART
    U1STAbits.UTXEN = 1;
}

void initialize_qei(void){
    //Turn on QEI
    RPINR14bits.QEA1R = 69; //Set RP69 (D5) as QEI1 A
    RPINR14bits.QEB1R = 68; //Set RP68 (D4) as QEI1 B
    RPINR16bits.QEA2R = 32; //Set RP32 (B0) as QEI2 A
    RPINR16bits.QEB2R = 33; //Set RP33 (B1) as QEI2 B
    ANSELBbits.ANSB0 = 0;   //Set B0 as a digital input
    ANSELBbits.ANSB1 = 0;   //Set B1 as a digital input
    POS1CNTL = 1700;
    POS2CNTL = 1700;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1
    QEI2CONbits.QEIEN = 1; //Turn on QEI 2
}

void initialize_i2c(void){

}

void initialize_timer1(void){
    //Create an interrupt at 1kHz
    T1CONbits.TON = 0; //Turn off Timer1
    T1CONbits.TCKPS = 0b11; //Set prescaler as 256:1
    TMR1 = 0; //Clear Timer1
    PR1 = 157; //Load Timer1 period value 1439

    IPC0bits.T1IP = 7; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt

    T1CONbits.TON = 1; //Turn on Timer1
}
