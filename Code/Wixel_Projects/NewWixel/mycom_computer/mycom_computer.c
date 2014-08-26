/** mycom_acrobot:

This app should be loaded onto the Wixel that is connected directly to the PC. It sends commands over radio to the Wixel that is connecetd directly to the Acrobot.
*/

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <radio_link.h>
#include <stdio.h>

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

/* VARIABLES ******************************************************************/

/** True if the yellow LED should currently be on. */
BIT yellowLedOn = 0;


/** A temporary buffer used for composing responses to the computer before
 * they are sent.  Must be bigger than the longest possible response to any
 * command.
 */
uint8 XDATA response[32];

/* FUNCTIONS ******************************************************************/

void updateLeds()
{
    usbShowStatusWithGreenLed();
    LED_YELLOW(yellowLedOn);
}

/** Processes a new byte received over either radio or USB. As currently configured,
* all bytes recieved over radio will be integer chars coming from another Wixel (either ADC readings or encoder counts).
* All bytes recieved over USB will be single letters from a PC specifying some command to run 
* (run motor, reverse direction, increase PWM duty cycle etc... ). These commands are sent over radio to another Wixel 
* when they are received. 
* */

void processByte(uint8 c)
{
    uint8 XDATA *tmt;

    switch(c) {
    // these cases handle encoder readings; a better
    // implementation would use sscanf in the processBytesUart0
    // function
	    case '0':
	    	usbComTxSendByte(c);
	    	break;
	    case '1':
	    	usbComTxSendByte(c);
	    	break;
	    case '2':
	    	usbComTxSendByte(c);
	    	break;
	    case '3':
	    	usbComTxSendByte(c);
	    	break;
	    case '4':
	    	usbComTxSendByte(c);
	    	break;
	    case '5':
	    	usbComTxSendByte(c);
	    	break;
	    case '6':
	    	usbComTxSendByte(c);
	    	break;
	    case '7':
	    	usbComTxSendByte(c);
	    	break;
	    case '8':
	    	usbComTxSendByte(c);
	    	break;
	    case '9':
	    	usbComTxSendByte(c);
	    	break;
	    case '\r':
	    	usbComTxSendByte(c);
	    	break;
		case '\n':
		 	usbComTxSendByte(c);
		 	break;

    // just in case we can't print anything to screen
    // this command allows for a visual that we are
    // at least getting serial commands
    case COMMAND_TOGGLE_YELLOW_LED:
        yellowLedOn ^= 1;
        break;

		
	case COMMAND_RESET_DSPIC:
    	tmt = radioLinkTxCurrentPacket();
    	if(tmt != NULL) {
        	tmt[0] = 1; // payload length
        	tmt[1] = COMMAND_RESET_DSPIC; // payload data
        	radioLinkTxSendPacket(0);
    	}
		break;
		
	case COMMAND_ENABLE_QEI:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
    		tmt[0] = 1; // payload length
    		tmt[1] = COMMAND_ENABLE_QEI; // payload data
    		radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_DISABLE_QEI:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_DISABLE_QEI; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_READ_QEI:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_READ_QEI; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_SEND_T:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_SEND_T; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_RUN_MOTOR:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_RUN_MOTOR; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_HALT_MOTOR:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_HALT_MOTOR; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_RUN_FASTER:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_RUN_FASTER; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
		
	case COMMAND_RUN_SLOWER:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_RUN_SLOWER; // payload data
			radioLinkTxSendPacket(0);
		}
		break;
			
		
	case COMMAND_INVERT_DIRECTION:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_INVERT_DIRECTION; // payload data
			radioLinkTxSendPacket(0);
			yellowLedOn ^= 1;
		}
		break;
		
	case COMMAND_READ_ADC:
		tmt = radioLinkTxCurrentPacket();
		if(tmt != NULL) {
			tmt[0] = 1; // payload length
			tmt[1] = COMMAND_READ_ADC; // payload data
			radioLinkTxSendPacket(0);
			yellowLedOn ^= 1;
		}
		break;
		
    }
}

/** Checks for new bytes available on the USB virtual COM port
 * and processes all that are available. */
void processBytesFromUsb()
{
    uint8 bytesLeft = usbComRxAvailable();
    while(bytesLeft && usbComTxAvailable() >= sizeof(response))
    {
        processByte(usbComRxReceiveByte());
        bytesLeft--;
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

/** Configures the USB and radio communication then calls the processBytesFromUsb and 
* processBytesFromRadio functions. 
**/
void main()
{
    // required by wixel api:
    // http://pololu.github.io/wixel-sdk/group__libraries.html
    systemInit();
    usbInit();
    radioLinkInit();


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
        usbComService();
        processBytesFromUsb();
        processBytesFromRadio();
  
    }
}
