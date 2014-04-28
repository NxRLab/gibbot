#include <plib.h>
#include "NU32_2012.h"

#define DESIRED_BAUDRATE_NU32 230400 // Baudrate for RS232
#define tempDESIRED_BAUDRATE_NU32 38400 // Baudrate for RS232

// Private Buffers
char NU32_RS232OutBuffer[32]; // Buffer for sprintf in serial tx

/* Perform startup routines:
 * Make NU32LED1 and NU32LED2 pins outputs (NU32USER is by default an input)
 * Initialize the serial ports - UART1 (no interrupt) and UART4 (with interrupt)
 */
void NU32_Startup() {
  // set to maximum performance and enable all interrupts
  SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
  INTEnableSystemMultiVectoredInt();
  // disable JTAG to get A4 and A5 back
  DDPCONbits.JTAGEN = 0;

  TRISACLR = 0x0030; // Make A5 and A4 outputs (L2 and L1 on the silkscreen)
  NU32LED1 = 1; // L1 is off
  NU32LED2 = 0; // L2 is on

  // turn on UART1 without an interrupt
  UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY );
  UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART1, SYS_FREQ, DESIRED_BAUDRATE_NU32);
  UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

  // turn on UART4 with an interrupt
  UARTConfigure(UART4, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetFifoMode(UART4, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART4, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART4, SYS_FREQ, DESIRED_BAUDRATE_NU32);
  UARTEnable(UART4, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

  // Configure UART4 RX Interrupt
  INTEnable(INT_U4RX, INT_ENABLED);
  INTSetVectorPriority(INT_UART_4_VECTOR, INT_PRIORITY_LEVEL_3);
  INTSetVectorSubPriority(INT_UART_4_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
}

// Enable UART1 interrupt, so don't use NU32_ReadUART1 anymore
void NU32_EnableUART1Interrupt(void) {
  // turn off the module to change the settings
  UARTEnable(UART1, UART_ENABLE_FLAGS(UART_DISABLE));

  // Configure UART1 RX Interrupt
  UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY );
  UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART1, SYS_FREQ, DESIRED_BAUDRATE_NU32);
  UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
  INTEnable(INT_U1RX, INT_ENABLED);
  INTSetVectorPriority(INT_UART_1_VECTOR, INT_PRIORITY_LEVEL_2);
  INTSetVectorSubPriority(INT_UART_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);

  // Now you can use the following ISR in your main .c file:
  /*
  // interrupt when the NU32 gets a character from the computer
  void __ISR(_UART_1_VECTOR, ipl2) IntUart1Handler(void) {
  // Is this an RX interrupt?
  if (INTGetFlag(INT_SOURCE_UART_RX(UART1))) {

    char data = UARTGetDataByte(UART1);

    // do something with the data, like echo it back
    // PutCharacter(UART1,data); // echo

    // Clear the RX interrupt Flag
    INTClearFlag(INT_SOURCE_UART_RX(UART1));
  }

  // We don't care about TX interrupt
  if (INTGetFlag(INT_SOURCE_UART_TX(UART1))) {
    INTClearFcclag(INT_SOURCE_UART_TX(UART1));
  }
}
*/
}
///////////////////////////////////----------added-------------///////////////////////////////
void NU32_EnableUART2Interrupt(void) {
  // turn off the module to change the settings
  UARTEnable(UART2, UART_ENABLE_FLAGS(UART_DISABLE));

  // Configure UART2 RX Interrupt
  UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY );
  UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART2, SYS_FREQ, tempDESIRED_BAUDRATE_NU32);
  UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
  INTEnable(INT_U2RX, INT_ENABLED);
  INTSetVectorPriority(INT_UART_2_VECTOR, INT_PRIORITY_LEVEL_2);
  INTSetVectorSubPriority(INT_UART_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
}
///////////////////////////////////----------added-------------///////////////////////////////

// Disable UART1 interrupt, so you can use NU32_ReadUART1 again
void NU32_DisableUART1Interrupt(void) {
  // turn off the module to change the settings
  UARTEnable(UART1, UART_ENABLE_FLAGS(UART_DISABLE));

  // Configure UART1 RX Interrupt to off
  UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART1, SYS_FREQ, DESIRED_BAUDRATE_NU32);
  UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
  INTEnable(INT_U1RX, INT_DISABLED);
}

/* Read from UART1
 * block other functions until you get a '\r' or '\n'
 * send the pointer to your char array and the number of elements in the array
 */
void NU32_ReadUART1(char * message, int maxLength) {
  char data;
  int complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (UARTReceivedDataIsAvailable(UART1)) {
      data = UARTGetDataByte(UART1);
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        num_bytes++;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}

// Write a charater array using UART1
void NU32_WriteUART1(const char *string) {
  WriteString(UART1, string);
}

// Write a string over the serial port
void WriteString(UART_MODULE id, const char *string) {
  while (*string != '\0') {
    while (!UARTTransmitterIsReady(id));
    UARTSendDataByte(id, (char) *string);
    string++;
    while (!UARTTransmissionHasCompleted(id));
  }
}

// Put a character over the serial port, called by WriteString
void PutCharacter(UART_MODULE id, const char character) {
  while (!UARTTransmitterIsReady(id));
  UARTSendDataByte(id, character);
  while (!UARTTransmissionHasCompleted(id));
}

// do a software reset and go into bootloader mode if you get a 'B'
void __ISR(_UART_4_VECTOR, ipl3) IntUart4Handler(void) {
  // Is this an RX interrupt?
  if (INTGetFlag(INT_SOURCE_UART_RX(UART4))) {

    char data = UARTGetDataByte(UART4);

    NU32LED1 = !NU32LED1;
    NU32LED2 = !NU32LED2;

    if (data == 'B') {
      sprintf(NU32_RS232OutBuffer, "Switching to bootloader\r\n");
      WriteString(UART1, NU32_RS232OutBuffer);
      SoftReset();
    }

    // Clear the RX interrupt Flag
    INTClearFlag(INT_SOURCE_UART_RX(UART4));
  }

  // We don't care about TX interrupt
  if (INTGetFlag(INT_SOURCE_UART_TX(UART4))) {
    INTClearFlag(INT_SOURCE_UART_TX(UART4));
  }
}
