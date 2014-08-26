/** mycom_acrobot:

This app should be loaded onto the Wixel that is connecetd directly to the Acrobot. It processes commands recieved over radio from the Wixel plugged into the PC.
*/

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <radio_link.h>
#include <uart0.h>
#include <stdio.h>
#include <adc.h>

#define DELAY_MS 750

// these are commands that the wixel responds to
#define COMMAND_TOGGLE_YELLOW_LED 'y'
#define COMMAND_RESET_DSPIC 'q'
#define COMMAND_ENABLE_QEI 'e'
#define COMMAND_DISABLE_QEI 'd'
#define COMMAND_READ_QEI 'l'
#define COMMAND_SEND_T 't'
#define COMMAND_RUN_MOTOR 'r'
#define COMMAND_RUN_FASTER 'f'
#define COMMAND_RUN_SLOWER 's'
#define COMMAND_HALT_MOTOR 'h'
#define COMMAND_INVERT_DIRECTION 'i'
#define COMMAND_READ_ADC 'a'
/** The the initial compare value for PWM on timer 1.*/
#define MAX_COUNT 1200
/** Configures the CC2511 chip of the Wixel to use timer 1 in modulo mode.*/
#define MODULO_MODE 0b00000010

/* VARIABLES ******************************************************************/

/** True if the yellow LED should currently be on. */
BIT yellowLedOn = 0;
uint8 XDATA response[32];
uint16 compare = 1200;

/* FUNCTIONS ******************************************************************/

void updateLeds()
{
    usbShowStatusWithGreenLed();
    LED_YELLOW(yellowLedOn);
}

/** Processes a new byte received over either radio or UART. As currently configured,
* all bytes recieved over UART will be integer chars coming from the dsPIC (either ADC readings or encoder counts). These integers are
then sent over radio to another Wixel. 
* all bytes recieved over radio will be single letters from another Wixel specifying some command to run 
* (run motor, reverse direction, increase PWM duty cycle etc... ). 
* */

void processByte(uint8 c)
{
    uint8 XDATA *tmt;
	uint8 read;
	uint16 adcValue;
	uint8 length;
	char XDATA buffer [32];

    switch(c) {
    // these cases handle encoder readings; a better
    // implementation would use sscanf in the processBytesUart0
    // function
    case '0':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '0'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '1':
    	tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '1'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '2':
   		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '2'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '3':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '3'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '4':
   		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '4'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '5':
   		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '5'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
	
    case '6':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '6'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '7':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '7'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '8':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '8'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '9':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '9'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '\r':
		tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '\r'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case '\n':
        tmt = radioLinkTxCurrentPacket();
        if(tmt != NULL) {
            tmt[0] = 1; // payload length
            tmt[1] = '\n'; // payload data
            radioLinkTxSendPacket(0);
        }
		break;
		
    case COMMAND_TOGGLE_YELLOW_LED:
        yellowLedOn ^= 1;
        break;
		
	case COMMAND_RESET_DSPIC:
        uart0TxSendByte(COMMAND_RESET_DSPIC);
		break;
		
	case COMMAND_ENABLE_QEI:
		uart0TxSendByte(COMMAND_ENABLE_QEI);
		break;
		
	case COMMAND_DISABLE_QEI:
		uart0TxSendByte(COMMAND_DISABLE_QEI);
		break;
		
	case COMMAND_READ_QEI:
		uart0TxSendByte(COMMAND_READ_QEI);
		break;
		
	case COMMAND_SEND_T:
		uart0TxSendByte(COMMAND_SEND_T);
    	break;
		
	case COMMAND_RUN_MOTOR:
		T1CC2 = compare;
		yellowLedOn ^= 1;
		break;
	
	case COMMAND_HALT_MOTOR:
		T1CC2 = 1200;
		yellowLedOn ^= 1;
		break;
		
	case COMMAND_RUN_FASTER:
		if (compare > 50){
			compare = compare - 50;
			T1CC2 = compare;
		}
		break;
		
	case COMMAND_RUN_SLOWER:
		if (compare < 1150){
			compare = compare +50;
			T1CC2 = compare;
		}
		break;
	
	case COMMAND_INVERT_DIRECTION:
		yellowLedOn ^= 1;
		read = isPinHigh(16);
		P1_6=!read;
		break;
		
	case COMMAND_READ_ADC:
		adcValue = adcRead(1); // | ADC_REFERENCE_INTERNAL); - if we want to use 1.25 V reference
		length = sprintf(buffer,"%5u \n",adcValue);
	
    tmt = radioLinkTxCurrentPacket();
    if(tmt != NULL) {
        tmt[0] = length; // payload length
        tmt[1] = buffer[1]; // payload data
		tmt[2] = buffer[2]; // payload data
		tmt[3] = buffer[3]; // payload data
		tmt[4] = buffer[4]; // payload data
		tmt[5] = buffer[5]; // payload data
		tmt[6] = buffer[6]; // payload data
        radioLinkTxSendPacket(0);
    }
	break;
				
		 


    }
}


