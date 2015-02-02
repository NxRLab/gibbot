#include <libpic30.h>
#include <p33EP512MC806.h>
#include "time.h"
#include "stdio.h"

// File: time.c 
// Author: Hannah Arntson
// Created on: February 1, 2015 

// Used to initialize timers and trigger interrupts

//*********************************
// function: timer1_on
// initializes Timer1 in timer mode at 20Hz

void timer_on(void){
	T1CONbits.TON = 0;  	//Disables the timer
	T1CONbits.TCS = 0;
	T1CONbits.TGATE = 0; 	//Sets the mode to timer
	T1CONbits.TCKPS=0b00; 	// Selects 1:1 presclar
	TMR1 = 0x00;		 	//Clear timer register
	PR1 = 0x3d0900; 		//Load the period value
							//Number of cycles to achieve 20Hz timer

	IPC0bits.T1IP = 0x01; 	//Set Timer1 interrupt priority level
	IFS0bits.T1IF = 0;  	//Clear Timer1 interrupt priority flag
	IEC0bits.T1IE = 1;		//Enable Timer1 interrupt

	T1CONbits.TON = 1;		//Start timer
}

//***********************************
// function: timer1_off
// turns off Timer1

void timer_off(void){
	T1CONbits.TON = 0;
}

//*************************************
// Interrupt triggered every period
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
	//ISR here, eventually while loop for motor

	IFS0bits.T1IF = 0; 	//Clear Timer1 interrupt flag
}