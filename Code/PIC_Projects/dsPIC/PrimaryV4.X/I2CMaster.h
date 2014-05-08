#ifndef I2CMASTER_H
#define	I2CMASTER_H

#define SLAVEADDR 0b11011010
#define R 1
#define W 0
#define MOTENC    0x09 //MOTENC is a short filling 0x09 -> 0x0A
#define LOWMAGENC 0x0B //LOWMAGENC is a long filling 0x0B -> 0x0F

void initialize_I2C_Master(void);
void write_I2C(unsigned char *data, unsigned char reg, int numbytes);
void read_I2C(unsigned char *data, unsigned char reg, int numbytes);
void start_I2C(void);
void repeatStart_I2C(void);
char sendOneByte_I2C(unsigned char data);
void receiveOneByte_I2C(unsigned char *data, char Ack);
void stop_I2C(void);

#endif	/* I2CMASTER_H */

