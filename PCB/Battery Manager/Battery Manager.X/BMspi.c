/* 
 * File:   spi_accel.c
 * Author: ryanyu
 *
 * Created on April 15, 2015, 1:50 PM
 */

#include "BMspi.h"
#include <xc.h>
// interface with the LSM303D accelerometer/magnetometer using spi
// Wire GND to GND, VDD to 3.3V,
// SDO1             -> SDI (labeled SDA),
// SDI1             -> SDO
// SCK1 (B14)       -> SCL
// some digital pin -> CS

#define CS LATBbits.LATB4 // replace x with some digital pin

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}


//method for calculating PEC (currently not working)

//short calc_PEC(short reg){
//  unsigned int i;
//  short IN[16];
//  short DIN;
//  short pec_array[15];
//  short pec = 0b000000000010000;
//
//  for (i = 0; i <= 14; ++i){
//      pec_array[i] = ((pec >> i) & 0x01);
//  }
//
//  for (i = 0; i <= 15; ++i){
//      DIN = ((reg >> (15-i)) & 0x01);
//      IN[0] = DIN^pec_array[14];
//      IN[3] = IN[0]^pec_array[2];
//      IN[4] = IN[0]^pec_array[3];
//      IN[7] = IN[0]^pec_array[6];
//      IN[8] = IN[0]^pec_array[7];
//      IN[10] = IN[0]^pec_array[9];
//      IN[14] = IN[0]^pec_array[13];
//
//      pec = (-IN[14] ^ pec) & (1 << 14);
//      pec = (-pec_array[12] ^ pec) & (1 << 13);
//      pec = (-pec_array[11] ^ pec) & (1 << 12);
//      pec = (-pec_array[10] ^ pec) & (1 << 11);
//      pec = (-IN[10] ^ pec) & (1 << 10);
//      pec = (-pec_array[8] ^ pec) & (1 << 9);
//      pec = (-IN[8] ^ pec) & (1 << 8);
//      pec = (-IN[7] ^ pec) & (1 << 7);
//      pec = (-pec_array[5] ^ pec) & (1 << 6);
//      pec = (-pec_array[4] ^ pec) & (1 << 5);
//      pec = (-IN[4] ^ pec) & (1 << 4);
//      pec = (-IN[3] ^ pec) & (1 << 3);
//      pec = (-pec_array[1] ^ pec) & (1 << 2);
//      pec = (-pec_array[0] ^ pec) & (1 << 1);
//      pec = (-IN[0] ^ pec) & (1 << 0);
//  }
//  return pec;
//}

// read data from the accelerometer, given the starting register address.
// return the data in data
void acc_read_register(unsigned char reg1,unsigned char reg2, unsigned char data[], unsigned int len) {
  unsigned int i;

  CS = 0;
  spi_io(reg1);
  spi_io(reg2);
  spi_io(0x07);
  spi_io(0xC2);

  for(i = 0; i != len; ++i) {
    data[i] = spi_io(0); // read data from spi
  }
  CS = 1;
}


void acc_write_register(unsigned char reg, unsigned char pec, unsigned char data) {
  CS = 0;               // bring CS low to activate SPI
  spi_io(reg);
  spi_io(data);
  CS = 1;               // complete the command
}


void BM_setup() {
  TRISBbits.TRISB4 = 0; // set CS to output and digital if necessary
  CS = 1;

  // select a pin for SDI1
  ANSELAbits.ANSA1 = 0;
  SDI1Rbits.SDI1R = 0b0000;

  // select a pin for SD01
  RPA4Rbits.RPA4R = 0b0011;

  // Setup the master Master - SPI1
  // we manually control SS as a digital output
  // since the pic is just starting, we know that spi is off. We rely on defaults here

  // setup spi1
  SPI1CON = 0;              // turn off the spi module and reset it
  SPI1BUF;                  // clear the rx buffer by reading from it
  SPI1BRG = 0x3;            // baud rate to 5MHz [SPI1BRG = (40000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0;  // clear the overflow bit
  SPI1CONbits.CKE = 1;      // data changes when clock goes from active to inactive
                            //    (high to low since CKP is 0)
  SPI1CONbits.MSTEN = 1;    // master operation
  SPI1CONbits.ON = 1;       // turn on spi


}

