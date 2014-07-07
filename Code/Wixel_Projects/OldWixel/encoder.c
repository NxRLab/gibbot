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

#define UPPER_MOTOR 2
#define LOWER_MOTOR 1
#define UPPER_WALL 4
#define LOWER_WALL 3


uint16 motor_encoder_read(void) 
{
	uint8 rxbuffer[2];
	uint16 data;
	
	uart0TxSendByte(LOWER_MOTOR); //send a 1 for lower motor encoder bits
	while (uart0RxAvailable() == 0); //wait to receive lower motor encoder bits from dsPIC
	if (uart0RxAvailable() != 0) {
	rxbuffer[0] = uart0RxReceiveByte(); //receive lower motor encoder bits
	}
	delayMs(1);
	uart0TxSendByte(UPPER_MOTOR); //send 2 for upper motor encoder bits
	while (uart0RxAvailable() == 0); //wait to receive upper motor encoder bits from dsPIC
	if (uart0RxAvailable() != 0) {
		rxbuffer[1] = uart0RxReceiveByte(); //receive upper motor encoder bits
	}
	data = 0;
	data = rxbuffer[1] << 8; //bit shift upper motor encoder bits
	data |= rxbuffer[0]; //or data with lower motor encoder bits to get full motor encoder value
	return data;
}

uint16 wall_encoder_read(void)
{
	uint8 rxbuffer[2];
	uint16 data;
	
	uart0TxSendByte(LOWER_WALL); //send a 3 for lower wall encoder bits
	while (uart0RxAvailable() == 0); //wait to receive lower wall encoder bits from dsPIC
	if (uart0RxAvailable() != 0) {
		rxbuffer[0] = uart0RxReceiveByte(); //receive lower wall encoder bits
	}
	delayMs(1);
	uart0TxSendByte(UPPER_WALL); //send 4 for upper wall encoder bits
	while (uart0RxAvailable() == 0); //wait to receive upper wall encoder bits from dsPIC
	if (uart0RxAvailable() != 0) {
		rxbuffer[1] = uart0RxReceiveByte(); //receive upper wall encoder bits
	}
	data = 0;
	data = rxbuffer[1] << 8; //bit shift upper wall encoder bits
	data |= rxbuffer[0]; //or data with lower wall encoder bits to get full wall encoder value
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
	
	
	



