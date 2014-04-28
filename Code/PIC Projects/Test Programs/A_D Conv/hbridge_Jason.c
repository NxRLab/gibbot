#if 0
#include <plib.h>
#include "NU32_2012.h"

#define DIRECTION LATDbits.LATD1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0
#define DUTYCYCLE OC1RS


  // interrupt when the NU32 gets a character from the computer
  void __ISR(_UART_2_VECTOR, ipl2) IntUart1Handler(void) {
  // Is this an RX interrupt?
  if (INTGetFlag(INT_SOURCE_UART_RX(UART2))) {

    char data = UARTGetDataByte(UART2);
LATDbits.LATD0=1;
 //   if (data == 0x61) //"a")
  //  {
 //       LATDbits.LATD0=1-LATDbits.LATD0;
  //  }
    // Clear the RX interrupt Flag
    INTClearFlag(INT_SOURCE_UART_RX(UART2));
  }

  // We don't care about TX interrupt
  if (INTGetFlag(INT_SOURCE_UART_TX(UART2))) {
    INTClearFlag(INT_SOURCE_UART_TX(UART2));
  }
}


void main(void) {
    NU32_Startup();
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0=0;
    INTSetFlag(INT_SOURCE_UART_TX(UART2));
 //   TRISDbits.TRISD5 = 1;
 //   int t=1;
 //   while(t<100)
 //   {   t=t+1;
 //       UARTSendDataByte(UART1,0x61);}

 //      while (1)
 //   {
 //   int data = UARTGetDataByte(UART2);
 //   if (LATDbits.LATD5==0)
 //   {
 //       LATDbits.LATD0=1-LATDbits.LATD0;
 //   }
    
 //   }
/*

    DIRECTION = CLOCKWISE;
    TRISD = 0;

    T2CONbits.ON = 0x0;
    TMR2 = 0;
    PR2 = 999;

    OC1CONbits.ON = 0;
 //   OC1R = 500;
    DUTYCYCLE = 500; //duty cycle 0.5
    OC1CON = 0x6; //pwm with fault pin off


    T2CONbits.ON = 1;
    OC1CONbits.ON = 1;
*/
    while (1);
}
#endif