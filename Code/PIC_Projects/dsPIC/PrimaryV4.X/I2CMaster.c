/* The I2C2 module is used to communicate between the dsPICs on the PCB in each
 * of the links. The function initialize_I2C_Master configures the dsPIC to be
 * function as the master at 400kHz.
 *
 * The I2C_Write and I2C_Read functions are used to communicated on the channel.
 */

#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CMaster.h"
#include "initialize.h"
/* I2C_Write is used for a single write or a burst write. 
 *   -data points to a buffer with the data to be written
 *   -reg is the address of the register on the slave that is being written to
 *   -numbytes is the number of bytes to be written, 1 for a single write
 */
void write_I2C(unsigned char *data, unsigned char reg, int numbytes){
    int i;
    start_I2C();                   //begin communication sequence
    sendOneByte_I2C(SLAVEADDR | W);//Send slave address and a write command
    sendOneByte_I2C(reg);          //send register to be written to, this is the
                                   //first register written to in a burst write
    for(i=0;i<numbytes;i++){       //send bytes from data buffer
        sendOneByte_I2C(data[i]);  //send data for burst write
    }
    stop_I2C();                    //end communication sequence
}

/* I2C_Read is used for a single read or a burst read.
 *   -data points to an empty buffer large enough to hold the entire packet
 *   -reg is the address of the register on the slave that is being read from
 *   -numbytes is the number of bytes to be read, 1 for a single read
 */
void read_I2C(unsigned char *data, unsigned char reg, int numbytes){
    int i;
    start_I2C();                    //begin communication sequence
    sendOneByte_I2C(SLAVEADDR | W); //Send slave address and a write command
    sendOneByte_I2C(reg);           //send register to be read from, this is the
                                    //first register read from in a burst write
    repeatStart_I2C();              //restart communication sequence
    sendOneByte_I2C(SLAVEADDR | R); //Send slave address with a read command
    for(i=0;i<(numbytes-1);i++){    //Read bytes from slave and place in data
        receiveOneByte_I2C(&data[i],0); //respond with ACK
    }
    receiveOneByte_I2C(&data[i],1); //Read final byte from slave, place in data
                                    //respond with NACK
    stop_I2C();                     //end communication sequence
}

void initialize_I2C_Master(void){
    //Configure I2C Master baud rate
    //Fcy is set to 40 MHz
    //FSCL should be 400kHz
    //I2C1BRG = (((1/FSCL)-120ns)*FCY)-2 = 94
    //BRG was recalibrated to 95 based on tests.
    I2C2BRG = 95;
    I2C2CONbits.I2CEN = 1; //Enable I2C2 Module
}

void start_I2C(void){
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

void repeatStart_I2C(void){
    I2C2CONbits.RSEN = 1;        //Initiate repeat start event
    while(I2C2CONbits.RSEN);     //Wait until the end of the repeat start event
}

void stop_I2C(void){
    I2C2CONbits.PEN = 1;        //Initiate stop event
    while(I2C2CONbits.PEN);     //Wait for the end of the stop event
}

/* Sends a single byte. Returns the slave's acknowledge response where 1 is NACK
 * (not-acknowledge).
 *    data is the byte to be sent  */
char sendOneByte_I2C(unsigned char data){
    if(!I2C2STATbits.TBF){           //Check that transmit buffer is not full
        I2C2TRN = data;              //Load transmit buffer with data
        while(I2C2STATbits.TRSTAT);  //Wait for transmit to complete
        return I2C2STATbits.ACKSTAT; //Return slave's acknowledge response
    } else {                         //If the transmit buffer is full
        //GENERATE ERROR
        return 1;
    }
}    

/* Reads one byte and stores it in the location pointed to by data.
   Also, sends the Ack response where 1 is NACK (not-acknowledge). */
void receiveOneByte_I2C(unsigned char *data, char Ack){    
    I2C2CONbits.RCEN = 1;    //Enable recieve
    while(!I2C2STATbits.RBF);//Wait until recieve register is full   
    *data = I2C2RCV;         //Save recieved byte to data. Clears RCEN and RBF
    I2C2CONbits.ACKDT = Ack; //Load ACK or NACK
    I2C2CONbits.ACKEN = 1;   //Send ACK or NACK
    while(I2C2CONbits.ACKEN);//Wait for the end of acknowledge
}

