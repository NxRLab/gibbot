#ifndef I2CMASTER_H
#define	I2CMASTER_H

#define SLAVEADDR 0b11011010
#define R 1
#define W 0
#define MOTENC    0x09 //MOTREG is a long filling 0x09 - 0x0C
#define LOWMAGENC 0x0D //BOTMAG is a long filling 0x0D - 0x10
#define LOWMAGCON 0x11 //BOTMAG is a char

#define I2C_TIMEOUT 100000 //number of while loop iterations before I2C times out

#define I2C_IDLE    0
#define I2C_DEVADDR 1
#define I2C_REGADDR 2
#define I2C_RESTART 3
#define I2C_DATA    4

void initialize_I2C_Master(void);
char write_I2C(unsigned char *data, unsigned char reg, int numbytes);
char read_I2C(unsigned char *data, unsigned char reg, int numbytes);
void start_I2C(void);
void repeatStart_I2C(void);
char sendOneByte_I2C(unsigned char data);
char receiveOneByte_I2C(unsigned char *data, char Ack);
void stop_I2C(void);

#endif	/* I2CMASTER_H */

