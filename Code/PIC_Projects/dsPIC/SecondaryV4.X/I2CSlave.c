/* The I2C module triggers the SI2C interrupt when the first byte in a data
     * package matches the device's slave address. The module will then set the
     * R/W status register based on the last bit in the slave address. The SI2C
     * interrupt will also trigger after each byte following a matched device
     * address.
     */
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CSlave.h"
#include "initialize.h"
#include "encoder.h"

unsigned char RegBuffer[256];
unsigned char *RegPtr;

/* Initialize the I2C2 module at 400kHz for communicating with the primary
   board. */
void initialize_I2C_Slave(void){
    I2C2ADD = SLAVEADDR>>1;    //Sets the 7 bit slave address
    IFS3bits.SI2C2IF = 0;   //Clear interrupt flag
    IPC12bits.SI2C2IP = 5;  //Set priority to 5
    IEC3bits.SI2C2IE = 1;   //Enable I2C 2 Slave interrupt
    I2C2CONbits.I2CEN = 1;  //Enable I2C 2

}

void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {
    /* I2C module will read to detect the address 11011010 being sent by the
     * master. The final bit of the address is the Read/Write
     * bit which is interpreted by the module.
     *   1101101R
     * Each time the interrupt triggers it will run one of the blocks
     * of code below depending on the status registers and a pair of flags.
     *    nextByteAddr is set when the device address is read indicating that
     *       if the master device is writing the next time the interrupt
     *       triggers the RCV register will contain the register address.
     *    nextByteData is set after the register address is received indicating
     *       that if the master device is writing the next time the interrupt
     *       triggers the RCV register will contain data.
     * The code blocks are numbered as follows:
     *    1. Device Address
     *    2. Register Address 
     *    3. Write Data
     *    4. Read Data
     * The sequence for each I2C command is as follows:
     *    Single Write: 123
     *    Single Read: 1214
     *    Burst Write: 123333...
     *    Burst Read: 1214444...
     */
    long i=0;
    static char nextByteData=0;
    static char nextByteAddr=0;
    unsigned char tempvar = 0;
    if(!I2C2STATbits.R_W){      //If Master device is sending a write command
        if(!I2C2STATbits.D_A){ //If byte received was device address
            /***1** Device Address */
            tempvar = I2C2RCV; //Dummy read to clear RCV register
            nextByteData = 0;
            nextByteAddr = 1;  //The following byte will be the register address
            //Update encoder readings at the beginning of each data transmit
            read_encoder();
            LED1 = !LED1;

        } else {               //If byte received was data
            if(nextByteAddr){  //If last byte recieved was device address this
                               //byte is the address of the register to be read.
                /***2** Register Address */
                RegPtr = RegBuffer + I2C2RCV; //Set pointer to register
                nextByteAddr = 0;
                nextByteData = 1;     //The following byte will be data
                LED2 = !LED2;
            } else if(nextByteData){  //If last byte recieved was register
                                      //address this byte is data to be written
                /***3** Write Data */
                *RegPtr = (unsigned char)I2C2RCV; //write data to register
                
                if(RegPtr==&RegBuffer[MOTENC+3]){
                    //Load data into hold register
                    POS2HLD = (RegBuffer[MOTENC+3]<<8) | RegBuffer[MOTENC+2];
                    //load data into CNTL register and transfer data from hold
                    //register to CNTH register
                    POS2CNTL = (RegBuffer[MOTENC+1]<<8) | RegBuffer[MOTENC];
                } else if(RegPtr==&RegBuffer[LOWMAGENC+3]){
                    //Load data into hold register
                    POS1HLD = (RegBuffer[LOWMAGENC+3]<<8) | RegBuffer[LOWMAGENC+2];
                    //load data into CNTL register and transfer data from hold
                    //register to CNTH register
                    POS1CNTL = (RegBuffer[LOWMAGENC+1]<<8) | RegBuffer[LOWMAGENC];
                } else if(RegPtr==&RegBuffer[LOWMAGCON]){
                    if(*RegPtr==0){
                        LOWMAG = 0;
                    } else if(*RegPtr==1){
                        LOWMAG = 1;
                    } else if(*RegPtr==2){
                        LOWMAG = !LOWMAG;
                    }
                }
                RegPtr = RegPtr + 1;  //Increment pointer by 1 for burst write
                LED3 = !LED3;
            }
        }
    } else {               //If Master device is sending a read command
        /***4** Read Data */
        tempvar = I2C2RCV; //Dummy read to clear RCV register
        I2C2TRN = *RegPtr; //Load the transmit register with data
        
        __delay32(12); //Delay for at least 100ns (4 clock cycles)
                       //minimum number of delay cycles for delay32 is 12.
        I2C2CONbits.SCLREL = 1;//Release the clock stretch
        //Wait for the transmit buffer to clear or for a timeout.
        while(I2C2STATbits.TBF && (i < I2C_TIMEOUT)){
            i++;
        }
        if(i == I2C_TIMEOUT){ //If transmit times out
            I2C2CONbits.I2CEN = 0; //Restart I2C module to clear TBF and
            I2C2CONbits.I2CEN = 1; //  TRN buffer
            LED4=0;
        }
        RegPtr = RegPtr + 1;  //Increment pointer by 1 for burst read
    }
    IFS3bits.SI2C2IF = 0;
}