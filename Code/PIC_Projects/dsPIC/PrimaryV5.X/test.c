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

typedef struct {
    int low_ang;
    int mot_ang;
    int top_ang;
    float current;
    float torque;
    float mot_temp;
    float batt_volt;
    double accel_x;
    double accel_y;
    double accel_z;
    double gyro_x;
    double gyro_y;
    double gyro_z;
    double accel_xs;
    double accel_ys;
    double accel_zs;
    double gyro_xs;
    double gyro_ys;
    double gyro_zs;
} Sensor_data;

typedef struct {
    double accel_xs;
    double accel_ys;
    double accel_zs;
    double gyro_xs;
    double gyro_ys;
    double gyro_zs;
} IMU_data;

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
            printf("%5.2f\n",ADC_to_current(data));
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
          LED4 = !LED4;
          unsigned char d1[10];
          Sensor_data sensor_data;
          unsigned char send2[500];
          short temp3;
          sensor_data.low_ang = encoder_to_angle(read_LOWMAGENC(),'l');
          sensor_data.mot_ang = encoder_to_angle(read_MOTENC(),'m');
          sensor_data.top_ang = encoder_to_angle(read_TOPMAGENC(),'t');
          temp3 = read_ADC();
          sensor_data.current = ADC_to_current(temp3);
          sensor_data.torque = ADC_to_torque(temp3);
          sensor_data.mot_temp = 98.62;
          sensor_data.batt_volt = 12.54;
          //read_Accel(d1);
          //sensor_data.accel_x = Accel_convert(d1,0,1);
          //sensor_data.accel_y = Accel_convert(d1,2,3);
          //sensor_data.accel_z = Accel_convert(d1,4,5);
          sensor_data.accel_x = 2.32;
          sensor_data.accel_y = -1.43;
          sensor_data.accel_z = 0.50;
          //read_Gyro(d1);
          //sensor_data.gyro_x = Gyro_convert(d1,0,1);
          //sensor_data.gyro_y = Gyro_convert(d1,2,3);
          //sensor_data.gyro_z = Gyro_convert(d1,4,5);
          sensor_data.gyro_x = 1.22;
          sensor_data.gyro_y = 15.55;
          sensor_data.gyro_z = 9.87;
          read_Accel_Secondary(d1);
          sensor_data.accel_xs = Accel_convert(d1,0,1);
          sensor_data.accel_ys = Accel_convert(d1,2,3);
          sensor_data.accel_zs = Accel_convert(d1,4,5);
          read_Gyro_Secondary(d1);
          sensor_data.gyro_xs = Gyro_convert(d1,0,1);
          sensor_data.gyro_ys = Gyro_convert(d1,2,3);
          sensor_data.gyro_zs = Gyro_convert(d1,4,5);
          sprintf(send2,"%i %i %i %05.2f %05.2f %5.2f %4.2f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f %5.4f\n",sensor_data.low_ang,sensor_data.mot_ang,sensor_data.top_ang,sensor_data.current,sensor_data.torque,sensor_data.mot_temp,sensor_data.batt_volt,sensor_data.accel_x,sensor_data.accel_y,sensor_data.accel_z,sensor_data.gyro_x,sensor_data.gyro_y,sensor_data.gyro_z,sensor_data.accel_xs,sensor_data.accel_ys,sensor_data.accel_zs,sensor_data.gyro_xs,sensor_data.gyro_ys,sensor_data.gyro_zs);
          printf("%s",send2);
          LED4 = !LED4;
      } else if(command == 'y'){
          initialize_ADC_Offset();
      } else if(command == 'z'){
          unsigned char d1[5];
          read_MPU_test(d1);
      } else if(command == 'x'){
          unsigned char d1[10];
          IMU_data imu;
          char *send = &imu;
          //,send[50];
          //double accel_xs,accel_ys,accel_zs,gyro_xs,gyro_ys,gyro_zs;
          read_Accel_Secondary(d1);
          imu.accel_xs = Accel_convert(d1,0,1);
          imu.accel_ys = Accel_convert(d1,2,3);
          imu.accel_zs = Accel_convert(d1,4,5);
          read_Gyro_Secondary(d1);
          imu.gyro_xs = Gyro_convert(d1,0,1);
          imu.gyro_ys = Gyro_convert(d1,2,3);
          imu.gyro_zs = Gyro_convert(d1,4,5);
          //sprintf(send,"%5.4f %5.4f %5.4f %5.4f %5.4f %5.4f\n",accel_xs,accel_ys,accel_zs,gyro_xs,gyro_ys,gyro_zs);
          //printf("%s",send);
           for (i=0; i<sizeof(imu);i++){
              write_UART(send[i]);
          }
      } else if(command == 'r'){
          LED4 = !LED4;
          unsigned char d1[10];
          Sensor_data sensor_data;
          char *send = &sensor_data;
          short temp3;
          sensor_data.low_ang = encoder_to_angle(read_LOWMAGENC(),'l');
          sensor_data.mot_ang = encoder_to_angle(read_MOTENC(),'m');
          sensor_data.top_ang = encoder_to_angle(read_TOPMAGENC(),'t');
          temp3 = read_ADC();
          sensor_data.current = ADC_to_current(temp3);
          sensor_data.torque = ADC_to_torque(temp3);
          sensor_data.mot_temp = 98.62;
          sensor_data.batt_volt = 12.54;
          //read_Accel(d1);
          //sensor_data.accel_x = Accel_convert(d1,0,1);
          //sensor_data.accel_y = Accel_convert(d1,2,3);
          //sensor_data.accel_z = Accel_convert(d1,4,5);
          sensor_data.accel_x = 2.32;
          sensor_data.accel_y = -1.43;
          sensor_data.accel_z = 0.50;
          //read_Gyro(d1);
          //sensor_data.gyro_x = Gyro_convert(d1,0,1);
          //sensor_data.gyro_y = Gyro_convert(d1,2,3);
          //sensor_data.gyro_z = Gyro_convert(d1,4,5);
          sensor_data.gyro_x = 1.22;
          sensor_data.gyro_y = 15.55;
          sensor_data.gyro_z = 9.87;
          read_Accel_Secondary(d1);
          sensor_data.accel_xs = Accel_convert(d1,0,1);
          sensor_data.accel_ys = Accel_convert(d1,2,3);
          sensor_data.accel_zs = Accel_convert(d1,4,5);
          read_Gyro_Secondary(d1);
          sensor_data.gyro_xs = Gyro_convert(d1,0,1);
          sensor_data.gyro_ys = Gyro_convert(d1,2,3);
          sensor_data.gyro_zs = Gyro_convert(d1,4,5);
          for (i=0; i<sizeof(Sensor_data);i++){
              write_UART(send[i]);
          }
      } else if(command == 's'){
          unsigned char d1[50];
          sprintf(d1,"%s","11111111111111111111111111111111111111111111111111111111111");
          printf("%s",d1);
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