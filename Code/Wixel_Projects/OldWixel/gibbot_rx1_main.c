/*
 *  gibbot_rx_main.c
 *  
 *
 *  Created by Matt Collins on 4/11/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <radio_link.h>
#include <radio_com.h>
#include <radio_registers.h>
#include <radio_queue.h>
#include <radio_mac.h>
#include <stdio.h>
	
static uint8 i=0;

void main()
{
	uint8 XDATA* receive;
	uint8 XDATA* send;
	uint16 data1,data2;
	uint8 XDATA usbbuffer[32];
	uint8 length;
	
	systemInit();
    usbInit();
	radioLinkInit();
	
	while (1)
	{
		boardService();
		usbShowStatusWithGreenLed();
		
		usbComService();
		
		delayMs(100);
		
		/*send=radioLinkTxCurrentPacket();
		if (send!=0)
		{
			send[0]=1;
			send[1]=1;
			if (i==5)
			{
				radioLinkTxSendPacket(1);
				i=0;
			}
			else 
			{
				radioLinkTxSendPacket(0);
				i++;
			}
		}
		*/
		/*receive=radioLinkRxCurrentPacket();
		if (receive[0]!=0)
		{
			data1=0;
			//data1=receive[1]<<8;
			//data1|=receive[2];
			data1=receive[1];
			data2=0;
			//data2=receive[3]<<8;
			//data2|=receive[4];
			length=sprintf(usbbuffer,"%x %u %x %u\r\n",data1,data1,data2,data2);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			usbComService();
		}*/
		receive=radioLinkRxCurrentPacket();
		if (receive[0]!=0)
		{
			data1 = receive[1];
			//data1|=receive[4];
			length=sprintf(usbbuffer,"%c\r\n",data1);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			usbComService();
		}
		
		radioLinkRxDoneWithPacket();
		data1=0;
		usbComService();
	}
}