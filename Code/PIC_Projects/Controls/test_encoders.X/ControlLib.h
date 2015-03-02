/* 
 * File:   ControlLib.h
 * Author: harntson
 *
 * Created on February 25, 2015, 11:57 AM
 */

#ifndef CONTROLLIB_H
#define	CONTROLLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>

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

#define SLAVEADDR 0b11011010
#define MPUSLAVEADDR 0b11010010 // Address for MPU9150
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
#define SMPLRT_DIV 0x19 // R/W Sample Rate Divider (Generates sample rate for MPU9150)
#define CONFIG 0x1A // R/W Configuration (Controls FSYNC pin sampling and DLPF setting for gyroscopes/accelerometers)
#define GYRO_CONFIG 0x1B // R/W Gyroscope Configuration (Sets sensitivity of gyroscope)
#define ACCEL_CONFIG 0x1C // R/W Accelerometer Configuration (Sets sensitivity of accelerometer)
#define INT_PIN_CFG 0x37 // R/W Interrupt Enable (Configures interrupt signals at INT pin)
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
#define USER_CTRL 0x6A // R/W User Control
#define PWR_MGMT_1 0x6B // R/W Power Management 1 (Configures power mode and clock source)
#define WHO_AM_I 0x75 // R

#define I2C_TIMEOUT 100000 //number of while loop iterations before I2C times out

#define I2C_IDLE    0
#define I2C_DEVADDR 1
#define I2C_REGADDR 2
#define I2C_RESTART 3
#define I2C_DATA    4

#define LED1 LATBbits.LATB13
#define LED2 LATBbits.LATB12
#define LED3 LATDbits.LATD11
#define LED4 LATDbits.LATD0
#define USER PORTDbits.RD10
#define TOPMAG LATBbits.LATB14

#define RST_POR    (1<<0)
#define RST_BOR    (1<<1)
#define RST_IDLE   (1<<2)
#define RST_SLEEP  (1<<3)
#define RST_WDTO   (1<<4)
#define RST_SWDTEN (1<<5)
#define RST_SWR    (1<<6)
#define RST_EXTR   (1<<7)
#define RST_VREGS  (1<<8)
#define RST_CM     (1<<9)
#define RST_VREGSF (1<<11)
#define RST_SBOREN (1<<13)
#define RST_IOPUWR (1<<14)
#define RST_TRAPR  (1<<15)

#define CW 0
#define CCW 1

//Rotary encoder outputs from the BLDC motor
#define S3 PORTDbits.RD5
#define S2 PORTDbits.RD4
#define S1 PORTDbits.RD3

struct linked_list_t {
    unsigned char c;            //Variable stored in linked list
    struct linked_list_t *next; //Pointer to next element in linked list
};

typedef struct linked_list_t LinkedList; //Shorten declaration of a new struct
                                         //to the syntax LinkedList name

struct buffer_t { //Create buffer type definition
    LinkedList *first; //Pointer to first element in buffer
    LinkedList *last;  //Pointer to last element in buffer
    int len;           //Tally of elements in buffer
};

void initialize_ADC(void);
unsigned short read_ADC(void);
void initialize_ADC_Single(void);
unsigned short ADC_Read_Single(void);
void initialize_ADC_Offset(void);
float ADC_to_current(unsigned short data);
float ADC_to_torque(unsigned short data);

extern unsigned short Avi;

extern volatile struct buffer_t error_buffer;

void log_error(char log);
char read_error(void);
void clear_error(void);
void print_error(void);

void initialize_QEI(void);
void write_MOTENC(long val);
void write_LOWMAGENC(long val);
void write_TOPMAGENC(long val);
long read_MOTENC(void);
long read_LOWMAGENC(void);
long read_TOPMAGENC(void);
int encoder_to_angle(long val, char num);
void initialize_encoder_values(long val1,long val2,long val3);

void initialize_I2C_Master(void);
char write_I2C(unsigned char *data, unsigned char reg, int numbytes);
char read_I2C(unsigned char *data, unsigned char reg, int numbytes);
void start_I2C(void);
void repeatStart_I2C(void);
char sendOneByte_I2C(unsigned char data);
char receiveOneByte_I2C(unsigned char *data, char Ack);
void stop_I2C(void);

void initialize(void);
void lights(void);
extern unsigned short resetStat;

void write_duty(int value);
int read_duty(void);
void High(int pin);
void Low(int pin);
void Float(int pin);
void initialize_PWM(void);
void initialize_CN(void);
void commutate(int state);
void kick(void);

extern char motoron;
extern char state;
extern int direction;

void initialize_MPU(void);
void write_MPU();
void read_Accel(unsigned char *data);
void read_Gyro(unsigned char *data);
void read_MPU_test(unsigned char *data);
double Accel_convert(unsigned char *data,int i,int j);
double Gyro_convert(unsigned char *data,int i,int j);
void read_Accel_Secondary(unsigned char *data);
void read_Gyro_Secondary(unsigned char *data);

float read_motor_temp(void);

void test_passthrough(void);
void test_passthroughburst(void);
void test_motor(void);
void test_plotter(void);
void test_PWMPlotter(void);
void test_HeartBeat(void);
void test_UART(void);
void test_encoder(void);
void test_MayDay(void);

void timer1_on(void);
 void timer1_off(void);
 void delay_ms(int x);
 void delay_us(int x);

void initialize_UART(void);
void initialize_UART2(void);
void clear_queue(void);
unsigned char dequeue(void);
void enqueue(unsigned char c);
unsigned char read_UART(void);
void write_UART(unsigned char data);
void write_UART2(unsigned char data);
void write(unsigned char data);
void read_string_UART(unsigned char *data, int n);
void write_string_UART2(unsigned char *data, int n);
void write_string_UART(unsigned char *data, int n);

extern volatile struct buffer_t uart_buffer;

#endif	/* CONTROLLIB_H */

