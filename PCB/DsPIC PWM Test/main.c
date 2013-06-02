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
int main(int argc, char** argv) {

    // External clock = 8 MHz

    // 8MHz/2*40/2 = 80 MHz = 40 MIPS
    CLKDIVbits.PLLPRE=2;        // PLLPRE divide input by 2
    PLLFBD = 40;                // pll multiplier
    CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0= DIV_2

    CLKDIVbits.PLLPRE -= 2;
    PLLFBD -= 2;

    RCONbits.SWDTEN = 0; // Disable Watch Dog Timer
    while(!OSCCONbits.LOCK);    // wait for PLL ready

    //init pwm
    PTCON2bits.PCLKDIV = 0b000; //clock divider = 1

    //pll period = 1.25 ns;
    //PWM period  = 1.25ns/2*PTPER
    PTPER = 80000; // PWM period = 50 us
    MDC = 40000; //50% duty cycle
    //PDC1 = 40000;
    //SDC1 = 40000; //50% duty cycle for PWM1L in independent mode
    PHASE1 = 0; //No phase shift
    //PHASE2 = 0;
    PWMCON1bits.FLTIEN = 0; // disable fault int
    PWMCON1bits.CLIEN = 0; //Current limit int disabled
    PWMCON1bits.TRGIEN = 0; //trigger in disabled
    PWMCON1bits.ITB = 0; //use PTPER for period;
    PWMCON1bits.MDCS = 1; //use MDC for duty cycle, can set to 0 and then set using PDCx
    PWMCON1bits.DTC = 0b10;// disable dead time
    IOCON1bits.PENH = 1; //PWM controls PWM1H
    IOCON1bits.PENL = 1; //PWM controls PWM1L
    IOCON1bits.POLH = 0; //PWM1H active high (default)
    IOCON1bits.POLL = 0; //PWM1L active low O(default)
    IOCON1bits.PMOD = 0b00; //Complementary output mode
    PTCONbits.PTEN = 1; //enable pwm

    return (EXIT_SUCCESS);
}

