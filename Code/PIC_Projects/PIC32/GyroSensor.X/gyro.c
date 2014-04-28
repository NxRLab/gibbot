#include <plib.h>
#include <string.h>
#include <math.h>
#include "NU32_2012.h"

// testing  SCK2 G6 <-> SCK4 F13 (master)
//          SDI2 G7 <-> SDO4 F5
//          SDO2 G8 <-> SDI4 F4
//           SS2 G9 <->  SS4 F12

#define GYRO_ADDR 0b110100x // x = state of SDO pin

// addr map
#define WHO_AM_I 0x0f // r
#define CTRL_REG1 0x20 // rw
#define CTRL_REG2 0x21 // rw
#define CTRL_REG3 0x22 // rw
#define CTRL_REG4 0x23 // rw
#define CTRL_REG5 0x24 // rw
#define REFERENCE 0x25 // rw
#define OUT_TEMP 0x26 // r
#define STATUS_REG 0x27 // r
#define OUT_X_L 0x28 // r
#define OUT_X_H 0x29 // r
#define OUT_Y_L 0x2A // r
#define OUT_Y_H 0x2B // r
#define OUT_Z_L 0x2C // r
#define OUT_Z_H 0x2D // r
#define FIFO_CTRL_REG 0x2E  // rw
#define FIFO_SRC_REG 0x2F // r
#define INT1_CFG 0x30 // rw
#define INT1_SRC 0x31 // r
#define INT1_TSH_XH 0x32 // rw
#define INT1_TSH_XL 0x33 // rw
#define INT1_TSH_YH 0x34 // rw
#define INT1_TSH_YL 0x35 // rw
#define INT1_TSH_ZH 0x36 // rw
#define INT1_TSH_ZL 0x37 // rw
#define INT1_DURATION 0x38 // rw

int main(void) {
    NU32_Startup();

    // initialize SPI

    // clear rx, tx, & err interrupts
    IEC0bits.SPI1EIE = 0;
    IEC0bits.SPI1RXIE = 0;
    IEC0bits.SPI1TXIE = 0;

    // clear the buffer
    SPI1BUF;

    // clear the control registers
    SPI1CON = 0;

    // enable interrupts
    /* do this later */

    // set baud rate // 465.11 kHz
    SPI1BRG = 85;

    // clear overrun bit
    SPI1STATbits.SPIROV = 0;

    // set the control register
    SPI1CONbits.MSTEN = 1; // spi master
    SPI1CONbits.MSSEN = 1; // use spi ss, ss is active-low (FRMPOL = 0)
    SPI1CONbits.CKP = 1; // clk is idle high
    SPI1CONbits.CKE = 0; // DO changes high-to-low
    SPI1CONbits.SMP = 1; // sample at end of cycle
    SPI1CONbits.MODE16 = 1; // 16-bit transfers

    // turn on SPI
    SPI1CONbits.ON = 1;

//    if (!SPI1STATbits.SPITBF) SPI1BUF = (0 << 14 | CTRL_REG1 << 8) | (0x3f & 0xff);
//    while (!SPI1STATbits.SPIRBF);
//    printf("ctrl1: 0x%x\r", SPI1BUF);

    // (gyro) read who am i register
    short data;
    while (1) {
        while (NU32USER);
        if (!SPI1STATbits.SPITBF) SPI1BUF = (2 << 14 | WHO_AM_I << 8);
        while (!SPI1STATbits.SPIRBF);
        printf("who am i: 0x%x\r", SPI1BUF);
    }
}

// use printf and friends

void _mon_putc(char c) {
    PutCharacter(UART1, c);
}