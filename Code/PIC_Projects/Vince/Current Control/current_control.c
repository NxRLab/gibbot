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

    /*if (count==0){
       test();
    }
    count=count+1;
    if (count==500){
    LED1=!LED1;
    count=1;
    }*/
switch (core_state) //core_state is a global variable that changes elsewhere based on the desired action (defined in core.h)
	{
		case TEST:
		{
                char str[200];
                while(pwm!=desiredpwm) {
		calc_effort(desiredpwm,pwm,kp,ki);
		sprintf(str, "Current duty cycle: %d Current proportional error: %d Current integral error: %d Current effort: %d\r\n",pwm,epro,eint,u);
		write_string_UART(str,200);
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

                if (abs(refcurrent) != 200) {
		refcurrent = 200;
		}

		count = count + 1;

		if (count == 25) {
		count = 0;
		refcurrent = -refcurrent;
		}

		int currentampsget;
		currentampsget = current_amps_get();
		calc_effort(refcurrent, currentampsget, kp, ki);

		if (u < 0) {
		OC1RS = abs(u + 500);
		OC2RS = 500;
		}

		if (u >= 0) {
		OC1RS = 500;
		OC2RS = abs(u - 500);
		}
			break;
		}
}
}

void initialize_CurrentControl (void) {
timer1_on();
core_init();
//initialize_ADC_Single(); //only include this if it is not initialized elsewhere
//include other initializations here
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

int current_amps_get()
{
int ticks;
int reftickslow = 0;    // TODO: measure adc ticks at zero load current
int reftickshigh = 1000;    // TODO: measure adc ticks at stall current
int amprange = 750;   // TODO: measure range from 0 current to stall current in mA
int sensorcurrent;
int offset;
ticks = core_adc_read();

if (ticks < reftickslow) {
ticks = reftickslow;
}

if (ticks > reftickshigh) {
ticks = reftickshigh;
}

offset = reftickslow + ((reftickshigh-reftickslow)/2);
sensorcurrent = (ticks-offset)*(amprange/((reftickshigh-reftickslow)/2)); // in mA

/*if (abs(ticks-510)<5) { //not too sure what this did in my old code...
sensorcurrent = 0;
}*/
	return sensorcurrent;
}

void current_gains_sprintf(char * buffer)
{

sprintf(buffer, "%d %i",kp,ki);

	// TODO: sprintf the gains ki and kp into the buffer
	//For Now we return return a dummy buffer with fixed gains
	//you will need to remove this
	//buffer[0]='1'; //remove me when implemented
	//buffer[1]=' '; //remove me when implemented
	//buffer[2]='7'; //remove me when implemented
	//buffer[3]='\0';//remove me when implemented
}

void current_gains_sscanf(const char * buffer)
{
sscanf(buffer, "%d %i",&kp,&ki);
	//TODO: buffer will contain the gains as two numbers separated by 
	// a space.  scanf them from buffer and store the gains in
	// kp and ki

}

/*void test(void) { //this function should go within the "switch" block once it is set up
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
*/