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
    // line hight -> i2c start -> 7-bit address + r/w bit -> sack -> inc + reg -> sack

    // CTR1: figure out data rate and BW settings
    // CTR2: HPF mode and cutoff settings
    // CTR3: sets interrupts on INT1/2 pins
    // CTR4: self test
    // CTR5: reboot mem, en/dis FIFO, HP en/dis, INT & OUT settings

    // set up change notification, call status, and read data

    // setup in bypass mode

    NU32_Startup();

    // initialize SPI

    // clear rx, tx, & err interrupts
    IEC1bits.SPI2EIE = 0;
    IEC1bits.SPI2RXIE = 0;
    IEC1bits.SPI2TXIE = 0;

    IEC1bits.SPI4EIE = 0;
    IEC1bits.SPI4RXIE = 0;
    IEC1bits.SPI4TXIE = 0;

    // clear the buffer
    SPI2BUF;
    SPI4BUF;

    // clear the control registers
    SPI2CON = 0;
    SPI4CON = 0;

    // enable interrupts
    /* do this later */

    // set baud rate
    SPI2BRG = 255;85; // 465.11 kHz
    SPI4BRG = 255;85;

    // clear overrun bit
    SPI2STATbits.SPIROV = 0;
    SPI4STATbits.SPIROV = 0;

    // set the control register
    SPI2CONbits.MSTEN = 0; // spi slave
    SPI2CONbits.SSEN = 1; // use spi ss
    SPI2CONbits.CKP = 1; // clk is idle high
    SPI2CONbits.CKE = 0; // DO changes high-to-low
    SPI2CONbits.MODE16 = 1;

    SPI4CONbits.MSTEN = 1; // spi master
    SPI4CONbits.MSSEN = 1; // use spi ss, ss is active-low (FRMPOL = 0)
    SPI4CONbits.CKP = 1; // clk is idle high
    SPI4CONbits.CKE = 0; // DO changes high-to-low
    SPI4CONbits.SMP = 1; // sample at end of cycle
    SPI4CONbits.MODE16 = 1; // 16-bit transfers

    // turn on SPI
    SPI2CONbits.ON = 1;
    SPI4CONbits.ON = 1;

    // (gyro) stay in spi mode
    if (!SPI4STATbits.SPITBF) SPI4BUF = (2 << 14 | 0x05 << 8);
    while (!SPI4STATbits.SPIRBF);
    printf("init: 0x%x\r", SPI4BUF);
    if (!SPI4STATbits.SPITBF) SPI4BUF = (0 << 14 | 0x05 << 8) | 0x20;

    // (gyro) read who am i register
    while (1) {
        while (NU32USER);
        if (!SPI4STATbits.SPITBF) SPI4BUF = (2 << 14 | WHO_AM_I << 8);

        while (!SPI4STATbits.SPIRBF);
        printf("spi4: 0x%x\r", SPI4BUF);
    }

    // spi test code btw SPI2 (slave) and SPI4 (master)
    while (1) {
        while (NU32USER);

        if (!SPI2STATbits.SPITBF) SPI2BUF = 0xAAAA;
        if (!SPI4STATbits.SPITBF) SPI4BUF = 0x5555; // transmit

        while (!SPI2STATbits.SPIRBF);
        printf("spi2: 0x%x\r", SPI2BUF);

        while (!SPI4STATbits.SPIRBF);
        printf("spi4: 0x%x\r", SPI4BUF);
    }
}

// use printf and friends
void _mon_putc(char c) {
    PutCharacter(UART1, c);
}