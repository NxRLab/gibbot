
/*
 * File:   SPI_23K256.c
 * Author: David J Meyer
 *
 * This code interfaces with the 23K256 SRAM chip by Microchip
 *
 * This code only uses the sequential mode, as other modes (page or byte) have
 * functionality that can also be done in sequential mode
 *
 *
 * PIC          MCP4922
 * SCK1      -> SCK
 * SDO1      -> SI
 * SDI1      -> SO
 * CS(A0)    -> CS
 * 3.3V      -> !HOLD (hold this pin HI)
 *
 * Created on December 12, 2012, 4:09 PM
 */

//LIBRARIES
#include <plib.h>
#include "NU32_2012.h"

//GLOBAL CONSTANTS

/* The 23K256 requires the use of a general purpose output pin to select
 * the slave device.
 *
 * CS: Chip Select, this pin drives low before writing data, and high otherwise
 *
 *
 */
#define CS      LATAbits.LATA0

//GLOBAL VARIABLES
char messageArray[64];

//FUNCTION PROTOTYPES
void initSRAM(void);
void writeToSRAM(int address, int data);
void readFromSRAM(int address);

//MAIN
int data1;
int data2;

int main(void) {

    int addr = 0x00FF;

    NU32_Startup();
    UARTSendDataByte(UART1,0x31);
    CS = 1;

    TRISACLR = 0x0001; // Set A0 as digital output;


    SPI1CON = 0; // Disable and reset SPI module
    SPI1BRG = 39; // Set the baudrate to (80MHz)/2/(39+1) = 1Mhz
    SPI1STATbits.SPIROV = 0; // Clear overflow flag

    SPI1CONbits.MSTEN = 1; // Enable Master Mode
    SPI1CONbits.MODE16 = 0;
    SPI1CONbits.MODE32 = 0; // 8 bit wide data
    SPI1CONbits.CKP = 0; // Clock is active high
    SPI1CONbits.CKE = 1; // Serial Data changes on active to idle
    SPI1CONbits.SMP = 1;
    SPI1CONbits.ON = 1; // Turn the SPI module on
    SPI1CONbits.MSSEN = 1;

    initSRAM();

    data1 = 0x77;
            //sprintf(data1, "Test Data\r");

    writeToSRAM(addr, data1);
  //  SPI1CONbits.MODE32 = 0;

    readFromSRAM(addr);
    UARTSendDataByte(UART1,(char)data1);
    UARTSendDataByte(UART1,(char)data2);
    
    while (1) // Run forever
    {

    }

    return 0;

}

//FUNCTIONS

void initSRAM(void) {
//    char instruction = 0x1; // Write to status register
//    char mode = 0x0; // Byte Mode
//    char output = 0;
//    char input = 0;

    SPI1CONbits.MODE32 = 1;
    SPI1BUF=0x0101;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    SPI1BUF; // Read the buffer to clear it

 /*
    output |= (mode << 6);
    output |= 1;

 //   CS = 0;
    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read BUF

    SPI1BUF = output;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read the buffer to clear it
 ///   CS = 1;

 //   CS = 0;
    SPI1BUF = 0x05;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read BUF

    SPI1BUF = 0x00;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read the buffer to clear it

 //   CS = 1;
*/
    return;
}

void writeToSRAM(int address, int data) {
//    int instruction = 0x2; // Write to address
//    int add1 = address >> 8; // Most significant 8 bits
//    int add2 = address & 0xFF; // Least significant 8 bits
//    int input;

    SPI1CONbits.MODE32 = 1;
//CS = 0;
    SPI1BUF=0x0200FF77;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    SPI1BUF; // Read the buffer to clear it
// CS = 1;
    /*
    //   CS = 0;
    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add1;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add2;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it


    SPI1BUF = data;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer

 //   CS = 1;
*/
}

void readFromSRAM(int address) {
  //  int instruction = 0x3; // Read from address
  //  int add1 = address >> 8; // Most significant 8 bits
 //   int add2 = address & 0xFF; // Least significant 8 bits
 //   int input;

 //   CS = 0;

    SPI1CONbits.MODE32 = 1;

    SPI1BUF=0x0300FF77;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    data2 = SPI1BUF; // Read the buffer to clear it

   /*
    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it


    SPI1BUF = add1;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add2;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it


    SPI1BUF = 0x00;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer
    data2 = input;
    */
 //    CS = 1;

    return;
}
