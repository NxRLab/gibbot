/*
 *  gibbot_rx_main.c
 *  
 *
 *  Created by Matt Collins on 5/5/14.
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

void main()
{
	uint8 XDATA* send;
	uint8 XDATA* receive;
	uint8 XDATA usbbuffer[32];
	uint8 length;
	uint8 usbreceive=0;
	
	systemInit();
    usbInit();
	radioLinkInit();
		
	delayMs(100);
	
	while (1) 
	{
		boardService();
		usbShowStatusWithGreenLed();
		usbComService();
		send=radioLinkTxCurrentPacket();
		receive=radioLinkRxCurrentPacket();
			
		
		if (usbComRxAvailable()!=0)
		{
			usbreceive=usbComRxReceiveByte();
		}
		
		if (usbreceive==32)
		{
			length=sprintf(usbbuffer,"Menu:\r\n 1: Start\r\n 2: Current\r\n 3: Angle\r\n 4: Stop\r\n\r\n");
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
		}
		
		if (usbreceive==49)
		{
			length=sprintf(usbbuffer,"%u START\r\n",1);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			
			if (send!=0)
			{
				send[0]=1;
				send[1]=1;
				radioLinkTxSendPacket(10);
			}
		}
		
		if (usbreceive==50)
		{
			if (send!=0)
			{
				send[0]=1;
				send[1]=1;
				radioLinkTxSendPacket(11);
			}
			/*usbComService();
			if (receive[0]!=0)
			{
				uint16 value;
				value=receive[1]<<8;
				value|=receive[2];
				length=sprintf(usbbuffer,"%u CURRENT = %u mA\r\n",2,value);
				usbComTxAvailable();
				usbComTxSend(usbbuffer,length);
				radioLinkRxDoneWithPacket();
			}*/
		}
		
		if (usbreceive==51)
		{
			length=sprintf(usbbuffer,"%u ANGLE\r\n",3);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			length=sprintf(usbbuffer," a: MOTOR ANGLE\r\n b: WALL ANGLE\r\n");
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			while (usbComRxAvailable()==0)
			{
				usbComService();
			}
			if (usbComRxAvailable()!=0)
			{
				usbreceive=usbComRxReceiveByte();
				if (usbreceive==97)
				{
					length=sprintf(usbbuffer,"%c MOTOR ANGLE = %u DEGREES\r\n",'a',3);
					usbComTxAvailable();
					usbComTxSend(usbbuffer,length);
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(12);
					}
				}
				else if (usbreceive==98)
				{
					length=sprintf(usbbuffer,"%c WALL ANGLE = %u DEGREES\r\n",'b',3);
					usbComTxAvailable();
					usbComTxSend(usbbuffer,length);
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(13);
					}
				}	
			}
		}
		
		if (usbreceive==52)
		{
			length=sprintf(usbbuffer,"%u STOP\r\n",4);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			
			if (send!=0)
			{
				send[0]=1;
				send[1]=1;
				radioLinkTxSendPacket(15);
			}
			
		}		
		/*if (receive[0]!=0)
		{
			if (radioLinkRxCurrentPayloadType()==11)
			{
				uint16 value;
				value=receive[1]<<8;
				value|=receive[2];
				length=sprintf(usbbuffer,"%u CURRENT = %u mA\r\n",2,value);
				usbComTxAvailable();
				usbComTxSend(usbbuffer,length);
				radioLinkRxDoneWithPacket();
			}
		}*/
		usbreceive=0;
	}
}