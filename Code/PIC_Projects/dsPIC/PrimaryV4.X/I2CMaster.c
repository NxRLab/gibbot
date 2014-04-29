/* The I2C2 module is used to communicate between the dsPICs on the PCB in each
 * of the links. The function Initialize_I2C_Master configures the dsPIC to be
 * function as the master at 400kHz.
 *
 * The I2C_Write and I2C_Read functions are used to communicated on the channel.
 */

#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CMaster.h"
#include "initialize.h"

#define SLAVEADDR 0b11011010
#define R 1
#define W 0

/* I2C_Write is used for a single write or a burst write. 
 *    *data points to a buffer with the data to be written
 *    reg is the address of the register on the slave that is being written to
 *    numbytes is the number of bytes to be written, 1 for a single write
 */
void I2C_Write(unsigned char *data, unsigned char reg, int numbytes){
    int i;
    I2C_Start();                   //begin communication sequence
    I2C_SendOneByte(SLAVEADDR | W);//Send slave address and a write command
    I2C_SendOneByte(reg);          //send register to be written to, this is the
                                   //first register written to in a burst write
    for(i=0;i<numbytes;i++){       //send bytes from data buffer
        I2C_SendOneByte(data[i]);
    }
    I2C_Stop();                    //end communication sequence
}

/* I2C_Read is used for a single read or a burst read.
 *    *data points to an empty buffer large enough to hold the entire packet
 *    reg is the address of the register on the slave that is being read from
 *    numbytes is the number of bytes to be read, 1 for a single read
 */
void I2C_Read(unsigned char *data, unsigned char reg, int numbytes){
    int i;
    I2C_Start();                    //begin communication sequence
    I2C_SendOneByte(SLAVEADDR | W); //Send slave address and a write command
    I2C_SendOneByte(reg);           //send register to be read from, this is the
                                    //first register read from in a burst write
    I2C_RepeatStart();              //restart communication sequence
    I2C_SendOneByte(SLAVEADDR | R); //Send slave address with a read command
    for(i=0;i<(numbytes-1);i++){    //Read bytes from slave and place in data
        I2C_ReceiveOneByte(&data[i],0); //response with ACK
    }
    I2C_ReceiveOneByte(&data[i],1); //Read final byte from slave, place in data
                                    //respond with NACK
    I2C_Stop();                     //end communication sequence
}

void Initialize_I2C_Master(void){
    //Configure I2C Master baud rate
    //Fcy is set to 40 MHz
    //FSCL should be 400kHz
    //I2C1BRG = (((1/FSCL)-120ns)*FCY)-2 = 94
    //BRG was recalibrated to 95 based on tests.
    I2C2BRG = 95;
    I2C2CONbits.I2CEN = 1; //Enable I2C2 Module
}

void I2C_Start(void){
    if(I2C2STATbits.S){          //If bus state is not idle
       I2C2CONbits.PEN = 1;      //Initiate stop event
       //GENERATE ERROR
    }
    if(!I2C2STATbits.S){         //Ensure bus state is now idle
        I2C2CONbits.SEN = 1;     //Initiate start event
        while(I2C2CONbits.SEN);  //Wait until the end of the start event
    }
    else{                        //If bus is still not idle
       //GENERATE ERROR
    }
}

void I2C_RepeatStart(void){ 
    I2C2CONbits.RSEN = 1;        //Initiate repeat start event
    while(I2C2CONbits.RSEN);     //Wait until the end of the repeat start event
}

void I2C_Stop(void){
    I2C2CONbits.PEN = 1;        //Initiate stop event
    while(I2C2CONbits.PEN);     //Wait for the end of the stop event
}

/* Sends a single byte. Returns the slave's acknowledge response where 1 is NACK
 * (not-acknowledge).
 *    data is the byte to be sent  */
char I2C_SendOneByte(unsigned char data){    
    if(!I2C2STATbits.TBF){           //Check that transmit buffer is not full
        I2C2TRN = data;              //Load transmit buffer with data
        while(I2C2STATbits.TRSTAT);  //Wait for transmit to complete
        return I2C2STATbits.ACKSTAT; //Return slave's acknowledge response
    } else {                         //If the transmit buffer is full
        //GENERATE ERROR
        return 1;
    }
}    

/* Reads one byte and stores it in the variable location pointed to by data.
   Also sends the Ack response where 1 is NACK (not-acknowledge). */
void I2C_ReceiveOneByte(unsigned char *data, char Ack){
    
    I2C2CONbits.RCEN = 1;    //Enable recieve

    while(!I2C2STATbits.RBF);//Wait until recieve register is full
    
    *data = I2C2RCV;         //Save recieved byte to data. Clears RCEN and RBF

    I2C2CONbits.ACKDT = Ack; //Load ACK or NACK
    I2C2CONbits.ACKEN = 1;   //Send ACK or NACK
    while(I2C2CONbits.ACKEN);//Wait for the end of acknowledge
}

