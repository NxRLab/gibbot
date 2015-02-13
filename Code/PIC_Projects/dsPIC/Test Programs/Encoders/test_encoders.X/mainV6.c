/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include <stdio.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
#include "time.h"
#include "UART.h"
#include "encoder.h"

int main(void) {
    initialize();
    
    long test_data;
    int test=0;

    //file initialization
    FILE *outfile;
    outfile = fopen("encoder_test.txt","w");
    fprintf(outfile,"Testing...\n");

    while (1) {
        if (USER=1){
            TOPMAG=1;
            test=1;
        }
        //test code
        if (test=1){
            //read motor encoder
            test_data = read_MOTENC();
            fprintf(outfile,"%ld \n",test_data);
        }
        //press reset to end code
    }
    return 0;
}
