/* 
 * File:   interrupts.h
 * Author: ajgriesemer
 *
 * Created on October 8, 2013, 4:16 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#define I2C_WRITE     0
#define I2C_READ      1
#define I2C_IDLE      2
#define I2C_ERR    0xFFFF

struct I2C_CONTROL_t{
    int cmd;
    int state;
    unsigned int repeatcount;
    unsigned int slaveaddr; //7 bit address
    unsigned int numbytes;
    char data[10]; 
};

extern struct I2C_CONTROL_t I2C_CONTROL;
#endif	/* INTERRUPTS_H */

