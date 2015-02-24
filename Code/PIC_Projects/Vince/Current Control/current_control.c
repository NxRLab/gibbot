/*
*File: current_control.h
*Author: Vince Martinez
*V1.1
*/

#include "current_control.h"
#include <stdio.h>
#include <p33EP512MC806.h>
#include "core.h"
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "UART.h"


static int kp = 1, ki = 0; //initialize gain variables
static int currentduty;
static int refcurrent = 200;
static int count = 0;
static int u;
static int epro; //initialize proportional error value
static int eint = 0; //initialize integral error value
int pwm=0;//used in case: TEST
int desiredpwm=500;//used in case: TEST



void _ISR _T1Interrupt(void) { //Timer 1 interrupt (interrupts at frequency determined in intialize_TIMER1)

    if (count==0){
       test();
    }
    count=count+1;
    if (count==500){
    LED1=!LED1;
    count=1;
    }
/*switch (core_state) //core_state is a global variable that changes elsewhere based on the desired action (defined in core.h)
	{
		case TEST:
		{
		while (pwm!=desiredpwm) {
		write_duty(pwm);
		calc_effort(desiredpwm,pwm,kp,ki);
		sprintf(str, "Current duty cycle: %d Current proportional error: %d Current integral error: %d Current effort: %d\r\n",pwm,epro,eint,u);
		write_string_UART(str,100);
		pwm=pwm+100;
		__delay32(40000000);
		__delay32(40000000);
		__delay32(40000000);
		}
			break;
		}
		case IDLE:
		{
		write_duty(0);
		eint = 0;
			break;
		}
		case PWM:
		{
		write_duty(currentduty);
			break;
		}
		case TUNE:
		{	
			break;
		}
}*/
}

void initialize_CurrentControl (void) {
initialize_TIMER1();
//initialize_ADC_Single(); //only include this if it is not initialized elsewhere
//include other initializations here
}

void initialize_TIMER1(void){// for 5kHz interrupt frequency, PR1=2000-1. For 5 Hz, PR1=62500-1 << wrong
	T1CONbits.TCS = 0;
	T1CONbits.TCKPS = 0b01;
	PR1 = 62500 - 1;
	TMR1 = 0;
	IPC0bits.T1IP = 7;
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
	T1CONbits.TON  = 1;

}

void calc_effort(int desired, short sensed, int kp, int ki) { //this function calculates an effort value "u" (in a duty cycle value 0-1000) based on integral and proportional "error"
int multiplier = 1; //this value is a conversion factor from amps (0 to max) to duty cycle (0-1000) defined emperically

epro = (desired - sensed)*multiplier;
eint = (eint + epro);
u = (kp*epro) + (ki*eint);

		if (u<-1000) {
		u = -1000;
		}

		if (u>1000) {
		u = 1000;
		}
}

void current_pwm_set(int duty_percent)//this is called by menu.c when the duty cycle % is specified by the user
{
currentduty = duty_percent*10;     // 10 = 1000 max duty cycle divided by 100 max percentage input
}

void test(void) { //this function should go within the "switch" block once it is set up
		//write_duty(pwm);
    char str[200];
    while(pwm!=desiredpwm) {
		calc_effort(desiredpwm,pwm,kp,ki);
		sprintf(str, "Current duty cycle: %d Current proportional error: %d Current integral error: %d Current effort: %d\r\n",pwm,epro,eint,u);
		write_string_UART(str,200);
                //U1TXREG = str;
                eint=0;
                epro=0;
                u=0;
                pwm=pwm+50;
		__delay32(80000000);
		__delay32(80000000);
		__delay32(80000000);
                __delay32(80000000);
                __delay32(80000000);
                count=1;
                LED2=!LED2;
    }
}