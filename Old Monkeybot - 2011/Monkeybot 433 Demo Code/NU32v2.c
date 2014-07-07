#include <plib.h>
#include "NU32v2.h"

// Initialize LEDs on G12 and G13 as output and the switch on G6 as input
// G6 has an internal pullup resistor enabled by the bootloader
void initLEDs(void) {
  TRISGCLR = 0x3000; TRISGSET = 0x0040;				
}

// Initialize the serial port 
// Note: the NU32v2 is hard wired to use UART3 (= UART2A)
void initSerialNU32v2() {
  int pbClk;
  // Configure the system performance
  pbClk = SYSTEMConfigPerformance(SYS_FREQ); 

  UARTConfigure(UART3, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetFifoMode(UART3, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART3, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART3, pbClk, DESIRED_BAUDRATE_NU32);
  UARTEnable(UART3, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

  // Configure UART3 RX Interrupt
  INTEnable(INT_U3RX, INT_ENABLED);
  INTSetVectorPriority(INT_UART_3_VECTOR, INT_PRIORITY_LEVEL_2);
  INTSetVectorSubPriority(INT_UART_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
}

// Write a string over the serial port
void WriteString(UART_MODULE id, const char *string) {
  while(*string != '\0') {
  while(!UARTTransmitterIsReady(id));
  UARTSendDataByte(id, *string);
  string++;
  while(!UARTTransmissionHasCompleted(id));
  }
}

// Put a character over the serial port, called by WriteString
void PutCharacter(UART_MODULE id, const char character) {
  while(!UARTTransmitterIsReady(id));
  UARTSendDataByte(id, character);
  while(!UARTTransmissionHasCompleted(id));
}

void delaysec(int tref) {
	int t1 = timesec;
	while(timesec - t1 < tref) {};
}
