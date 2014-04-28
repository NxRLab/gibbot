// Timer Functions
#include <jvp002.h>



void SetupT1CountINT(void)
{
/*******************/
/*  Configure Timer1 in synchronous counter mode
 *
 * 1. Clear the ON control bit (TxCON<15>=0) to disable the timer.
 * 2. Clear the TCS control bit (TxCON<1>=0) to select the internal PBCLK source.
 * 3. Select the desired timer input clock prescale.
 * 4. Load/Clear the timer register TMRx.
 * 5. Load the period register PRx with the desired 16-bit match value.
 * 6. If interrupts are used:
 *      a) Clear the TxIF interrupt flag bit in the IFSx register.
 *      b) Configure the interrupt priority and subpriority levels in the IPCx register.
 *      c) Set the TxIE interrupt enable bit in the IECx register.
 * 7. Set the ON control bit (TxCON<15>=1) to enable the timer.
 * 
 */
// Setup the Timer
	// Turn timer 1 off
	T1CONbits.ON = 0;
	// Operate in 16-Bit Synchronous Clock Counter Mode
	T1CONbits.TCS = 0;
	// Disable the Timer Gated Time Accumulation
	T1CONbits.TGATE = 0;
	// We want it to be running at 1 ms, thus 1:64 prescale from 80MHz clock and
	T1CONbits.TCKPS = 0x02;
	// Set the period match to 1250
	PR1 = 0x04E2;
	// Clear the timer register
	TMR1 = 0x0000;
// Setup the interrupt
    // Set the Priority of the Timer1 Interrupt Service Routine to 4
    IPC1bits.T1IP = 0x05;
    // Set sub-priority to 0
    IPC1bits.T1IS = 0x00;
    // Enable Timer1 as an interrupt
    IEC0bits.T1IE = 1;
/*******************/	
	
}

void SetupTimer2_3PWM(void)
{
// We'll use timer 2 for the the motors
// and timer 3 for the servos. Need two timers in case
// We need different frequencies for the two actuators

// OC1 = Right Motor
// OC2 = Left Motor
// OC3 = PWM0
// OC4 = PWM1
// OC5 = MUXed with PMWR/PMENB
/*
* 1.Set the PWM period by writing to the selected timer period register (PRy).
* 2.Set the PWM duty cycle by writing to the OCxRS register.
* 3.Write the OxCR register with the initial duty cycle.
* 4.Enable interrupts, if required, for the timer and Output Compare modules. The output compare interrupt is required for PWM Fault pin utilization.
* 5.Configure the Output Compare module for one of two PWM Operation modes by writing to the Output Compare mode bits, OCM<2:0> (OCxCON<2:0>).
* 6.Set the TMRy prescale value and enable the time base by setting TON (TxCON<15>) = 1.
*/

/* Setting up for OC1-4 */

	// Disable the Output Compare modules
	OC1CONbits.ON = 0;
	OC2CONbits.ON = 0;
	OC3CONbits.ON = 0;
	OC4CONbits.ON = 0;
	
	// Setup for 16 bit timer mode
	OC1CONbits.OC32 = 0;
	OC2CONbits.OC32 = 0;
	OC3CONbits.OC32 = 0;
	OC4CONbits.OC32 = 0;
	
	// Timer 2 for OC1 and 2, Timer 3 for OC3 and 4
	OC1CONbits.OCTSEL = 0;
	OC2CONbits.OCTSEL = 0;
	OC3CONbits.OCTSEL = 1;
	OC4CONbits.OCTSEL = 1;
	
	// All modules will be PWM mode, fault pin disabled
	OC1CONbits.OCM = 0x06;
	OC2CONbits.OCM = 0x06;
	OC3CONbits.OCM = 0x06;
	OC4CONbits.OCM = 0x06;
	
// Set the initial Duty Cycle to 50%
	// For timer 2, max duty cycle is 0x04E2
	OC1R = 0x0271;
	OC2R = 0x0271;
	// For timer 3, max duty cycle is 0x61A8
	OC3R = 0x30D4;
	OC4R = 0x30D4;

// Set the next Duty Cycle to 50%
	// For timer 2, max duty cycle is 0x04E2
	OC1RS = 0x0271;
	OC2RS = 0x0271;
	// For timer 3, max duty cycle is 0x61A8
	OC3RS = 0x30D4;
	OC4RS = 0x30D4;



/* Setting up for Timers 2 and 3 */

// For Timer 2, we want a 1kHz period, same as Timer 1
	// Turn timer 2 off
	T2CONbits.ON = 0;
	// Operate in 16-Bit Synchronous Clock Counter Mode
	T2CONbits.TCS = 0;
	// Disable the Timer Gated Time Accumulation
	T2CONbits.TGATE = 0;
	// We want it to be running at 1kHz, thus 1:64 prescale from 80MHz clock and ...
	T2CONbits.TCKPS = 0x02;
	// ... set the period match to 1250
	PR2 = 0x04E2;
	// Clear the timer register
	TMR2 = 0x0000;

// For timer 3, set up a 50 Hz period
	// Turn timer 1 off
	T3CONbits.ON = 0;
	// Operate in 16-Bit Synchronous Clock Counter Mode
	T3CONbits.TCS = 0;
	// Disable the Timer Gated Time Accumulation
	T3CONbits.TGATE = 0;
	// We want it to be running at 1 ms, thus 1:64 prescale from 80MHz clock and
	T3CONbits.TCKPS = 0x02;
	// Set the period match to 25000
	PR3 = 0x61A8;
	// Clear the timer register
	TMR3 = 0x0000;

// Turn on the Timers
	T2CONbits.ON = 1;
	T3CONbits.ON = 1;
	
// Enable the Output Compare modules
	OC1CONbits.ON = 1;
	OC2CONbits.ON = 1;
	OC3CONbits.ON = 1;
	OC4CONbits.ON = 1;
	

}


