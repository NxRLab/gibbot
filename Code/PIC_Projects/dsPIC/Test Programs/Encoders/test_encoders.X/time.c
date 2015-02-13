#include <libpic30.h>
#include <p33EP512MC806.h>
#include "time.h"
#include "stdio.h"
#include "motor.h"
#include "initializeV6.h"
#include "encoder.h"

// File: time.c 
// Author: Hannah Arntson
// Created on: February 1, 2015 

// Used to initialize timers and trigger interrupts

//*********************************
// function: timer1_on
// initializes Timer1 in timer mode to interrupt every 30ms

void timer1_on(void){
	T1CONbits.TON = 0;  	//Disables the timer
	T1CONbits.TCS = 0;
	T1CONbits.TGATE = 0; 	//Sets the mode to timer
	T1CONbits.TCKPS=0b11; 	// Selects 1:256 presclar, 256 clk cycles per timer tick
	TMR1 = 0x00;		 	//Clear timer register
        PR1 = 0x7a12;                   //period value for 30ms
	//PR1 = 0x16e36;                //period value for 300ms
        //PR1=0x4c4b4;                  //period value for 1s

	IPC0bits.T1IP = 0x01; 	//Set Timer1 interrupt priority level
	IFS0bits.T1IF = 0;  	//Clear Timer1 interrupt priority flag
	IEC0bits.T1IE = 1;		//Enable Timer1 interrupt

	T1CONbits.TON = 1;		//Start timer
}

//***********************************
// function: timer1_off
// turns off Timer1

void timer1_off(void){
	T1CONbits.TON = 0;
}

//************************************
// function: timer2_on
// initializes Timer2 in timer mode at 10Hz

void timer2_on(void){
	T2CONbits.TON = 0; 		//Disables timer
	T2CONbits.TSIDL = 1;	//Stop operation in idle mode
	T2CONbits.TCS = 0;
	T2CONbits.TGATE = 0;	//Sets the mode to timer
	T2CONbits.T32 = 0;		//Selects 16-bit timer mode
	T2CONbits.TCKPS = 0b11;	//Selects 1:256 prescalar
	TMR2 = 0x00;			//Clear timer register
	PR2 = 0x7a12;			//Load the period value
							//Number of cycles to achieve 1Hz timer

	IPC1bits.T2IP = 0x01;	//Set Timer2 interruprt priority level
	//IFS0bits.T2IF = 0;		//Clear Timer2 interrupt priority flag
	IEC0bits.T2IE = 1;		//Enable Timer2 interrupt

	T2CONbits.TON = 1;		//Start Timer2
}

//**************************************
// function: timer2_off
// turns off Timer2

void timer2_off(void){
	T2CONbits.TON = 0;
}

//************************************
// function: timer3_on
// initializes Timer3 in timer mode at 10Hz

void timer3_on(void){
	T3CONbits.TON = 0; 		//Disables timer
	T3CONbits.TSIDL = 1;	//Stop operation in idle mode
	T3CONbits.TCS = 0;
	T3CONbits.TGATE = 0;	//Sets the mode to timer
	T3CONbits.TCKPS = 0b11;	//Selects 1:256 prescalar
	TMR3 = 0x00;			//Clear timer register
	PR3 = 0x7a12;			//Load the period value
							//Number of cycles to achieve 1Hz timer

	IPC2bits.T3IP = 0x01;	//Set Timer2 interruprt priority level
	//IFS0bits.T3IF = 0;		//Clear Timer2 interrupt priority flag
	IEC0bits.T3IE = 1;		//Enable Timer2 interrupt

	T3CONbits.TON = 1;		//Start Timer2
}

//**************************************
// function: timer3_off
// turns off Timer3

void timer3_off(void){
	T2CONbits.TON = 0;
}


//*************************************
// Interrupt 1
long test_data;
int test_angle;
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //ISR here
    LED1 = 1;   //test to check how long interrupt takes
    //read topmag encoder encoder
    test_data = read_TOPMAGENC();
    test_angle = encoder_to_angle(test_data,'m');
    printf("%d \n",test_angle);
    LED1 = 0;   //turn LED off, interrupt complete

    //clear interrupt flag
    IFS0bits.T1IF = 0;
}

//**************************************
//Interrupt triggered at 1Hz

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    write_duty(0);
	IFS0bits.T3IF = 0; //Clear Timer3 interrupt flag
}


//**************************************
//Interrupt triggered at 1Hz

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    TOPMAG = 1;
	//IFS0bits.T3IF = 0; //Clear Timer3 interrupt flag
}