/* 
 * File:   main.c
 * Author: James
 *
 * Created on June 1, 2013, 11:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>


/*
 * 
 */


/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(FWDTEN_OFF)
_FPOR(FPWRT_PWR128)
_FICD(ICS_PGD2 & JTAGEN_OFF)

int main() {

    //Configure oscillator freq Fosc
    // Fin = External oscillater clock = 8 MHz
    // Fosc = Fin*M/(N1*N2)
    // 8MHz*40/(2*2) = 80 MHz
    // Fcy = Fosc/2 = 40 MIPS

    //TRISBbits.TRISB15 = 0;
    //LATBbits.LATB15 = 1;
    CLKDIVbits.PLLPRE=2;        // N1 = PLLPRE-2
    PLLFBD = 40;                // M = PLLFBD-2
    CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0= DIV_2

    CLKDIVbits.PLLPRE -= 2;
    PLLFBD -= 2;

    __builtin_write_OSCCONH(0x01);	/* New Oscillator FRC w/ PLL */
    __builtin_write_OSCCONL(0x01);  	/* Enable clock switch Switch */
    
    RCONbits.SWDTEN = 0; // Disable Watch Dog Timer
    
    while(OSCCONbits.COSC != 0b001); //Wait for new Oscillator to become FRC w/ PLL */
    while(!OSCCONbits.LOCK);    // wait for PLL ready

    ACLKCONbits.FRCSEL = 1;	/* FRC provides input for Auxiliary PLL (x16) */
    ACLKCONbits.SELACLK = 1;	/* Auxiliary Oscillator provides clock source for PWM & ADC */
    ACLKCONbits.APSTSCLR = 7;	/* Divide Auxiliary clock by 1 */
    ACLKCONbits.ENAPLL = 1;	/* Enable Auxiliary PLL */

    while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */



    //init pwm
    //PWM period  = PTPER*1.04ns*PCLKDIV
    PTCON2bits.PCLKDIV = 0b101; //PCLKDIV = 32
    PTPER = 3004; // PWM period = 100 us => freq = 10kHz
        
    PWMCON1bits.FLTIEN = 0; // disable fault int
    PWMCON1bits.CLIEN = 0; //Current limit int disabled
    PWMCON1bits.TRGIEN = 0; //trigger in disabled
    PWMCON1bits.ITB = 0; //use PTPER for period;
    PWMCON1bits.MDCS = 0; //use PDC1 for duty cycle
    PWMCON1bits.DTC = 0b00;// enable dead time
    IOCON1bits.PENH = 1; //PWM controls PWM1H
    IOCON1bits.PENL = 1; //PWM controls PWM1L
    IOCON1bits.POLH = 0; //PWM1H active high (default)
    IOCON1bits.POLL = 0; //PWM1L active low O(default)
    IOCON1bits.PMOD = 0; //Complementary output mode
    PDC1 = 1502; //50% duty cycle
    DTR1 = 30; //1% dead time
    ALTDTR1 = 30;
    PHASE1 = 0; //No phase shift
    PTCONbits.PTEN = 1; //enable pwm
    while(1);
}

