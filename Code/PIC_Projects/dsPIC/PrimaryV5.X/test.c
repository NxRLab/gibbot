#include <libpic30.h>
#include <stdio.h>
#include <string.h>
#include <p33EP512MC806.h>
#include "UART.h"
#include "test.h"
#include "initializeV5.h"
#include "motor.h"
#include "ADC.h"
#include "encoder.h"
#include "debug.h"
#include "MPU.h"
#include "I2CMaster.h"

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
            write_UART(data);
            write_UART(data>>8);
            printf("%u\n",Avi);
            printf("%i\n",(Avi - data));
            printf("%i\n",ADC_to_current(data));
        } else if(command=='1'){ //Set Encoder Values
            write_LOWMAGENC(1600);
            write_MOTENC(1700);
            write_TOPMAGENC(1800);
        } else if(command=='2'){ // Read Encoder Values
            temp = read_LOWMAGENC();
            write_UART(temp);
            write_UART(temp>>8);
            write_UART(temp>>16);
            write_UART(temp>>24);
            temp = read_MOTENC();
            write_UART(temp);
            write_UART(temp>>8);
            write_UART(temp>>16);
            write_UART(temp>>24);
            temp = read_TOPMAGENC();
            write_UART(temp);
            write_UART(temp>>8);
            write_UART(temp>>16);
            write_UART(temp>>24);
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
        /*} else if(command=='a'){ //Pass through test, 256 single reads
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
            LED4 = 1;*/
        } else if(command=='c'){ //Toggle Top Magnet
            TOPMAG = !TOPMAG;
        } else if(command=='d'){ //Turn on Top Magnet
            TOPMAG = 1;
        } else if(command=='e'){ //Turn off Top Magnet
            TOPMAG = 0;
        } else if(command=='f'){ //Toggle Bottom Magnet
            unsigned char as;
            write_UART2('3');
            while(!(uart_buffer.len>0));
            as = read_UART();
            write_UART(as);
            //datachar = 2;
            //write_I2C(&datachar, LOWMAGCON, 1);
        } else if(command=='g'){ //Turn on Bottom Magnet
            write_UART2('1');
            //datachar = 1;
            //write_I2C(&datachar, LOWMAGCON, 1);
        } else if(command=='h'){ //Turn off Bottom Magnet
            write_UART2('2');
            //datachar = 0;
            //write_I2C(&datachar, LOWMAGCON, 1);
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
            
      } else if(command == 'n'){
          unsigned char d1[5];
          write_UART2('8');
          while(!(uart_buffer.len>4));
          read_string_UART(d1,5);
          printf("%s\n",d1);
      } else if(command == 'q'){
          unsigned char send[200],d1[10];
          short temp3;
          //int temp2;
          int low_ang,mot_ang,top_ang,current,torque;
          double mot_temp,batt_volt;
          double accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z,accel_xs,accel_ys,accel_zs,gyro_xs,gyro_ys,gyro_zs;
          low_ang = encoder_to_angle(read_LOWMAGENC(),'l');
          //send[0] = temp2;
          //send[1] = temp2 >> 8;
          mot_ang = encoder_to_angle(read_MOTENC(),'m');
          //send[2] = temp2;
          //send[3] = temp2 >> 8;
          top_ang = encoder_to_angle(read_TOPMAGENC(),'t');
          //send[4] = temp2;
          //send[5] = temp2 >> 8;
          temp3 = read_ADC();
          current = ADC_to_current(temp3);
          //send[6] = temp2;
          //send[7] = temp2 >> 8;
          torque = ADC_to_torque(temp3);
          //send[8] = temp2;
          //send[9] = temp2 >> 8;
          mot_temp = 98.62;
          batt_volt = 12.54;
          /*send[10] = 0xFF;
          send[11] = 0xFF;
          send[12] = 0xFF;
          send[13] = 0xFF;
          send[14] = 0xFF;
          send[15] = 0xFF;
          send[16] = 0xFF;
          send[17] = 0xFF;
          send[18] = 0xFF;
          send[19] = 0xFF;
          send[20] = 0xFF;
          send[21] = 0xFF;
          send[22] = 0xFF;
          send[23] = 0xFF;
          send[24] = 0xFF;
          send[25] = 0xFF;*/
          read_Accel(d1);
          accel_x = Accel_convert(d1,0,1);
          accel_y = Accel_convert(d1,2,3);
          accel_z = Accel_convert(d1,4,5);
          read_Gyro(d1);
          gyro_x = Gyro_convert(d1,0,1);
          gyro_y = Gyro_convert(d1,2,3);
          gyro_z = Gyro_convert(d1,4,5);
          read_Accel_Secondary(d1);
          accel_xs = Accel_convert(d1,0,1);
          accel_ys = Accel_convert(d1,2,3);
          accel_zs = Accel_convert(d1,4,5);
          read_Gyro_Secondary(d1);
          gyro_xs = Gyro_convert(d1,0,1);
          gyro_ys = Gyro_convert(d1,2,3);
          gyro_zs = Gyro_convert(d1,4,5);
          //write_string_UART(send,26);
          sprintf(send,"%i %i %i %i %i %5.2f %4.2f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f\n",low_ang,mot_ang,top_ang,current,torque,mot_temp,batt_volt,accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z,accel_xs,accel_ys,accel_zs,gyro_xs,gyro_ys,gyro_zs);
          printf("%s",send);
      } else if(command == 'y'){
          initialize_ADC_Offset();
      } else if(command == 'z'){
          unsigned char d1[5];
          read_MPU_test(d1);
      } else if(command == 'x'){
          unsigned char d1[10],d2[3],d3[10],d4[3];
          double s1,s2;
          unsigned int s;
          read_Gyro(d1);
          read_Accel(d3);
          d2[0] = d1[4];
          d2[1] = d1[5];
          s = d1[5] << 8 | d1[4];
                  //Gyro_convert(d2);
          d4[0] = d3[4];
          d4[1] = d3[5];
          //s2 = Accel_convert(d4);-----------------------
          //printf("%u %f",s,s2);
      } else if(command == 'r'){
          unsigned char d1[10];
          double s;
          write_UART2('9');
          while(!(uart_buffer.len>5));
          read_string_UART(d1,6);
          s = d1[1] << 8 | d1[0];
          s = 4.8828125e-04 * s;
          printf("%f",s);
      } else if(command == 's'){
          unsigned char d1[10];
          double s;
          write_UART2('a');
          while(!(uart_buffer.len>5));
          read_string_UART(d1,6);
          s = d1[1] << 8 | d1[0];
          s = .0609756098 * s;
          printf("%f",s);
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