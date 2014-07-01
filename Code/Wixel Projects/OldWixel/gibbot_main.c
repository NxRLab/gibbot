/*
 *  gibbot_main.c
 *  
 *
 *  Created by Matt Collins on 5/2/14.
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
#include "gibbot_current.h"
#include "gibbot_motion.h"

void main()
{
	uint8 XDATA* receive;
	uint8 XDATA* send;
	boardIoInit();
	boardClockInit();
	dmaInit();
    usbInit();
	usbComService();
	radioLinkInit();
	uart0Init();
	uart0SetParity(PARITY_NONE);
	uart0SetBaudRate(9600);
	receive = radioLinkRxCurrentPacket();
	send = radioLinkTxCurrentPacket();
	
	/*while (radioLinkRxCurrentPayloadType()!=10)
	{
		boardService();
		usbShowStatusWithGreenLed();
		usbComService();
		radioLinkRxDoneWithPacket();
	}*/
	
	timer4Init();
	timer3Init();
	motion_init();
	while (1)
	{
		boardService();
        usbShowStatusWithGreenLed();
		usbComService();
		if (receive[0] != 0)
		{
			if (radioLinkRxCurrentPayloadType() == 15)
			{
				shutdown_movement();
				radioLinkRxDoneWithPacket();
			}
			
			else if (radioLinkRxCurrentPayloadType() == 10)
			{
				start_up_movement();
				radioLinkRxDoneWithPacket();
			}
			else if (radioLinkRxCurrentPayloadType() == 11)
			{
				if (send != 0)
				{
					uint16 currentsend;
					currentsend=current_amps_get();
					send[0] = 2;
					send[1] = (currentsend >> 8);
					send[2] = (currentsend & 0xFF);
					radioLinkTxSendPacket(11);
				}
				radioLinkRxDoneWithPacket();
			}
			else if (radioLinkRxCurrentPayloadType() == 12)
			{
				if (send != 0)
				{
					int16 motorangle;
					uint16 motoranglesend;
					motorangle = motor_angle();
					send[0] = 3;
					if (motorangle < 0)
					{
						send[3] = 1;
						motoranglesend = -1 * motorangle;
					}
					else
					{
						send[3] = 0;
						motoranglesend = motorangle;
					}
					
					send[1] = (uint8) (motoranglesend >> 8);
					send[2] = (uint8) motoranglesend;
					radioLinkTxSendPacket(12);
				}		
				radioLinkRxDoneWithPacket();
			}
			else if (radioLinkRxCurrentPayloadType() == 13)
			{
				if (send != 0)
				{
					int16 wallangle;
					uint16 wallanglesend;
					wallangle = wall_angle();
					send[0] = 3;
					/*if (wallangle < 0)
					{
						send[3] = 1;
						wallanglesend = -1 * wallangle;
					}
					else
					{
						send[3] = 0;
						wallanglesend = wallangle;
					}*/
					send[3] = 0;
					send[1] = 0;
					//(uint8) (wallanglesend >> 8);
					send[2] = 0x5A;
					//(uint8) wallanglesend;
					radioLinkTxSendPacket(13);
				}		
				radioLinkRxDoneWithPacket();
			}
			
		}
		else if (radioLinkRxCurrentPayloadType() == 2)
		{
			motor_encoder_reset();
		}
		else if (radioLinkRxCurrentPayloadType() == 3)
		{
			wall_encoder_reset();
		}
		else if (radioLinkRxCurrentPayloadType() == 4)
		{
			motor_encoder_reset();
			wall_encoder_reset();
		}
	}
}