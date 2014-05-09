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
    //systemInit();
	boardIoInit();
	boardClockInit();
	dmaInit();
    usbInit();
	radioLinkInit();
	receive=radioLinkRxCurrentPacket();
	send=radioLinkTxCurrentPacket();
	
	while (radioLinkRxCurrentPayloadType()!=10)
	{
		boardService();
		usbShowStatusWithGreenLed();
		usbComService();
		radioLinkRxDoneWithPacket();
	}
	
	timer4Init();
	timer3Init();
	motion_init();
	while (1)
	{
		boardService();
        usbShowStatusWithGreenLed();
		usbComService();
		
		if (receive[0]!=0)
		{
			if (radioLinkRxCurrentPayloadType()==15)
			{
				shutdown();
			}
			
			else if (radioLinkRxCurrentPayloadType()==10)
			{
				start_up();
			}
			else if (radioLinkRxCurrentPayloadType()==11)
			{
				if (send!=0)
				{
					uint16 currentsend;
					currentsend=current_amps_get();
					send[0]=2;
					send[1]=(currentsend>>8);
					send[2]=(currentsend&0xFF);
					radioLinkTxSendPacket(11);
					send[0]=2;
					send[1]=(currentsend>>8);
					send[2]=(currentsend&0xFF);
					radioLinkTxSendPacket(11);
				}
			}
		}
		radioLinkRxDoneWithPacket();

	}
}