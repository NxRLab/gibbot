#include <libpic30.h>
#include <p33EP512MC806.h>
#include "time.h"
#include "stdio.h"
#include "motor.h"
#include "initializeV6.h"
#include "encoder.h"

/* File: time.c
   Author: Hannah Arntson
   Created on: February 1, 2015

   Used to initialize timers and trigger interrupts */

//global array to hold angle data if printf is too slow
//int angles[850];
//int count = 0;

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


//*************************************
// Interrupt 1

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    long test_data1, test_data2;
    //int test_angle;
    
    //ISR here
    LED1 = 1;   //test to check how long interrupt takes
    //read topmag encoder encoder
    test_data1 = read_TOPMAGENC();
    //test_angle = encoder_to_angle(test_data,'m');
    test_data2 = read_LOWMAGENC();

    //store to an array rather than print to screen every time
    /*if (count<(sizeof(angles)/sizeof(int))){
        angles[count] = test_angle;
    }
    else{
        int i =0;
        for(i; i<(sizeof(angles)/sizeof(int)); i++){
            printf("%d \n",angles[i]);
        }
        count=0;
    }*/

    printf("%ld \t %ld\n",test_data1, test_data2);
    LED1 = 0;   //turn LED off, interrupt complete

    //clear interrupt flag
    IFS0bits.T1IF = 0;
}
