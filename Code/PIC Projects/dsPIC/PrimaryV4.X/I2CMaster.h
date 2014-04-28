#ifndef I2CMASTER_H
#define	I2CMASTER_H

void Initialize_I2C_Master(void);
void I2C_Start(void);
char I2C_SendOneByte(unsigned char data);
void I2C_ReceiveOneByte(unsigned char *data, char Ack);
void I2C_Write(unsigned char *data, unsigned char reg, int numbytes);
void I2C_Read(unsigned char *data, unsigned char reg, int numbytes);
void I2C_Stop(void);

#endif	/* I2CMASTER_H */

