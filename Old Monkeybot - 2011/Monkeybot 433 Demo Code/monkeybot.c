// Monkeybot code

#include <plib.h>
#include <math.h>
#include "NU32v2.h"
#include "7366.h"

// global variables
int HBridgeDuty;
unsigned char readbuf[COUNTER_BYTES];
int start=0;
int delay1=5;
int delay2=10;
int delay3=3;


int main(void) {
	timesec=0;
	// set PIC32 to max computing power
	SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableSystemMultiVectoredInt();   
    initLEDs(); 	
    LED0 = 1;
    LED1 = 1;
    initSerialNU32v2();
	setup_counters();

  	CloseADC10();
  	#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
  	#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_16 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
  	#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_31
  	#define PARAM4  ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN5_ANA | ENABLE_AN15_ANA
  	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4,0);
  	EnableADC10();


    // Setup and turn off electromagnets
    EMAG1 = 0; EMAG2 = 0; 
    TRISEbits.TRISE7 = 0; TRISCbits.TRISC1 = 0;
	//Direction Output
	DIR = 1;
  	TRISAbits.TRISA9 = 0;
	//g-select Outputs
	GSEL1 = 0; GSEL2 = 0;
  	TRISEbits.TRISE2 = 0; TRISCbits.TRISC13= 0;
  	//0g Inputs
  	TRISAbits.TRISA0 = 1;
  	TRISAbits.TRISA4 = 1;

  	// 20kHz PWM signal, duty from 0-1000, pin D3
  	OpenTimer2(T2_ON | T2_PS_1_4, 1000);
  	OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
  	HBridgeDuty = 0;
  	SetDCOC4PWM(HBridgeDuty);

    // 20Hz ISR
    OpenTimer3(T3_ON | T3_PS_1_256, 15625);
    mT3SetIntPriority(1);
    mT3ClearIntFlag();
    mT3IntEnable(1);


	while(1) {
		if(start){
			EMAG2=0;
			SetDCOC4PWM(100);
			delaysec(delay1);
			SetDCOC4PWM(1000);		
			delaysec(delay2);
			SetDCOC4PWM(500);
			delaysec(delay3);
			EMAG2=1;
			SetDCOC4PWM(0);	

//			EMAG1=0;
//			SetDCOC4PWM(900);
//			DIR = 0;
//			delaysec(delay1);
//			SetDCOC4PWM(0);
//			delaysec(delay2);
//			SetDCOC4PWM(700);
//			delaysec(delay1);
//			SetDCOC4PWM(1000);
//			EMAG1=1;

			start=0;
		}
	}
}


// timer3 ISR
// Read the encoder, and send over the data desired by printMode
void __ISR( _TIMER_3_VECTOR, ipl1) T3Interrupt( void) {
	timesec++;

	int counterval1;
    int counterval2;

	if(!start) {

//	read_7366(MOT, CNTR, readbuf);
//	counterval1 = (((int)(readbuf[0]))<<8) | ((int)(readbuf[1]));	
//
//	read_7366(MAG1, CNTR, readbuf);
//	counterval2 = (((int)(readbuf[0]))<<8) | ((int)(readbuf[1]));
	
	counterval1 = (int)(atan2(((float)ACC1X-505.0),((float)ACC1Y-530.0))*180.0/3.1416);
    
	counterval2 = (int)(atan2(((float)ACC2X-505.0),((float)ACC2Y-530.0))*180.0/3.1416);

	sprintf(RS232_Out_Buffer,"%i %i %i %i %i\r\n", counterval1, counterval2, delay1,delay2, delay3);
  	WriteString(UART3, RS232_Out_Buffer);

	}

	else {	

	counterval1 = GYRO1HI;
	counterval2 = GYRO2HI;

	sprintf(RS232_Out_Buffer,"%i %i\r\n", counterval1, counterval2);
  	WriteString(UART3, RS232_Out_Buffer);
	
	}	
	
	// clear interrupt flag and exit
	mT3ClearIntFlag();
}


// UART3 interrupt handler, priority level 2
void __ISR(_UART_3_VECTOR, ipl2) IntUart3Handler(void) {
  // Is this an RX interrupt?
  if(INTGetFlag(INT_SOURCE_UART_RX(UART3))){
    char data = UARTGetDataByte(UART3);

    LED1 = !LED1;

	if(data =='x') {
		//Stop program, both magnets ON
		start = 0;
		EMAG1 = EMAG2 = 1;
	}
	
    if(data =='e') {
       // Magnet 1 ON
       EMAG1 = 1;
    }

    if(data =='f') {
       // Magnet 1 OFF
       EMAG1 = 0;
    }

    if(data =='g') {
       // Magnet 2 ON
       EMAG2 = 1;
    }

    if(data =='h') {
       // Magnet 2 OFF
       EMAG2 = 0;
    }

	if(data =='s') {
		// start motion program
		start = 1;
		LED0=0;
	}
    if(data =='o') {
        delay1 = delay1+1;
	}
	if(data =='p') {
        delay1 = delay1-1;
	}
	if(data =='k') {
        delay2 = delay2+1;
	}
	if(data =='l') {
        delay2 = delay2-1;
	}
	if(data =='n') {
        delay3 = delay3+1;
	}
	if(data =='m') {
        delay3 = delay3-1;
	}


    // Clear the RX interrupt Flag
    INTClearFlag(INT_SOURCE_UART_RX(UART3)); 
  }

  // We don't care about TX interrupt
  if(INTGetFlag(INT_SOURCE_UART_TX(UART3))) {
    INTClearFlag(INT_SOURCE_UART_TX(UART3));
  }
}
