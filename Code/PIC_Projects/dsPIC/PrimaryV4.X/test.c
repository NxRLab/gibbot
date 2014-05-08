#include <libpic30.h>
#include <p33EP512MC806.h>
#include "UART.h"
#include "test.h"
#include "initialize.h"
#include "I2CMaster.h"
#include "motor.h"
#include "ADC.h"
#include "encoder.h"

unsigned char testBuff[256];
short duty=300;
int senddata=0;
unsigned short csdata[1024];
int j=0;

void test_encoder(void){
    unsigned char command;
    unsigned long temp;
    if(uart_buffer.len >0){
        command = read_UART();
        if(command=='a'){
            clear_LOWMAGENC();
        } else if(command=='b'){
            temp = read_LOWMAGENC();
            U1TXREG = temp;
            U1TXREG = temp>>8;
            U1TXREG = temp>>16;
            U1TXREG = temp>>24;
        }
    }
}

void test_MayDay(void){
    unsigned char command;
    unsigned short data;
    unsigned char testdata;
    unsigned char testecho[256];
    static long i=0;
    int ij=0;
    long temp;
    int incr=0;
    if(i>8000){
        if(duty>MDC){
            MDC++;
        } else if(duty<MDC){
            MDC--;
        }
        i=0;
    } else{
        i++;
    }
    if(uart_buffer.len>0){
        command = read_UART();
        LED1 = !LED1;
        if(command =='z'){
            LED2 = 0;
            data = read_ADC();
            U1TXREG = data;
            U1TXREG = data>>8;
            LED2 = 1;
        }
        if(command == 'a'){
            direction = !direction;
            LED2 = !LED2;
        } else if(command =='b'){
            motoron = !motoron;
            kick();
            LED3 = !LED3;
        } else if(command =='q'){
            if(duty<950){
                duty = duty+50;
            } else{
                LED4 = !LED4;
            }
        } else if(command =='w'){
            if(duty>50){
                duty=duty-50;
            } else {
                LED4 = !LED4;
            }
        } else if(command =='1'){
            duty=300;
            kick();
            LED3 = !LED3;
        } else if(command =='2'){
            duty=50;
            LED3 = !LED3;
        } else if(command=='h'){
            while(ij<256){
                if(uart_buffer.len > 0){
                    testdata = read_UART();
                    unsigned char testecho;
                    write_I2C(&testdata, 3, 1);
                    read_I2C(&testecho, 3, 1);
                    U1TXREG = testecho; //echo data
                    ij++;
                }
            }
        } else if(command=='k'){
            while(incr<256){
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
                }
            }
        } else if(command=='u'){
            clear_LOWMAGENC();
        } else if(command=='i'){
            temp = read_LOWMAGENC();
            U1TXREG = temp;
            U1TXREG = temp>>8;
            U1TXREG = temp>>16;
            U1TXREG = temp>>24;
        } else if(command=='m'){
            TOPMAG = !TOPMAG;
        }
    }
}

void test_UART(void){
    static long i;
    if(i>80000){
        U1TXREG=U1STA;
        U1TXREG=U1STA>>8;
        U1TXREG=0xFF;
        i=0;
    }
    i++;
    if(U1STAbits.URXDA == 1){
            U1TXREG = U1RXREG;
    }
}
void test_passthrough(void){
    unsigned char testdata;
    if(uart_buffer.len > 0){
        testdata = read_UART();
        unsigned char testecho;
        write_I2C(&testdata, 3, 1);
        read_I2C(&testecho, 3, 1);
        U1TXREG = testecho; //echo data
    }
}

void test_passthroughburst(void){
    unsigned char testecho[256];
    unsigned char testdata;
    int i;
    static int incr=0;
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
            incr=0;
        }
        
    }
}

void test_motor(void){
    unsigned char command;
    unsigned short data;
    static long i=0;
    if(i>8000){
        if(duty>MDC){
            MDC++;
        } else if(duty<MDC){
            MDC--;
        }
        i=0;
    } else{
        i++;
    }
    if(uart_buffer.len>0){
        command = read_UART();
        LED1 = !LED1;
        if(command == 'a'){
            direction = !direction;
            LED2 = !LED2;
        } else if(command =='b'){
            motoron = !motoron;
            kick();
            LED3 = !LED3;
        } else if(command =='q'){
            if(MDC<1000){
                duty = duty+50;
            } else{
                LED4 = !LED4;
            }
        } else if(command =='w'){
            if(MDC>50){
                duty=duty-50;
            } else {
                LED1 = !LED1;
            }
        } else if(command =='z'){
            LED1 = 0;
            data = read_ADC();
            U1TXREG = data;
            U1TXREG = data>>8;
            LED1 = 1;
        } 
    }
}

void test_HeartBeat(void){
    static long i=0;
//    static long j=0;
//    static char up = 1;
    unsigned char testecho;
    unsigned char *testdata;
    unsigned char data;
    data = 's';
    testdata = &data;
//    if(j>8000){
//        if(up){
//            if(duty>MDC){
//                MDC++;
//            } else{
//                up=0;
//                duty=10;
//            }
//        } else {
//            if(duty<MDC){
//                MDC--;
//            } else{
//                direction=!direction;
//                kick();
//                up=1;
//                duty=1000;
//            }
//        }
//        j=0;
//    } else{
//        j++;
//    }
    if(i>500000){
        LED1 = !LED1;
        if(uart_buffer.len>0){
            U1TXREG = read_UART();
        }else{
            write_I2C(testdata, 3, 1);
            read_I2C(&testecho, 3, 1);
            U1TXREG = testecho; //echo data
        }
        i=0;
    } else{
        i++;
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
            if(MDC>50){
                MDC = MDC+50;
                U1TXREG = MDC;
                U1TXREG = MDC>>8;
            } else {
                LED1 = !LED1;
            }
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