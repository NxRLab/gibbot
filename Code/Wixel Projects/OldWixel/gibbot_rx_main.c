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

#define START '1'
#define CURRENT '2'
#define ANGLE '3'
#define MOTOR_ANGLE 'a'
#define WALL_ANGLE 'b'
#define MOTOR_ANGLE_RESET 'c'
#define WALL_ANGLE_RESET 'd'
#define RESET_ALL 'e'
#define GAINS '4'
#define STOP '5'

void main()
{
	uint8 XDATA* send;
	uint8 XDATA* receive;
	uint8 XDATA usbbuffer[32];
	uint8 length;
	uint8 usbreceive = 0;
	
	systemInit();
    usbInit();
	radioLinkInit();
			
	while (1) 
	{
		boardService();
		usbShowStatusWithGreenLed();
		usbComService();
		send = radioLinkTxCurrentPacket();
		receive = radioLinkRxCurrentPacket();
					
		
		if (usbComRxAvailable() != 0)
		{
			usbreceive=usbComRxReceiveByte();
		}
		
		if (usbreceive == 32) //spacebar brings up menu
		{
			length=sprintf(usbbuffer,"Menu:\r\n 1: Start\r\n 2: Current\r\n 3: Angle\r\n 4: Gains\r\n 5: Stop\r\n\r\n");
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
		}
		
		else if (usbreceive == START) //keyboard 1
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
		
		else if (usbreceive == CURRENT) //keyboard 2
		{
			if (send!=0)
			{
				send[0]=1;
				send[1]=1;
				radioLinkTxSendPacket(11);
			}
			while (receive[0] == 0)
			{
				usbComService();
				if (usbComRxReceiveByte() == 32)
				{
					break;
				}
			}
			if (receive[0] != 0)
			{
				uint16 value;
				value = receive[1] << 8;
				value |= receive[2];
				length = sprintf(usbbuffer,"%u CURRENT = %u mA\r\n",2,value);
				usbComTxAvailable();
				usbComTxSend(usbbuffer,length);
				radioLinkRxDoneWithPacket();
			}
		}
		
		else if (usbreceive == ANGLE) //keyboard 3
		{
			length=sprintf(usbbuffer,"%u ANGLE\r\n",3);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			length=sprintf(usbbuffer," a: MOTOR ANGLE\r\n b: WALL ANGLE\r\n c: RESET MOTOR ANGLE\r\n d: RESET WALL ANGLE\r\n e: RESET ALL\r\n");
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			while (usbComRxAvailable()==0)
			{
				usbComService();
			}
			if (usbComRxAvailable()!=0)
			{
				usbreceive=usbComRxReceiveByte();
				if (usbreceive == MOTOR_ANGLE) //keyboard a
				{
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(12);
					}
					while (receive[0] == 0)
					{
						usbComService();
						if (usbComRxReceiveByte() == 32)
						{
							break;
						}
					}
					if (receive[0] != 0)
					{
						int16 value;
						value = receive[1] << 8;
						value |= receive[2];
						if (receive[3] == 1)
						{
							value = -1 * value;
						}
						length=sprintf(usbbuffer,"%c MOTOR ANGLE = %i DEGREES\r\n",'a',value);
						usbComTxAvailable();
						usbComTxSend(usbbuffer,length);						
						radioLinkRxDoneWithPacket();
					}
				}
				else if (usbreceive == WALL_ANGLE) //keyboard b
				{
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(13);
					}
					while (receive[0] == 0)
					{
						usbComService();
						if (usbComRxReceiveByte() == 32)
						{
							break;
						}
					}
					if (receive[0] != 0)
					{
						int16 value;
						value = receive[1] << 8;
						value |= receive[2];
						if (receive[3] == 1)
						{
							value = -1 * value;
						}						
					length=sprintf(usbbuffer,"%c WALL ANGLE = %i DEGREES\r\n",'b',value);
					usbComTxAvailable();
					usbComTxSend(usbbuffer,length);
					radioLinkRxDoneWithPacket();
					}
				}
				else if (usbreceive ==  MOTOR_ANGLE_RESET) //keyboard c
				{
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(2);
					}
				}
				else if (usbreceive ==  WALL_ANGLE_RESET) //keyboard d
				{
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(3);
					}
				}
				else if (usbreceive == RESET_ALL) //keyboard e
				{
					if (send!=0)
					{
						send[0]=1;
						send[1]=1;
						radioLinkTxSendPacket(4);
					}
				}
			}
		}
		
		else if (usbreceive == GAINS) //keyboard 4
		{
		}
			
		else if (usbreceive == STOP) //keyboard 5
		{
			length=sprintf(usbbuffer,"%u STOP\r\n",5);
			usbComTxAvailable();
			usbComTxSend(usbbuffer,length);
			
			if (send!=0)
			{
				send[0]=1;
				send[1]=1;
				radioLinkTxSendPacket(15);
			}
			
		}		
			usbreceive=0;
	}
}