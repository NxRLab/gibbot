/*
 *  encoder.c
 *  
 *
 *  Created by Matt Collins on 4/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <uart0.h>
#include "encoder.h"

uint16 motor_encoder_read(void) 
{
	uint8 rxbuffer[2];
	uint16 data;
	
	uart0TxSendByte(1); //send a 1 for lower motor encoder bits
	if (uart0RxAvailable()!=0) {
		rxbuffer[0]=uart0RxReceiveByte(); //receive lower motor encoder bits
	}
	delayMs(1);
	uart0TxSendByte(2); //send 2 for upper motor encoder bits
	if (uart0RxAvailable()!=0) {
		rxbuffer[1]=uart0RxReceiveByte(); //receive upper motor encoder bits
	}
	data=0;
	data=rxbuffer[1]<<8;
	data|=rxbuffer[0];
	return data;
}

uint16 wall_encoder_read(void)
{
	uint8 rxbuffer[2];
	uint16 data;
	
	uart0TxSendByte(3); //send a 3 for lower wall encoder bits
	if (uart0RxAvailable()!=0) {
		rxbuffer[0]=uart0RxReceiveByte(); //receive lower wall encoder bits
	}
	delayMs(1);
	uart0TxSendByte(4); //send 4 for upper wall encoder bits
	if (uart0RxAvailable()!=0) {
		rxbuffer[1]=uart0RxReceiveByte(); //receive upper wall encoder bits
	}
	data=0;
	data=rxbuffer[1]<<8;
	data|=rxbuffer[0];
	return data;
}

void motor_encoder_reset(void)
{
	uart0TxSendByte(5);
}

void wall_encoder_reset(void)
{
	uart0TxSendByte(6);
}
	
	
	



