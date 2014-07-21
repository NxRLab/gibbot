#include <libpic30.h>
#include <stdio.h>
#include <p33EP512MC806.h>
#include "initializeV5.h"
#include "MPU.h"
#include "I2CMaster.h"
#include "UART.h"
#include "linkedlist.h"

void initialize_MPU(void){
    unsigned char c;
    c = 0x01; // PLL with x-gyroscope reference for clock
    write_I2C(&c,PWR_MGMT_1,1);
    c = 0x01; // reset signal paths
    write_I2C(&c,USER_CTRL,1);
    c = 0x00; // DLPF_CFG = 0 (gyroscope at 8kHz)
    write_I2C(&c,CONFIG,1);
    c = 0x07; // sample rate = gyroscope output rate/(1 + SMPLRT_DIV) gyro output rate = 8kHz and SMPLRt_DIV = 7 so 1kHz sample rate
    write_I2C(&c,SMPLRT_DIV,1);
    // c = 0x00; // Gyro range of + or - 250 degrees/s (131 LSB/(degree/s))
    // c = 0b00001000; // Gyro range of + or - 500 degrees/s (65.5 LSB/(degree/s))
    // c = 0b00010000; // Gyro range of + or - 1000 degrees/s (32.8 LSB/(degree/s))
    c = 0b00011000; // Gyro range of + or - 2000 degrees/s (16.4 LSB/(degree/s))
    write_I2C(&c,GYRO_CONFIG,1);
    // c = 0x00; // Accel range of + or - 2g (16384 LSB/g)
    // c = 0b00001000; // Accel range of + or - 4g (8192 LSB/g)
    // c = 0b00010000; // Accel range of + or - 8g (4096 LSB/g)
    c = 0b00011000; // Accel range of + or - 16g (2048 LSB/g)
    write_I2C(&c,ACCEL_CONFIG,1);
    c = 0x00; // INT pin not implemented, switch to next line when interrupt is used
    // c = 0x30; // INT pin held high until interrupt cleared; interrupt cleared on any read operation
    write_I2C(&c,INT_PIN_CFG,1);
    c = 0x00; // interrupt disabled
    // c = 0x01; // Data Ready interrupt enabled
    write_I2C(&c,INT_ENABLE,1);
}


void write_MPU(){

}

void read_Accel(unsigned char *data){
    read_I2C(data,ACCEL_XOUT_L,1);
    read_I2C(data+1,ACCEL_XOUT_H,1);
    read_I2C(data+2,ACCEL_YOUT_L,1);
    read_I2C(data+3,ACCEL_YOUT_H,1);
    read_I2C(data+4,ACCEL_ZOUT_L,1);
    read_I2C(data+5,ACCEL_ZOUT_H,1);
}

void read_Gyro(unsigned char *data){
    read_I2C(data,GYRO_XOUT_L,1);
    read_I2C(data+1,GYRO_XOUT_H,1);
    read_I2C(data+2,GYRO_YOUT_L,1);
    read_I2C(data+3,GYRO_YOUT_H,1);
    read_I2C(data+4,GYRO_ZOUT_L,1);
    read_I2C(data+5,GYRO_ZOUT_H,1);
}

void read_Accel_Secondary(unsigned char *data){
    write_UART2('9');
    while(!(uart_buffer.len>5));
    read_string_UART(data,6);
}

void read_Gyro_Secondary(unsigned char *data){
    write_UART2('a');
    while(!(uart_buffer.len>5));
    read_string_UART(data,6);
}

void read_MPU_test(unsigned char *data){
    read_I2C(data,WHO_AM_I,1); // use to verify identity of IMU to make sure communication is working.  Should return 0x68.
    printf("%x\n",data[0]);
}

double Accel_convert(unsigned char *data,int i,int j){
    double accel;
    accel = data[j] << 8 | data[i];
    accel = 4.8828125e-04 * accel;
    /* Accel Range      Sensitivity (g/LSB)
     * 2g               6.103515625e-05
     * 4g               1.220703125e-04
     * 8g               2.44140625e-04
     * 16g              4.8828125e-04
     */
    return accel;
}

double Gyro_convert(unsigned char *data,int i, int j){
    double gyro;
    gyro = data[j] << 8 | data[i];
    gyro = .0609756098 * gyro;
    /* Gyro Range       Sensitivity ((degree/s)/LSB)
     * 250              .0076335878
     * 500              .0152671756
     * 1000             .0304878049
     * 2500             .0609756098
     */
    return gyro;
}
