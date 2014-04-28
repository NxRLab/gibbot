#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

//Functions for initializing the necessary modules
void Startup(void);
void Initialize_CN(void);
void Initialize_PWM(void);
void Initialize_UART(void);
void Initialize_QEI(void);
void Initialize_Timer1(void);
void Initialize_ADC(void);
void Lights(void);
short ADC_Read(void);
void Initialize_I2C_Master(void);
void I2C_Read(char command);
void I2C_Write(char command);
extern int MOTCNT;
extern long LOWMAGCNT;

#define I2C_WRITE     0
#define I2C_READ      1
#define I2C_IDLE      2
#define I2C_ERR    0xFFFF

#define MAGNET_ON   0b0000100
#define READ_MOTOR  0b0000010
#define READ_LOWMAG 0b0000001

struct I2C_CONTROL_t{
    int cmd;
    int state;
    unsigned int repeatcount;
    unsigned int slaveaddr; //7 bit address
    unsigned int numbytes;
    unsigned char trndata[10];
    unsigned char rcvdata[6];
};

extern struct I2C_CONTROL_t I2C_CONTROL;

extern int error;
#endif	/* PERIPHERALS_H */