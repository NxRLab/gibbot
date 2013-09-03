// Main program for testing JVP002


#include "jvp002.h"
#include "lcd_setup.h"
#include "misc.h"
#include "adc_setup.h"

/** Configurations **/
// Configuring the Device Configuration Registers
// 80Mhz Core/Periph, Pri Osc w/PLL
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx1, BWP = OFF

/** # Defines **/
#define MAX		2500

/** Globals **/
int state;
int reset;
int adc1,adc2;
char string[32];
int led;
int pwm;
int d1;
int d2;
int state_init[5] = {0,0,0,0,0};

int main(void)
{
	int delay;
	d2 = 0;
	d1 = 0;
	state = 0;
	reset = 1;
	adc1 = 0;
	adc2 = 0;
	led = 0;
	pwm = 0;
	double volt1 = 0.0;
	double volt2 = 0.0;

	// Setup functions for operation
	CP0Init();
	INTInitialize();
	ADCSetup();
	SetupButtons();
	SetupIO();
	SetupT1CountINT();
	SetupTimer2_3PWM();

	// Wait until LCD screen comes up
	wait(1000);	wait(1000);	wait(1000); wait(1000);
	LCDConfig();
	LCDSetup();

	

	// Start the timer
	T1CONbits.ON = 1;

	while(1)
	{
		if(reset == 1)
		{
			ClearLCDScreen();
			sprintf(string,"A = Cmd button");
			WriteLCD(1,string);
			reset = 0;
			state = 0;
		}
		else
		{
			switch(state)
			{
				case 0:
					if(state_init[0] != 0)
						state_init[0] = 0;
					wait(100);
					break;
				case 1:
					if(state_init[0] != 1)
					{
						state_init[0] = 1;
						if(state_init[1] == 0)
							state_init[1] = 1;
						else
							state_init[1] = 0;
					}
					wait(100);
					break;
				case 2:
					if(state_init[0] != 2)
					{
						state_init[0] = 2;
						if(state_init[2] == 0)
							state_init[2] = 1;
						else
							state_init[2] = 0;
					}
					wait(100);
					break;
				case 3:
					if(state_init[0] != 3)
					{
						state_init[0] = 3;
						if(state_init[3] == 0)
							state_init[3] = 1;
						else
							state_init[3] = 0;
					}
					wait(100);
					break;
				case 4:
					if(state_init[0] != 4)
					{
						state_init[0] = 4;
						if(state_init[4] == 0)
							state_init[4] = 1;
						else
							state_init[4] = 0;
					}
					wait(100);
					break;
				default:
					wait(100);
					break;
			}
			if(state_init[1] == 0 && state_init[2] == 0 && state_init[3] == 0)
				sprintf(string,"LB=0;RB=0;WPER=0");
			else if(state_init[1] == 1 && state_init[2] == 0 && state_init[3] == 0)
				sprintf(string,"LB=1;RB=0;WPER=0");
			else if(state_init[1] == 0 && state_init[2] == 1 && state_init[3] == 0)
				sprintf(string,"LB=0;RB=1;WPER=0");
			else if(state_init[1] == 1 && state_init[2] == 1 && state_init[3] == 0)
				sprintf(string,"LB=1;RB=1;WPER=0");
			else if(state_init[1] == 0 && state_init[2] == 0 && state_init[3] == 1)
				sprintf(string,"LB=0;RB=0;WPER=1");
			else if(state_init[1] == 1 && state_init[2] == 0 && state_init[3] == 1)
				sprintf(string,"LB=1;RB=0;WPER=1");
			else if(state_init[1] == 0 && state_init[2] == 1 && state_init[3] == 1)
				sprintf(string,"LB=0;RB=1;WPER=1");
			else if(state_init[1] == 1 && state_init[2] == 1 && state_init[3] == 1)
				sprintf(string,"LB=1;RB=1;WPER=1");

			if(state != -1)// && state != 0)
			{
				wait(100);
				WriteLCD(2,string);
			}
		}		
	}
	return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL5AUTO) Timer1INTHandler(void)
{
	int a;
	double perc;

	if(d1 == 25)
	{
		state = CheckButtons();

		if(state_init[3] == 1)
		{
			ReadADC(&adc1,&adc2);
			perc = (double)(adc1)/1023.00;
			SetPWMDutyCycle(3,perc);
		}
		else
		{
			perc = 1.00;
			SetPWMDutyCycle(3,perc);
		}

		d1 = 0;
	}
	else
		d1++;

	if(d2 == 1000)
	{
		if(state_init[1] == 0 && state_init[2] == 0)
		{
			LED1 = 1;
			LED2 = 1;
		}
		else if(state_init[1] == 1 && state_init[2] == 0)
		{
			LED1 = !LED1;
			LED2 = 1;
		}
		else if(state_init[2] == 1 && state_init[1] == 0)
		{
			LED2 = !LED2;
			LED1 = 1;
		}
		else if(state_init[2] == 1 && state_init[1] == 1)
		{
			a = LED1;
			LED1 = !LED1;
			LED2 = !a;
		}
		d2 = 0;
	}
	else
		d2++;
	// Clear the interrupt flag
	IFS0bits.T1IF = 0;
}


