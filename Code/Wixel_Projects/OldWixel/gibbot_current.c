/*
 *  gibbot_current.c
 *  
 *
 *  Created by Matt Collins on 4/27/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


/** example_pwm app:
 *
 * This app shows how to generate two PWM signals with the Wixel on pins P1_3
 * and P1_4 using Timer 3.
 *
 * To understand how this app works, you will need to read Section 12 of the
 * CC2511 datasheet, which documents Timer 3 and Timer 4.
 *
 * We do not currently have a general-purpose PWM library, so this example
 * directly accesses the timer registers in order to set up PWM.
 * The servo library is not appropriate for most PWM applications because it
 * is designed for RC servos and cannot produce a full range of duty cycles.
 *
 * The PWM frequency used by this app is 11.7 kHz, which works well for most
 * DC motor control applications.  If you need a different frequency, you can
 * change the prescaler configuration bits in the T3CTL register to achieve
 * frequencies as high as 93.8 kHz and as low as 0.73 kHz.
 *
 * If you are using PWM to control a DC motor and your driver can tolerate a
 * 23.4 kHz PWM frequency, then we recommend uncommenting the line in timer3Init
 * that sets the frequency to 23.4 kHz.  This frequency is ultrasonic so you
 * should not hear a high-pitched whine from your motor.  You will need to
 * consult the datasheet of your motor driver and make sure it can tolerate the
 * higher frequency.
 *
 * This code could be adapted to use Timer 4, but Timer 4 is used by the
 * wixel.lib library to implement getMs(), so it would interfere with many of
 * the Wixel's standard libraries.
 *
 * If you need finer control over the duty cycle, you should use Timer 1
 * which is a 16-bit timer.
 */

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <uart0.h>
#include <stdio.h>
#include <radio_com.h>
#include <radio_link.h>
#include "encoder.h"
#include "gibbot_current.h"
#include "gibbot_motion.h"

static uint16 i = 0;
//static uint8 j=255;
//static int e=0,eint=0,u=0,kp=0,ki=0,Ampsref=0;
 
ISR(T4,0)
 {
	 uint8 horl;
	 uint16 prevwallenc, wallenc;
	 int16 direction;
	 horl = isPinHigh(15);
	 setDigitalOutput(15,!horl);	
	 
	 //wallenc = wall_angle();
	 //direction = wallenc - prevwallenc;
	 //prevwallenc = wallenc;
	 
	 if (i < 16384)
	 {
		 setDigitalOutput(17,0);
		 T3CC0 = 0;
		 T3CC1 = 125;
		 i++;
	 }
	 else
	 {
		setDigitalOutput(17,1);
		if (32768 == i)
		 {
			 i = 0;
		 }
		 else 
		 {
			 i++;
		 }
	 }
		 
	/* if (direction < 0)
	 {
		 setDigitalOutput(17,0);
		 //T3CC0 = 0;
		 //T3CC1 = 150;
	 }
	 
	 else if (direction > 0)
	 {
		 setDigitalOutput(17,1);
		// T3CC0 = 0;
		 //T3CC1 = 150;
	 }
	 else
	 {
		 T3CC0 = 255;
		 T3CC1 = 0;
	 }
	 
	 if (-45 <= wall_angle() <= 45)
	 {
		 T3CC0 = 0;
		 T3CC1 = 150;
	 }
	 else 
	 {
		 T3CC0 = 0;
		 T3CC1 = 255;
	 }*/
	 /*uint32 ampvalue;
	 uint16 ucycle;
	 ampvalue=current_amps_get();
	 ucycle=0;
	 e = Ampsref - ampvalue;
	 eint = e + eint;
	 u = (kp*e+ki*eint)/100;
 
	 if (ucycle < 0) {
		 T3CC0 = ucycle;
		 T3CC1 = 256;
	}
	 else if (ucycle > 0) {
		 T3CC0 = 256;
		 T3CC1 = ucycle;
	 }
	 else if (ucycle == 0) {
		 T3CC0 = 0;
		 T3CC1 = 0;
	 }*/
	 
	 T4IF = 0;
 }


void timer3Init()
{
    // Start the timer in free-running mode and set the prescaler.
    //T3CTL = 0b01110000;   // Prescaler 1:8, frequency = (24000 kHz)/8/256 = 11.7 kHz
    T3CTL = 0b01010000; // Use this line instead if you want 23.4 kHz (1:4)
	
    // Set the duty cycles to zero.
    T3CC0 = T3CC1 = 0;
	
    // Enable PWM on both channels.  We choose the mode where the channel
    // goes high when the timer is at 0 and goes low when the timer value
    // is equal to T3CCn.
    T3CCTL0 = 0b00011100;
    T3CCTL1 = 0b00100100;
	
    // Configure Timer 3 to use Alternative 1 location, which is the default.
    PERCFG &= ~(1<<5);  // PERCFG.T3CFG = 0;
	
    // Configure P1_3 and P1_4 to be controlled by a peripheral function (Timer 3)
    // instead of being general purpose I/O.
    P1SEL |= (1<<3) | (1<<4);
	
    // After calling this function, you can set the duty cycles by simply writing
    // to T3CC0 and T3CC1.  A value of 255 results in a 100% duty cycle, and a
    // value of N < 255 results in a duty cycle of N/256.
	
	P1DIR |= 1<<7;
}

void timer4Init()
{
	T4CTL = 0b10111010;
	T4CC0 = 0x95;
	T4CCTL0 = 0b01000000;
	T4IF = 0;
	T4IE = 1;
	P1SEL |= 0<<5;
	P1DIR |= 1<<5;
}

uint16 current_amps_get()
{
	uint16 adcvalue;
	uint16 mAvalue, mVvalue;
	adcvalue = adcRead(0);
	mVvalue = ((float) adcvalue * 3300) / 2047;
	mAvalue = ((float) mVvalue * 1000) / 525;
	return mAvalue;
}

void shutdown_movement()
{
	T3CC0 = 255;
	T3CC1 = 0;
	T1IE = 0;
	T4IE = 0;
}

void start_up_movement()
{
	T1IE = 1;
	T4IE = 1;
}
/*void current_gains_sprintf(char * buffer)
{
	sprintf(buffer,"%d %d",kp,ki);
}

void current_gains_sscanf(const char * buffer)
{
	sscanf(buffer,"%d %d",&kp,&ki);
}*/



	