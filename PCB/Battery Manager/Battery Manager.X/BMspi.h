/* 
 * File:   accel.h
 * Author: ryanyu
 *
 * Created on April 15, 2015, 1:49 PM
 */

#ifndef BMspi__H__
#define BMspi__H__
// Basic interface with an LSM303D accelerometer/compass.
// Used for both i2c and spi examples, but with different implementation (.c) files

                        // register addresses
#define RDCVA 0x04      // control register 1
#define RDCVB 0b00000000110      // control register 2
#define RDCVC 0b00000001000      // control register 5
#define RDCVD 0b00000001010      // control register 7

#define PEC 0x07 0xC2  // LSB of x axis acceleration register.
                        // all acceleration registers are contiguous, and this is the lowest address
#define OUT_X_L_M 0x08  // LSB of x axis of magnetometer register

#define TEMP_OUT_L 0x05 // temperature sensor register

// read len bytes from the specified register into data[]
void BM_read_register(unsigned char reg1, unsigned char reg2, unsigned char data[], unsigned int len);

// write to the register
void BM_write_register(unsigned char reg, unsigned char data);

// initialize the battery manager
void BM_setup();
#endif

