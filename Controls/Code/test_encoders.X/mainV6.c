/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include <stdio.h>
#include "ControlLib.h"

#define TOPMAG_ON (TOPMAG = 1)
#define BOTMAG_ON (write_UART2('1'))

#define TOPMAG_OFF (TOPMAG = 0)
#define BOTMAG_OFF (write_UART2('2'))

int main(void) {
    long test_data1 = 0;
    long test_data2 = 0;
    //initialize all peripherals, encoder values
    initialize();

    TOPMAG_OFF;
    BOTMAG_OFF;

    printf("hello world!\n");
    while (1) {
       /*
        if (USER){
            TOPMAG_ON;
            BOTMAG_ON;
            timer1_on();    //encoder reading is in ISR in time.c
        }
       */
        TOPMAG_ON;

         //read topmag encoder encoder
        test_data1 = read_TOPMAGENC();
        //test_data2 = read_LOWMAGENC();


    //store to an array rather than print to screen every time
    /*if (count<(sizeof(angles)/sizeof(int))){
        angles[count] = test_angle;
    }
    else{
        int i =0;
        for(i; i<(sizeof(angles)/sizeof(int)); i++){
            printf("%d \n",angles[i]);
        }
        count=0;
    }*/

    printf("Top: %ld  Bottom: %ld\n",test_data1,test_data2);

    __delay32(20000000);
       
        //press reset to end code
    }
    return 0;
}
