#ifndef DEBUG_H
#define	DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include "linkedlist.h"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(msg) printf("%s %d %s\r",__FILE__, __LINE__, msg)
#else
#define DEBUG_PRINT(msg)
#endif

//Error Codes
#define ERR_BUFF_EMPT     0xFF
#define ERR_BUFF_FULL     0x01
#define ERR_I2C_START     0x02
#define ERR_I2C_STOP      0x03
#define ERR_I2C_READ      0x04
#define ERR_I2C_WRITE     0x05
#define ERR_I2C_RESTART   0x06
#define ERR_I2C_ADDNACK1  0x07
#define ERR_I2C_ADDNACK2  0x08
#define ERR_I2C_DATANACK  0x09
#define ERR_I2C_BUSY1     0x0A
#define ERR_I2C_BUSY2     0x0B
#define ERR_I2C_TBF       0x0C
#define ERR_I2C_RCVTMOUT  0x0D
#define ERR_I2C_RADDNACK  0x0E
#define ERR_I2C_TRNTMOUT  0x0F
#define ERR_I2C_IWCOL     0x10
#define ERR_I2C_I2COV     0x11
extern volatile struct buffer_t error_buffer;

void log_error(char log);
char read_error(void);
void clear_error(void);
void print_error(void);

#endif	/* DEBUG_H */

