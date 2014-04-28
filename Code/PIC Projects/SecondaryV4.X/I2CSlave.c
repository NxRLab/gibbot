#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CSlave.h"
#include "initialize.h"
#include "encoder.h"
/* Initialize the I2C2 module at 400kHz for communicating with the primary
   board. */

unsigned char RegBuffer[256];
char nextByteData=0;
char nextByteAddr=0;
unsigned char *RegPtr;

void initialize_I2C_Slave(void){
    I2C2ADD = 0b1101101;    //Sets the 7 bit slave address
    RegPtr = &RegBuffer[0]; //Reg pointer points to beginning of RegBuffer
    int j;
    for(j=0;j<256;j++){
        RegBuffer[j] = 255-j;
    }
    IFS3bits.SI2C2IF = 0;   //Clear interrupt flag
    IPC12bits.SI2C2IP = 7;  //Set priority to 6
    IEC3bits.SI2C2IE = 1;   //Enable I2C 2 Slave interrupt

    I2C2CONbits.I2CEN = 1;  //Enable I2C 2

}

/* This function handles all slave side I2C communication. The SI2C2Interrupt
 * is called when the slave detects a start condition, a stop condition, an
 * address byte, a data byte,
 *
 */

void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {
    /* I2C module will read to detect the address 11011010 being sent by the
     * master. The final bit of the address is the Read/Write
     * bit which is interpreted by the module.
     *   1101101R
     */
    int i;
    unsigned char tempvar = 0;
    if(!I2C2STATbits.R_W){      //If Master device is sending a write command
        if(!I2C2STATbits.D_A){ //If byte received was device address
            tempvar = I2C2RCV; //Dummy read to clear RCV register
            nextByteData = 0;
            nextByteAddr = 1;  //The following byte will be the register address
        } else {               //If byte received was data
            if(nextByteAddr){  //If last byte recieved was device address this
                               //byte is the address of the register to be read.
                RegPtr = &RegBuffer[0] + I2C2RCV; //Set pointer to register
                nextByteAddr = 0;
                nextByteData = 1;     //The following byte will be data
            } else if(nextByteData){  //If last byte recieved was register
                                      //address this byte is data to be written
                *RegPtr = (unsigned char)I2C2RCV; //write data to register
                RegPtr = RegPtr + 1;  //Increment pointer by 1 for burst write
            }
        }
    } else {                   //If Master device is sending a read command
        encoder_Read(MOTENC);
        I2C2TRN = *RegPtr;     //Load the transmit register with data
        
        __delay32(12); //Delay for at least 100ns (4 clock cycles)
                       //minimum number of delay cycles for delay32 is 12.
        I2C2CONbits.SCLREL = 1;//Release the clock stretch
        //Wait for the transmit buffer to clear or for a timeout.
        while(I2C2STATbits.TBF && (i < 4000000)){
            i++;
        }
        if(i >= 4000000){ //If timeout indicate with LED and restart I2C module
           LED3 = 0;
           I2C2CONbits.I2CEN = 0;
           I2C2CONbits.I2CEN = 1;
        }
        RegPtr = RegPtr + 1;  //Increment pointer by 1 for burst read
    }
    IFS3bits.SI2C2IF = 0;
}