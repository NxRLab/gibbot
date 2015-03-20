
#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "current_control.h"

int main(void) {
    
    initialize();
    unsigned char b = 'x';

    write_duty(0);
    motoron=0;
    direction = CW;

    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;

    printf("%s %s\rHi! Welcome to the current control menu. Please press the number corresponding to your choice.\r1 = Idle\r2 = PWM Select\r3 = Tuning\r4 = Activate PI controller\r\n", __DATE__, __TIME__);


    while(1){ //The actual running menu portion is currently commented out to test the controller output. 

        test_output(); 
        delay_ms(10000);
        LED1=!LED1;



//MENU

        /*if (USER){
            motoron=0;
            LED1=!LED1;
        }

        b = read_UART();    //read command from UART
        
        if (b=='1'){
            printf("Motor is in Idle mode.\r\n");
            write_duty(0);
            b='x';
        }

        if (b=='2'){
            printf("PWM mode selected. the motor is running at 10 percent duty.\rpress 'u' to increase it by 10, or press 'd' to decrease it by 10.\rpress'q' to quit.\r\n");
            motoron=1;
            write_duty(100);
            kick();
        while (b=='2'){
            int x = read_UART();
            if (x=='u'){
                write_duty(read_duty()+100);
            }
            else if (x=='d'){
                write_duty(read_duty()-100);
            }
            else if (x=='q'){
                write_duty(0);
                motoron=0;
                b='x';
                printf("PWM mode exited.\r\n");
            }
            }
            }

        if (b=='3'){
            printf("Tuning mode selected.");
            tune='1';
            track_wave(refcurrent);
            motoron=1;
            write_duty(10);
            kick();
            timer1_on();
            while(1);
        }

        if (b=='4'){
            printf("PI controller activated.");
			run='1';
            motoron=1;
            write_duty(10);
            kick();
            timer1_on();
            while(1);
        }

        else if (b=='x'){
            LED4=!LED4;
            continue;
        }*/
    }
    


}