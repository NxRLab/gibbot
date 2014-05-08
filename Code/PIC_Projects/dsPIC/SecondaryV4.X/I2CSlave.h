#ifndef I2CSLAVE_H
#define	I2CSLAVE_H

#define SLAVEADDR 0b11011010
#define MOTENC    0x09 //MOTREG is a short filling 0x09 - 0x0A
#define LOWMAGENC 0x0B //BOTMAG is a long filling 0x0B - 0x0F

extern unsigned char RegBuffer[256];

void initialize_I2C_Slave(void);

#endif	/* I2CSLAVE_H */

