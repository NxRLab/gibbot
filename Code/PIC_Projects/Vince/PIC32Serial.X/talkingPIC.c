/**
 * This code enables a PIC32 to act as a pass-through serial port for the
 * Gibbot dsPIC.  This is a modified version of talkingPIC.c.  This code is
 * extended, so that UART2 is enabled.  Both UART1 and UART2 have RX interrupts
 * enabled.  RX bytes from UART1 (i.e., a PC) are sent to UART2's TX register.
 * RX interrupts from UART2 (i.e., data from the dsPIC) are sent to UART1's TX
 * register.
 *
 * Make sure to connect XBEE ground to PIC32 ground.  RX (F4) to XBEE TX
 * and TX (F5) to XBEE RX.  Do not connect any other pins.
 */

#define NU32_STANDALONE  // uncomment if program is standalone, not bootloaded
#include "NU32.h"          // config bits, constants, funcs for startup and UART

#define LED_OFF 1
#define MAX_MESSAGE_LENGTH 200

int main(void) {
  char message[MAX_MESSAGE_LENGTH];

  NU32_EnableUART1Interrupt();
  NU32_EnableUART2WithInterrupt(); // // UART2 RX - pin F4, TX - pin F5
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  
  NU32_LED1 = LED_OFF;
  NU32_LED2 = LED_OFF;

  sprintf(message, "Gibbot Serial v0.1; Hello World!\r\n");
  NU32_WriteUART1(message);

  while (1);
  return 0;
}
