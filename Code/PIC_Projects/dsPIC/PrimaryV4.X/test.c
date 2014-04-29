#include <libpic30.h>
#include <p33EP512MC806.h>
#include "XBee.h"
#include "test.h"
#include "initialize.h"
#include "I2CMaster.h"
#include "motor.h"

unsigned char testBuff[256];
int incr=0;

void test_passthrough(unsigned char *testdata){
    unsigned char testecho;
    I2C_Write(testdata, 3, 1);
    I2C_Read(&testecho, 3, 1);
    U1TXREG = testecho; //echo data
}

void test_passthroughburst(unsigned char *testdata){
    unsigned char testecho[256];
    int i;
    if(incr<255){
        testBuff[incr] = *testdata;
        incr++;
    } else{
        testBuff[incr] = *testdata;
        I2C_Write(&testBuff[0], 0, 256);
        I2C_Read(&testecho[0], 0, 256);
        for(i=0;i<256;i++){
            U1TXREG = testecho[i];
            while(U1STAbits.UTXBF);
        }
        incr=0;
    }
}

void test_motor(unsigned char command){
    LED1 = !LED1;
    if(command == 'a'){
        direction = 1;
        LED2 = !LED2;
    } else if(command =='b'){
        direction = 0;
        LED3 = !LED3;
    } else if(command =='q'){
        if(MDC<1000){
            MDC = MDC + 50;
        } else{
            LED4 = !LED4;
        }
    } else if(command =='w'){
        if(MDC>50){
            MDC = MDC-50;
        } else {
            LED1 = !LED1;
        }
    } else if(command =='z'){
        motoron = 1;
        LED3 = !LED3;
    } else if(command =='x'){
        motoron = 0;
        LED3 = !LED3;
    }
} 