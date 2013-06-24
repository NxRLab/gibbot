#if 0
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
void writeToSRAM(int address, int length, char* data);
void readFromSRAM(int address, int length, char* data);

//MAIN
char data1[32];
char data2[32];

int main(void) {

    int addr = 0x00FF;

    NU32_Startup();
    //NU32_Initialize();
    NU32_WriteUART1("Hello World\r");
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

    initSRAM();

    sprintf(data1, "Test Data\r");

    writeToSRAM(addr, 10, data1);

    readFromSRAM(addr, 10, data2);

    NU32_WriteUART1(data2);

    while (1) // Run forever
    {

    }

    return 0;

}

//FUNCTIONS

void initSRAM(void) {
    char instruction = 0x1; // Write to status register
    char mode = 0x1; // Sequential Mode
    char output = 0;
    char input = 0;

    output |= (mode << 6);
    output |= 1;

    CS = 0;
    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read BUF

    SPI1BUF = output;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read the buffer to clear it
    CS = 1;

    CS = 0;
    SPI1BUF = 0x05;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read BUF

    SPI1BUF = 0x00;
    while (!SPI1STATbits.SPIRBF); // Wait till the module move BUF to Transfer
    input = SPI1BUF; // Read the buffer to clear it

    CS = 1;

    return;
}

void writeToSRAM(int address, int length, char* data) {
    char instruction = 0x2; // Write to address
    char add1 = address >> 8; // Most significant 8 bits
    char add2 = address & 0xFF; // Least significant 8 bits
    char input;
    int byte;

    CS = 0;
    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add1;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add2;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    for (byte = 0; byte < length; byte++) {
        SPI1BUF = *data;
        while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
        input = SPI1BUF; // Read the buffer
        data++;
    }
    CS = 1;

}

void readFromSRAM(int address, int length, char* data) {
    char instruction = 0x3; // Read from address
    char add1 = address >> 8; // Most significant 8 bits
    char add2 = address & 0xFF; // Least significant 8 bits
    char input;
    int byte;

    CS = 0;

    SPI1BUF = instruction;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it


    SPI1BUF = add1;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    SPI1BUF = add2;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it

    for (byte = 0; byte < length; byte++) {

        SPI1BUF = 0x00;
        while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
        input = SPI1BUF; // Read the buffer
        *data = input;
        data++;
    }
    CS = 1;

    return;
}


//ISRs

#endif