/** Checks for new bytes available from the wireless radio
 * and processes all that are available. */
void processBytesFromRadio()
{
    uint8 i, n;
    uint8 XDATA *rcv;
    
    rcv = radioLinkRxCurrentPacket();
    if(rcv != NULL) {
        n = rcv[0]; // payload length
        for(i = 1; i <= n && radioLinkTxAvailable(); i++) {
            processByte(rcv[i]);
        }
        radioLinkRxDoneWithPacket();
    }
}

/** Checks for new bytes available on UART0
 * and processes all that are available. */
void processBytesFromUart0()
{
    // this code should be modified to use sscanf.
    uint8 bytesLeft = uart0RxAvailable();
    while(bytesLeft && uart0TxAvailable() >= sizeof(response))
    {
        processByte(uart0RxReceiveByte());
        bytesLeft--;
    }
}

/** Configures the timer 1 registers and UART and radio communation, then calls the 
* processBytesFromRadio and processBytesFromUart functions.
**/
void main()
{
    // required by wixel api:
    // http://pololu.github.io/wixel-sdk/group__libraries.html
    systemInit();
    radioLinkInit();
    uart0Init();
	
	P1SEL |= 0<<6;
	P1DIR |= 1<<6;
	P1_6=0;
	
	T1CTL = MODULO_MODE; // start timer 1 with no prescaler in modulo mode
	
	T1CCTL1 = 0b00011100; // channel 1 - set output on compare-up, clear on 0 
	T1CCTL2 = 0b00100100; // channe 2 - clear output on compare-up, set on 0 
	
	// Set the overflow to 1200, giving us a frequency of 20kHz
	T1CC0 = MAX_COUNT;
	
	// set compare for both channels
	T1CC1 = 0; // 100% duty cycle
	
	T1CC2 = 1200; // 100% duty cycle

    // Configure Timer 1 to use Alternative 2 location.
	PERCFG |= 0b01000000; 

    // Configure P1_0 and P1_1 to be controlled by a peripheral function (Timer 1)
    // instead of being general purpose I/O.
    P1SEL |= (1<<0) | (1<<1);

    // After calling this function, you can set the duty cycles by simply writing
    // to T1CC1 and T1CC0.

    // set uart
    uart0SetBaudRate(9600);
    uart0SetParity(PARITY_NONE);
    uart0SetStopBits(STOP_BITS_1);

    // wait for a wireless pairing
    // between two wixels
    // blink yellow LED while connection is being established
    while(!radioLinkConnected()) {
        yellowLedOn ^= 1;
        updateLeds();
        delayMs(DELAY_MS);
    }

    // turn off LED
    yellowLedOn = 0;

    // process bytes
    while(1)
    {
        boardService();
        updateLeds();
        processBytesFromRadio();
        processBytesFromUart0();
    }
}
