#include <libpic30.h>
#include <p33EP512MC806.h>
#include "UART.h"
#include "test.h"
#include "initializeV5.h"
#include "I2CMaster.h"
#include "motor.h"
#include "ADC.h"
#include "encoder.h"
#include "debug.h"

unsigned char testBuff[256];
short duty=300;
int senddata=0;
unsigned short csdata[1024];
int j=0;

void test_MayDay(void){
    unsigned char command;
    unsigned short data;
    unsigned char datachar;
    unsigned char testdata=0;
    unsigned char testecho[256];
    static long i=0;
    int i2=0;
    long i3=0;
    long temp;
    int incr=0;
    int fa;
    if(i>4000){
        if(duty>read_duty()){
            write_duty(read_duty()+1);
        } else if(duty<read_duty()){
            write_duty(read_duty()-1);
        }
        i=0;
    } else{
        i++;
    }
    if(uart_buffer.len>0){
        command = read_UART();
        LED1 = !LED1;
        if(command =='0'){ //Return ADC value
            data = read_ADC();
            write_UART(data>>8);
            write_UART(data);
            //write_UART(data>>8);
        } else if(command=='1'){ //Set Encoder Values
            write_LOWMAGENC(1600);
            write_MOTENC(1700);
            write_TOPMAGENC(1800);
        } else if(command=='2'){ // Read Encoder Values
            temp = read_LOWMAGENC();
            write_UART(temp>>24);           
            write_UART(temp>>16);            
            write_UART(temp>>8);
            write_UART(temp);
            //write_UART(temp>>8);
            //write_UART(temp>>16);
            //write_UART(temp>>24);
            temp = read_MOTENC();
            write_UART(temp>>24);
            write_UART(temp>>16);
            write_UART(temp>>8);
            write_UART(temp);
            //write_UART(temp>>8);
            //write_UART(temp>>16);
            //write_UART(temp>>24);
            temp = read_TOPMAGENC();
            write_UART(temp>>24);
            write_UART(temp>>16);
            write_UART(temp>>8);
            write_UART(temp);
            //write_UART(temp);
            //write_UART(temp>>8);
            //write_UART(temp>>16);
            //write_UART(temp>>24);
        } else if(command == '3'){ //Reverse Motor Direction
            direction = !direction;
        } else if(command =='4'){ //Turn motor on
            motoron = 1;
            kick();
        } else if(command =='5'){ //Turn motor off
            motoron = 0;
        } else if(command =='6'){ //Increment duty cycle
            if(duty<950){
                duty = duty+50;
            } else{
                LED4 = !LED4;
            }
        } else if(command =='7'){ //Decrement duty cycle
            if(duty>50){
                duty=duty-50;
            } else {
                LED4 = !LED4;
            }
        } else if(command =='8'){ //Set to maximum duty cycle
            duty=1000;
            kick();
            LED3 = !LED3;
        } else if(command =='9'){ //Set to minimum duty cycle
            duty=150;
            LED3 = !LED3;
        } else if(command=='a'){ //Pass through test, 256 single reads
            LED4 = 0;
            while((i2<256) && (i3<1000000)){
                if(uart_buffer.len > 0){
                    testdata = read_UART();
                    unsigned char testecho;
                    write_I2C(&testdata, 3, 1);
                    read_I2C(&testecho, 3, 1);
                    U1TXREG = testecho; //echo data
                    i2++;
                    i3=0;
                }
                i3++;
            }
            LED4=1;
        } else if(command=='b'){ //Pass through test, burst read
            LED4 = 0;
            while(incr<256 && (i3<1000000)){
                if(uart_buffer.len > 0){
                    if(incr<255){
                        testdata = read_UART();
                        testBuff[incr] = testdata;
                        incr++;
                    } else{
                        testdata = read_UART();
                        testBuff[incr] = testdata;
                        write_I2C(&testBuff[0], 0, 256);
                        read_I2C(&testecho[0], 0, 256);
                        for(i=0;i<256;i++){
                            while(U1STAbits.UTXBF);
                            U1TXREG = testecho[i];
                        }
                        incr++;
                    }
                    i=0;
                }
                i3++;
            }
            LED4 = 1;
        } else if(command=='c'){ //Toggle Top Magnet
            TOPMAG = !TOPMAG;
        } else if(command=='d'){ //Turn on Top Magnet
            TOPMAG = 1;
        } else if(command=='e'){ //Turn off Top Magnet
            TOPMAG = 0;
        } else if(command=='f'){ //Toggle Bottom Magnet
            datachar = 2;
            write_I2C(&datachar, LOWMAGCON, 1);
        } else if(command=='g'){ //Turn on Bottom Magnet
            datachar = 1;
            write_I2C(&datachar, LOWMAGCON, 1);
        } else if(command=='h'){ //Turn off Bottom Magnet
            datachar = 0;
            write_I2C(&datachar, LOWMAGCON, 1);
        } else if(command=='i'){ //Return Errors
            print_error();
        } else if(command=='j'){ //kick
            kick();
        } else if(command=='k'){ //kick
            commutate(0);
        } else if(command == 'l'){
            for(i=0;i<1024;i++){
                csdata[i] = read_ADC();
                __delay32(39000);
                LED1 = !LED1;
            }
            LED2 = !LED2;
            j=0;
        } else if(command == 'm'){
            if(j<64){
                fa = j*16;
                char *s = (char *) &csdata[fa];
                for(i=0;i<32;i++){
                    while (U1STAbits.UTXBF); // wait until tx buffer isn't full
                    U1TXREG = s[i];
                    LED3=!LED3;
                }
                j++;
            } else {
                j=0;
            }
            
        }
    }
}

void test_PWMPlotter(void){
    unsigned char command;
    long i;
    int fa;
    if(uart_buffer.len>0){
        command = read_UART();
        if(command == 'e'){
            MDC = 100;
            direction = 1;
            motoron = 1;
            LED1 = 0;
            kick();
        } else if(command =='r'){
            for(i=0;i<1024;i++){
                csdata[i] = read_ADC();
                __delay32(39000);
                LED1 = !LED1;
            }
            LED2 = !LED2;
            j=0;
        } else if(command == 't'){
            if(j<64){
                fa = j*16;
                char *s = (char *) &csdata[fa];
                for(i=0;i<32;i++){
                    while (U1STAbits.UTXBF); // wait until tx buffer isn't full
                    U1TXREG = s[i];
                    LED3=!LED3;
                }
                j++;
            } else {
                j=0;
            }
            
        } else if(command =='y'){
            motoron=0;
        } else if(command =='u'){
            write_duty(read_duty()+50);
        }
    }
}

void test_plotter(void){
    char command;
    int i;
    int fa;
    if(uart_buffer.len>0){
        command = dequeue();
        if(command == 'a'){
            for(i=0;i<1024;i++){
                csdata[i] = read_ADC();
                __delay32(39000);
                LED1 = !LED1;
            }
            LED2 = !LED2;
            j=0;
        } else if(command == 'b'){
            if(j<64){
                fa = j*16;
                char *s = (char *) &csdata[fa];
                for(i=0;i<32;i++){
                    while (U1STAbits.UTXBF); // wait until tx buffer isn't full
                    U1TXREG = s[i];
                    LED3=!LED3;
                }
                j++;
            } else {
                j=0;
            }
            
        }
    }
}