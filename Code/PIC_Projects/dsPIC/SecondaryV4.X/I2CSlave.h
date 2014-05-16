#ifndef I2CSLAVE_H
#define	I2CSLAVE_H

#define SLAVEADDR 0b11011010
#define MOTENC    0x09 //MOTREG is a long filling 0x09 - 0x0C
#define LOWMAGENC 0x0D //BOTMAG is a long filling 0x0D - 0x10
#define LOWMAGCON 0x11 //BOTMAG is a char

extern unsigned char RegBuffer[256];

void initialize_I2C_Slave(void);

#endif	/* I2CSLAVE_H */

