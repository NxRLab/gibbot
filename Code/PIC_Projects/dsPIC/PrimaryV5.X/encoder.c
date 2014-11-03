#include <libpic30.h>
#include <stdio.h>
#include <p33EP512MC806.h>
#include "encoder.h"
#include "UART.h"
#include "initializeV5.h"
#include "linkedlist.h"

void initialize_QEI(void){
    //Turn on QEI
    RPINR14bits.QEA1R = 99; //Set RP99 (F3) as QEI1 A
    RPINR14bits.QEB1R = 98; //Set RP98 (F2) as QEI1 B
    POS1CNTH = 0;
    POS1CNTL = 0;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1
}

void write_MOTENC(long val){
    //write_I2C((unsigned char*) &val,MOTENC,4);
    write_UART2('7');
    write_string_UART2((unsigned char *) &val,4);
    //write_UART2(val>>24);
    //write_UART2(val>>16);
    //write_UART2(val>>8);
    //write_UART2(val);
}

void write_LOWMAGENC(long val){
    //write_I2C((unsigned char*) &val,LOWMAGENC,4);
    write_UART2('6');
    write_string_UART2((unsigned char *) &val,4);
    //write_UART2(val>>24);
    //write_UART2(val>>16);
    //write_UART2(val>>8);
    //write_UART2(val);
}

void write_TOPMAGENC(long val){
    POS1HLD = val>>16;
    POS1CNTL = val & 0xFFFF;
}

long read_MOTENC(void){
    unsigned char temp[4] = {0,0,0,0};
    long test;
    //read_I2C(temp,MOTENC,4);
    write_UART2('5');
    while(!(uart_buffer.len>3));
    temp[0] = read_UART();
    temp[1] = read_UART();
    temp[2] = read_UART();
    temp[3] = read_UART();
    //read_string_UART(temp,4);
    test = *((long *)temp);
    return test;
}

long read_LOWMAGENC(void){
    unsigned char temp[4]= {0,0,0,0};
    long test;
    //read_I2C(temp,LOWMAGENC,4);
    write_UART2('4');
    while(!(uart_buffer.len>3));
    temp[0] = read_UART();
    temp[1] = read_UART();
    temp[2] = read_UART();
    temp[3] = read_UART();
    //read_string_UART(temp,4);
    test = *((long *)temp);
    return test;
}

long read_TOPMAGENC(void){
    long temp1;
    long temp2;
    long test;
    temp1 = POS1CNTL;
    temp2 = POS1HLD;
    test = temp2<<16 | temp1;
    return test;
}

int encoder_to_angle(long val, char num){
    /*Returns the angle value of one of three encoders from the encoder count.*/
    int angle, cpr;
    long start;
    switch (num){
        case 'l': // lower magnet encoder
            start = 1600; // starting value of lower magnet encoder
            cpr = 2000; // counts per revolution of lower magnet encoder
            break;
        case 'm': // motor encoder
            start = 1700; // starting value of motor encoder
            cpr = 2000; // counts per revolution of motor encoder
            break;
        case 't': // top magnet encoder
            start = 1800; // starting value of top magnet encoder
            cpr = 2000; // counts per revolution of top magnet encoder
            break;
    }
    angle = (val - start)*360/cpr; // angle of specified encoder
    return angle;
}

void initialize_encoder_values(long val1,long val2,long val3){
    /*Writes the specified encoder values to the three encoders being used.
     This is used on initialization to set the starting encoder values so that
     the proper angles can be calculated from a known value.*/
     write_LOWMAGENC(val1);
     write_MOTENC(val2);
     write_TOPMAGENC(val3);
}