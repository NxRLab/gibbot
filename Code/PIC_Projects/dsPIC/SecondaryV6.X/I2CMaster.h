#ifndef I2CMASTER_H
#define	I2CMASTER_H

#define SLAVEADDR 0b11011010
#define MPUSLAVEADDR 0b11010010
#define R 1
#define W 0
#define MOTENC    0x09 //MOTREG is a long filling 0x09 - 0x0C
#define LOWMAGENC 0x0D //BOTMAG is a long filling 0x0D - 0x10
#define LOWMAGCON 0x11 //BOTMAG is a char

//Registers for MPU9150
#define SELF_TEST_X 0x0D // R/W
#define SELF_TEST_Y 0x0E // R/W
#define SELF_TEST_Z 0x0F // R/W
#define SELF_TEST_A 0x10 // R/W
#define SMPLRT_DIV 0x19 // R/W
#define CONFIG 0x1A // R/W
#define GYRO_CONFIG 0x1B // R/W
#define ACCEL_CONFIG 0x1C // R/W
#define INT_PIN_CFG 0x37 // R/W
#define INT_ENABLE 0x38 // R/W
#define ACCEL_XOUT_H 0x3B // R
#define ACCEL_XOUT_L 0x3C // R
#define ACCEL_YOUT_H 0x3D // R
#define ACCEL_YOUT_L 0x3E // R
#define ACCEL_ZOUT_H 0x3F // R
#define ACCEL_ZOUT_L 0x40 // R
#define GYRO_XOUT_H 0x43 // R
#define GYRO_XOUT_L 0x44 // R
#define GYRO_YOUT_H 0x45 // R
#define GYRO_YOUT_L 0x46 // R
#define GYRO_ZOUT_H 0x47 // R
#define GYRO_ZOUT_L 0x48 // R
#define USER_CTRL 0x6A // R/W
#define PWR_MGMT_1 0x6B // R/W
#define WHO_AM_I 0x75 // R

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

