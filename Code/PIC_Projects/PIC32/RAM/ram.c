#if 0
#include <plib.h>
#include <string.h>
#include <math.h>
#include "NU32_2012.h"


// testing  SCK2 G6 <-> SCK4 F13 (master)
//          SDI2 G7 <-> SDO4 F5
//          SDO2 G8 <-> SDI4 F4
//           SS2 G9 <->  SS4 F12
#define CS      LATAbits.LATA0
int main(void) {
    int input;
    int output;
    int add1;
    int add2;
    NU32_Startup();

    // initialize SPI

    // clear rx, tx, & err interrupts
    IEC1bits.SPI4EIE = 0;
    IEC1bits.SPI4RXIE = 0;
    IEC1bits.SPI4TXIE = 0;

    // clear the buffer
    SPI4BUF;

    // clear the control registers
    SPI4CON = 0;

    // enable interrupts
    /* do this later */

    // set baud rate
    //SPI4BRG = 85; // 465.11 kHz
    SPI1CON = 0; // Disable and reset SPI module
    SPI1BRG = 39; // Set the baudrate to (80MHz)/2/(39+1) = 1Mhz
    SPI1STATbits.SPIROV = 0; // Clear overflow flag


    // set the control register
    SPI1CONbits.MSTEN = 1; // spi master
    //SPI1CONbits.MSSEN = 1; // use spi ss, ss is active-low (FRMPOL = 0)
    SPI1CONbits.CKP = 0; // clk is idle low   //changed
    SPI1CONbits.CKE = 1; // DO changes low-to-high   //changed
    SPI1CONbits.SMP = 1; // sample at end of cycle
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 0;

    // turn on SPI
    SPI1CONbits.ON = 1;

    //start;
    //SPI1CONbits.FRMPOL = 0; //bring CS to 0

    //SPI1BUF = 0b00000001;//byte mode by sending 00000001 then 00000001
    //SPI1BUF = 0b00000001;
    //--
    while(1)
    {
////    SPI1BUF = 0x02000071;//0b00000010000000000000000001110001;

////    SPI1BUF = 0x03000071;//0b00000011000000000000000000000000;
    CS=0;
    SPI1BUF=0x01;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it
    SPI1BUF=0x01;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it
    CS=1;
 //   SPI1BUF;
    CS=0;
    SPI1BUF=0x05;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it
    SPI1BUF=0x00;
    while (!SPI1STATbits.SPIRBF); // Wait for transaction to finish
    input = SPI1BUF; // Read the buffer to clear it
    
    printf("data1 read: 0x%x\r", input);
CS=1;
  //  while (SPI1STATbits.SPIRBF == 0);
    
    printf("data2 read: 0x%x\r", SPI1BUF);

    }
}

// use printf and friends

void _mon_putc(char c) {
    PutCharacter(UART1, c);
}
#endif