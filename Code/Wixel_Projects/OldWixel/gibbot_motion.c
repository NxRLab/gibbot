/*
 *  gibbot_motion.c
 *  
 *
 *  Created by Matt Collins on 4/29/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <uart0.h>
#include <stdio.h>
#include <radio_com.h>
#include <radio_link.h>
#include "encoder.h"
#include "gibbot_motion.h"
#include "gibbot_current.h"

//static int kp=0, ki=0, kd=0, e=0, eint = 0, edot = 0, u = 0, eprev=0;

ISR(T1,0)
{
	uint8 horl;
	horl = isPinHigh(16);
	setDigitalOutput(16,!horl);	
	T1IF = 0;

}

void motion_init()
{
	P1SEL |= 0 << 6;
	P1DIR |= 1 << 6;
	PERCFG = 1 << 6;
	T1IF = 0;
	T1IE = 1;
	T1CTL = 0b00000110;
	T1CC0 = 0x3A97;
	TIMIF |= 0b01000000;
	
		
	motor_encoder_reset();
	wall_encoder_reset();
	
	/*core_register_int(&kp);
	core_register_int(&ki);
	core_register_int(&kd);*/
}

int16 motor_angle()
{
	int16 angle;
	angle=((((float)motor_encoder_read()-32768)*360)/39000);
	return angle; 
}

int16 wall_angle()
{
	int16 angle;
	angle=((((float)wall_encoder_read()-32768)*360)/8194);
	return angle; 
}

/*void motion_gains_sprintf(char * buffer)
{	
	//TODO: this is like the current_gains_sprintf,
	//print the gains you use for motion control to the buffer.
	//note: You should edit gains.m so that the format in matlab
	//matches the format here
		sprintf(buffer,"%d %d %d",kp,ki,kd);
}

void motion_gains_sscanf(const char * buffer)
{
	//TODO: read the gains from the buffer using sscanf and store them
	//in the variables you defined to hold them
	sscanf(buffer,"%d %d %d",&kp,&ki,&kd);
}
*/
