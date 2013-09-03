#include <plib.h>
#include "math.h"
#include "data.h"
#include "library.h"
#include "7366.h"

int main(void)
{
    // initalize global variables
    start = 0;
    delay1 = 5;
    delay2 = 10;
    delay3 = 3;
    timesec = 0;

    startupPIC();
    initalizePIC();
    setup_counters();

    initAnalogInput();
    initMagnets();


    while(1) {
        if(start) {
            EMAG2=0;
            SetDCOC4PWM(100);
            delaysec(delay1);
            SetDCOC4PWM(1000);
            delaysec(delay2);
            SetDCOC4PWM(500);
            delaysec(delay3);
            EMAG2=1;
            SetDCOC4PWM(0);

//            EMAG1=0;
//            SetDCOC4PWM(900);
//            DIR = 0;
//            delaysec(delay1);
//            SetDCOC4PWM(0);
//            delaysec(delay2);
//            SetDCOC4PWM(700);
//            delaysec(delay1);
//            SetDCOC4PWM(1000);
//            EMAG1=1;

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
//        read_7366(MOT, CNTR, readbuf);
//        counterval1 = (((int)(readbuf[0]))<<8) | ((int)(readbuf[1]));
//
//        read_7366(MAG1, CNTR, readbuf);
//        counterval2 = (((int)(readbuf[0]))<<8) | ((int)(readbuf[1]));

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
    if(INTGetFlag(INT_SOURCE_UART_RX(UART3))) {
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
