/*
*File: current_control.h
*Author: Vince Martinez
*V1.1
*/

#include "current_control.h"
#include <stdio.h>
#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "UART.h"
#include "initializeV6.h"


static int kp = 2, ki = 1; //initialize gain variables
static double kt = 53.4; //torque constant for Maxon EC60
static int currentduty;
static int refcurrent;
static int count = 0;
static int u = 0;
static int uff;
static int epro; //initialize proportional error value
static int eint = 0; //initialize integral error value
int pwm=0;//used in case: TEST
int desiredpwm=500;//used in case: TEST

unsigned char d = 'x';
int tune=0;

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)//changed this to timer 2 for the sake of making the current control timer interrupt function properly. timer 2 should be set up as well.
{

    d=read_UART();

    if (d=='1'){
        printf("you chose the test case. good choice\r\n");
        printf("that's awkward... I don't really have anything to do here. yell at vince he's a slacker.\r\n");
        d='x';

    }

    else if (d=='2'){
        printf("you chose the idle case. exciting choice.\r\n");
        write_duty(0);
        eint = 0;
        d='x';
    }

    else if (d=='3'){
        printf("you chose PWM mode. the motor should be running at 10 percent duty.\rpress 'u' to increase it by 10, or press 'd' to decrease it by 10.\rpress'q' to quit.\r\n");
            motoron=1;
            // write duty
            write_duty(100);
            kick();
        while (d=='3'){
            int x = read_UART();
            if (x=='u'){
                write_duty(read_duty()+100);
            }
            else if (x=='d'){
                write_duty(read_duty()-100);
            }
            else if (x=='q'){
                write_duty(0);
                motoron=0;
                d='x';
                printf("peace\r\n");
            }
        }
    }

    /*else if (d=='4'){
        printf("welcome to the tuning case!!! here you can test the gains you have saved in the variables kp and ki.\r\n");
        printf("for now, we'll pulse the motor between a few different settings.\r this will give a visual idea of how quickly the current converges.\r\n");
        tune=1;
        d='x';

    }*/

    else if (d=='x'){
            LED3=!LED3;
    }

    else{
        d='x';
    }


    /*if (tune==1){
        if (count<80000000){
            refcurrent=1000; //1 amps case (1000mA)
            calc_effort(refcurrent, current_amps_get(), kp, ki, kt);
            motoron=1;
            // write duty
            write_duty(u);
            kick();
            count=count+1;
        }

        if (count>=80000000 && count<160000000){
            refcurrent=3000; //3 amps case (3000mA)
            calc_effort(refcurrent, current_amps_get(), kp, ki, kt);
            write_duty(u);
            count=count+1;
        }

        if (count>=160000000 && count<240000000){
            refcurrent=0; //0 amps case (0mA)
            calc_effort(refcurrent, current_amps_get(), kp, ki, kt);
            write_duty(u);
            count=count+1;
        }

        if (count>=240000000){
            count=0;
            tune=0;
            printf("done!!!!\r\n");
        }


    }*/
//clear interrupt flag
IFS0bits.T1IF = 0;


    

}


/*
void _ISR _T1Interrupt(void) { //Timer 1 interrupt (interrupts at frequency determined in intialize_TIMER1)

    /*if (count==0){
       test();
    }
    count=count+1;
    if (count==500){
    LED1=!LED1;
    count=1;
    }
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
		case COAST:
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
*/

void initialize_CurrentControl (void) {
//timer1_on();
//initialize_ADC_Single(); //only include this if it is not initialized elsewhere
//include other initializations here
}


void calc_effort(int desired, short sensed, int kp, int ki, double kt) { //this function calculates an effort value "u" (in a duty cycle value 0-1000) based on integral and proportional "error"
int multiplier = 1; //this value is a conversion factor from amps (0 to max) to duty cycle (0-1000) defined emperically

epro = (desired - sensed)*multiplier;
eint = (eint + epro);
uff = desired*kt; //feed forward term
u = (kp*epro) + (ki*eint) + uff;

		if (u<-100) {
		u = -100;
		}

		if (u>100) {
		u = 100;
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
ticks = read_ADC();

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