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

#define WAVEFORMSIZE 1000
#define kt 53.4 //torque constant for Maxon EC60

static int kp = 2, ki = 1; //initialize gain variables
int waveform[WAVEFORMSIZE];
static int count = 0;
int u = 0;
static int uff;
static int epro; //initialize proportional error value
static int eint = 0; //initialize integral error value
static double desired_torque; //This is a value provided by the motion controller to be used in the current controller
static double desired_current;
char tune = '0';



void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) //NOTE: May interfere with other code using timer 1
{
    if (tune=='1'){
        motoron=1;
        controltune(count);
        count=count+1;
        if (count>1000){
            tune='0';
            count=0;
        }
    }


    else {
        calc_effort(desired_torque,current_amps_get(),kp,ki);
        desired_current=desired_torque*kt;
        write_duty(u);
    }



    

}




void calc_effort(int desired, short sensed, int kp, int ki) { //this function calculates an effort value "u" (in a duty cycle value 0-1000) based on integral and proportional "error"
int multiplier = 1; //this value is a conversion factor from amps (0 to max) to duty cycle (0-1000) defined emperically

epro = (desired - sensed)*multiplier;
eint = (eint + epro);
uff = desired; //feed forward term
u = (kp*epro) + (ki*eint) + uff;

		if (u<-1000) {
		u = -1000;
		}

		if (u>1000) {
		u = 1000;
		}
}


//TODO: set up ADC properly
int current_amps_get()
{
int ticks;
int reftickslow = 0;    // TODO: measure adc ticks at zero load current
int reftickshigh = 1000;    // TODO: measure adc ticks at stall current
int amprange = 750;   // TODO: measure range from 0 current to stall current in mA
int sensorcurrent;
int offset;


ticks = read_ADC(); //read initial value from ADC.


//prevents misreads and limits range of readings:
if (ticks < reftickslow) {
ticks = reftickslow;
}

if (ticks > reftickshigh) {
ticks = reftickshigh;
}

//sets an offset to adjust the range of readings to be centered around 0:
offset = reftickslow + ((reftickshigh-reftickslow)/2);

//calculates a current value (mA) and returns it:
sensorcurrent = (ticks-offset)*(amprange/((reftickshigh-reftickslow)/2)); // in mA
return sensorcurrent;

}


void controltune(int i){
    calc_effort(waveform[i], current_amps_get(), kp, ki);
    write_duty(u);
}

void track_wave(int reference){ //this function creates either a square wave or sine wave at the desired frequency based on its input
    int i;
    count=0;
        for (i = 0; i < WAVEFORMSIZE; i++){
            if(count<(WAVEFORMSIZE/2)){
                waveform[i] = 0;
                count=count+1;
            }
            else {
                waveform[i] = reference;
            }
    }
}

//This is to test that the PI controller functions are outputting reasonable values without the motor running or ADC functioning
void test_output(void){
    track_wave(750);
        int ADC_fake[1000];
        int effort[1000];
        int j;
        for (j = 0; j < 1000; j++){
            ADC_fake[j]=j;
            calc_effort(waveform[j],ADC_fake[j],1,1);
            effort[j]=u;
        }

        int somenumber=7;
        printf("%d\r\n",somenumber);
        /*int k;

        for (k = 0; k < 1000; k++){
            int adcfake=ADC_fake[k];
            printf("%d",adcfake);
        }

        k=0;
        delay_ms(5000);

        for (k = 0; k < 1000; k++){
            printf("%d",effort[k]);
        }

        k=0;
        delay_ms(5000);

        for (k = 0; k < 1000; k++){
            printf("%d",waveform[k]);
        }*/
}