/* First iteration of code to go with the Gibbot v4 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */
#include <libpic30.h>
#include <p33Exxxx.h>
#include "initialize.h"
#include "motor.h"
#include "XBee.h"
#include "currentsensor.h"
#include "I2CMaster.h"

int send;

int main(void) {
    //Set the calibration bits for phase lock loop
    //Clock frequency is set at 80MHz
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    PLLFBDbits.PLLDIV = 42;  // M = 44
    CLKDIVbits.PLLPOST = 0;  // N2 = 2
    initialize();
//    int data[10];
//    int ave;
//    int i;
//    int i2;
//    char sendstr[7];
//    int n;
    unsigned char data[256];
    unsigned char *dataddress;
    dataddress = &data[0];
    long i;
    int j;
    for(j=0;j<256;j++){
        data[j] = j;
    }
    while (1){

        if(USER){
            I2C_Read(dataddress, 12, 5);
        }
        for(i=0; i < 1000000; i++);
//        for(i = 0; i<10; i++){
//            data[i] = ADC_Read();
//            ave = 0;
//            for(i2 = 0; i2<10; i2++){
//                ave = ave+data[i2];
//            }
//
//            n = sprintf(sendstr,"%5i\r\n",ave);
//            char *s = (char *) &sendstr;
//            int j;
//            for (j = 0; j < n; j++) {
//                while (U1STAbits.UTXBF); // wait until tx buffer isn't full
//                U1TXREG = s[j];
//            }
//        }
//        long i3;
//        for(i3=0; i3 < 10000;i3++);
    }
    return 0;
}
