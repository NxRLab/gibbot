#include <libpic30.h>
#include <p33EP512MC806.h>
#include "encoder.h"
#include "I2CMaster.h"

void initialize_QEI(void){
    //Turn on QEI
    RPINR14bits.QEA1R = 99; //Set RP69 (D5) as QEI1 A
    RPINR14bits.QEB1R = 98; //Set RP68 (D4) as QEI1 B
    POS1CNTH = 0;
    POS1CNTL = 0;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1
}

void write_MOTENC(long val){
    write_I2C((unsigned char*) &val,MOTENC,4);
}

void write_LOWMAGENC(long val){
    write_I2C((unsigned char*) &val,LOWMAGENC,4);
}

void write_TOPMAGENC(long val){
    POS1HLD = val>>16;
    POS1CNTL = val & 0xFFFF;
}

long read_MOTENC(void){
    unsigned char temp[4]= {0,0,0,0};
    long test;
    read_I2C(temp,MOTENC,4);
    test = *((long *)temp);
    return test;
}

long read_LOWMAGENC(void){
    unsigned char temp[4]= {0,0,0,0};
    long test;
    read_I2C(temp,LOWMAGENC,4);
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