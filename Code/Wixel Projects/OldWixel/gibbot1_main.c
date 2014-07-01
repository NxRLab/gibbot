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

//static uint8 i=0;
//static uint8 j=255;
/*static int e=0,eint=0,u=0,kp=0,ki=0,Currentref=0;

ISR(T4,0)
{
	uint32 y, adcvalue;
    uint16 ucycle;
	
	ucycle=0;
    adcvalue=adcRead(0);
    y=(adcvalue*(256))>>11;
	e = Currentref - adcvalue;
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
	}
	
    // Set the duty cycle on channel 0 (P1_3) to 210/256 (82.0%).
    T3CC0 = ucycle;
	
    // Make the duty cycle on channel 1 (P1_4) vary smoothly up and down.
    T3CC1 = ucycle;
	
	
	T4IF = 0;
}*/
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
}



void updatePwm()
{
	uint32 y, adcvalue;
	

    //adcvalue=adcRead(0);
    //y=(adcvalue*(256))>>11;
	// Set the duty cycle on channel 0 (P1_3) to 210/256 (82.0%).
    T3CC0 = 256;

    // Make the duty cycle on channel 1 (P1_4) vary smoothly up and down.
    T3CC1 = 0;
}

void main()
{
	//const uint8 XDATA txbuffer[2]={1,2};
	//uint8 XDATA rxbuffer[2];
	uint8 XDATA usbbuffer[32];
	uint8 length, usbreceive=0;
	//uint16 data;
	uint16 menc,wenc,wenc1;
	int16 wallang,direction,mang;
	uint16 ADCRead,readADC,readMv,readMa;
	uint8 XDATA* sendmotor;
	//uint8 XDATA* receive;
    systemInit();
    usbInit();
    timer3Init();
	radioLinkInit();
	ADCCFG=0b00000001;
	
	uart0Init();
	uart0SetParity(PARITY_NONE);
	uart0SetBaudRate(9600);
	//T4IF = 0;
	//T4IE = 1;
	
	//delayMs(10);
	
	while(1)
    {
		boardService();
        usbShowStatusWithGreenLed();
       // updatePwm();
		wenc = wall_encoder_read();
		menc = motor_encoder_read();
		wallang=((((float)wall_encoder_read()-32768)*360)/8194);
		mang=((((float)motor_encoder_read()-32768)*360)/39000);
		direction = wenc - wenc1;
		/*receive=radioLinkRxCurrentPacket();
		
		if (receive[0]!=0)
		{
			if (radioLinkRxCurrentPayloadType()==0)
			{
				sendmotor = radioLinkTxCurrentPacket();
				if (sendmotor != 0)
				{
				/*sendmotor[0]=2;
				sendmotor[1]=menc>>8;
				sendmotor[2]=menc&0xFF;
				radioLinkTxSendPacket(0);*/
					/*sendmotor[0]=1;
					sendmotor[1]=i;
					radioLinkTxSendPacket(0);
					radioLinkRxDoneWithPacket();
					i++;
				}
			}
			else if (radioLinkRxCurrentPayloadType()==1)
			{
				sendmotor = radioLinkTxCurrentPacket();
				if (sendmotor != 0)
				{
				/*sendmotor[0]=2;
				 sendmotor[1]=menc>>8;
				 sendmotor[2]=menc&0xFF;
				 radioLinkTxSendPacket(0);*/
					/*sendmotor[0]=1;
					sendmotor[1]=j;
					radioLinkTxSendPacket(1);
					radioLinkRxDoneWithPacket();
					j--;
				}
			}
		}
		else 
		{
			radioLinkRxDoneWithPacket();
		}*/

		/*length=sprintf(usbbuffer,"%x %u %x %u %i %i %i\r\n",wenc,wenc,menc,menc,wallang,mang,direction);
		usbComTxAvailable();
		usbComTxSend(usbbuffer,length);*/
		ADCRead=adcRead(0);
		readADC=ADCRead;
		/*if (ADCRead<557){
			readADC=0;
		}
		else {
			readADC=ADCRead-557;
		}*/
		readMv=((float)readADC/2047)*3300;
		readMa=((float)readMv/440)*1000;
		//length=sprintf(usbbuffer,"%u %u %u\r\n",readADC,readMv,readMa);
		//usbComTxAvailable();
		//usbComTxSend(usbbuffer,length);
		sendmotor=radioLinkTxCurrentPacket();
		if (sendmotor!=0)
		{
			sendmotor[0]=1;
			sendmotor[1]='a';
			//readADC;
			/*sendmotor[2]=readMv;
			sendmotor[3]=readMa>>8;
			sendmotor[4]=readMa&0xFF;*/
			radioLinkTxSendPacket(1);
		}
		
		//usbComService();
		wenc1 = wenc;
		
	/*	if (usbComRxAvailable() != 0)
		{
			usbreceive=usbComRxReceiveByte();
		}
		
		if (usbreceive == 32)
		{
			wall_encoder_reset();
			motor_encoder_reset();
			usbreceive=0;
		}*/
		
	}
}