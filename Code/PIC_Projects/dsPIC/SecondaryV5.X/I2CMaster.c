/* The I2C2 module is used to communicate between the dsPIC and the MPU9150 on the PCB in each
 * of the links. The function initialize_I2C_Master configures the dsPIC to be
 * function as the master at 400kHz.
 *
 * The I2C_Write and I2C_Read functions are used to communicated on the channel.
 */

#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CMaster.h"
#include "initializeV5.h"
#include "debug.h"

/* I2C_Write is used for a single write or a burst write. 
 *   -data points to a buffer with the data to be written
 *   -reg is the address of the register on the slave that is being written to
 *   -numbytes is the number of bytes to be written, 1 for a single write
 */
char write_I2C(unsigned char *data, unsigned char reg, int numbytes){
    int i=0;
    char nack;
    int state = 1;
    while(state != I2C_IDLE){
        switch (state){
            case I2C_DEVADDR:
                start_I2C();
                nack = sendOneByte_I2C(MPUSLAVEADDR | W);//Send slave address and a write command
                if(nack){ //If slave did not reply with an ACK
                    log_error(ERR_I2C_ADDNACK1); //If NACK, log error
                    stop_I2C();                  //Restart I2C comm sequence
                    start_I2C();
                    nack = 0;
                    nack = sendOneByte_I2C(MPUSLAVEADDR | W); //Attempt a second try
                }
                state = I2C_REGADDR;
                break;
            case I2C_REGADDR:
                nack = sendOneByte_I2C(reg);
                state = I2C_DATA;
                break;
            case I2C_DATA:
                while((i<numbytes) && !nack){//while no nack, send bytes from data buffer
                    nack = sendOneByte_I2C(data[i]);  //send data for burst write
                    i++;
                }
                if(!nack){
                    stop_I2C();
                }
                state = I2C_IDLE;
                break;
        }
        if(nack){
            switch (state){
                case I2C_REGADDR:
                    log_error(ERR_I2C_ADDNACK2);
                    break;
                case I2C_DATA:
                    log_error(ERR_I2C_DATANACK);
                    break;
                case I2C_IDLE:
                    log_error(ERR_I2C_DATANACK);
                    break;
            }
            stop_I2C();
            break;
        }
    }
    if(I2C1STATbits.IWCOL){ //Check for write collision error
        log_error(ERR_I2C_IWCOL); //log error
        I2C1STATbits.IWCOL=0;     //Clear flag status bit
    }
    if(I2C1STATbits.I2COV){ //Check for receive buffer overflow error
        log_error(ERR_I2C_I2COV); //log error
        I2C1STATbits.I2COV=0;     //Clear flag status bit
    }
    return !nack;
}

/* I2C_Read is used for a single read or a burst read.
 *   -data points to an empty buffer large enough to hold the entire packet
 *   -reg is the address of the register on the slave that is being read from
 *   -numbytes is the number of bytes to be read, 1 for a single read
 */
char read_I2C(unsigned char *data, unsigned char reg, int numbytes){
    int i=0;
    char nack;
    int state = 1;
    while(state > 0){
        switch (state){
            case I2C_DEVADDR:
                start_I2C();
                nack = sendOneByte_I2C(MPUSLAVEADDR | W);//Send slave address and a write command
                if(nack){ //If slave did not reply with an ACK
                    log_error(ERR_I2C_ADDNACK1); //If NACK, log error
                    stop_I2C();                  //Restart I2C comm sequence
                    start_I2C();
                    nack = 0;
                    nack = sendOneByte_I2C(MPUSLAVEADDR | W); //Attempt a second try
                }
                state = I2C_REGADDR;
                break;
            case I2C_REGADDR:
                nack = sendOneByte_I2C(reg);
                state = I2C_RESTART;
                break;
            case I2C_RESTART:
                repeatStart_I2C();
                nack = sendOneByte_I2C(MPUSLAVEADDR | R); //Send slave address with a read command
                state = I2C_DATA;
                break;
            case I2C_DATA:
                while((i<(numbytes-1)) && !nack){    //Read bytes from slave, place in data
                    nack = receiveOneByte_I2C(data+i,0); //respond with ACK
                    i++;
                }
                if(!nack){
                    nack = receiveOneByte_I2C(data+i,1); //Read final byte from slave, place in data
                                                //respond with NACK
                    stop_I2C();
                }
                state = I2C_IDLE;
                break;
        }
        if(nack){
            switch (state){
                case I2C_REGADDR:
                    log_error(ERR_I2C_ADDNACK2);
                    break;
                case I2C_RESTART:
                    log_error(ERR_I2C_DATANACK);
                    break;
                case I2C_DATA:
                    log_error(ERR_I2C_RADDNACK);
                    break;
                case I2C_IDLE:
                    log_error(ERR_I2C_DATANACK);
                    break;
            }
            stop_I2C();
            break;
        }
    }
    if(I2C1STATbits.IWCOL){ //Check for write collision error
        log_error(ERR_I2C_IWCOL); //log error
        I2C1STATbits.IWCOL=0;     //Clear flag status bit
    }
    if(I2C1STATbits.I2COV){ //Check for receive buffer overflow error
        log_error(ERR_I2C_I2COV); //log error
        I2C1STATbits.I2COV=0;     //Clear flag status bit
    }
    return nack;
}

void initialize_I2C_Master(void){
    //Configure I2C Master baud rate
    //Fcy is set to 40 MHz
    //FSCL should be 400kHz
    //I2C1BRG = (((1/FSCL)-120ns)*FCY)-2 = 94
    I2C1BRG = 94;
    I2C1CONbits.I2CEN = 1; //Enable I2C2 Module
}

void start_I2C(void){
    //log_error(ERR_I2C_START);
    if(I2C1STATbits.S){          //If bus state is not idle
       I2C1CONbits.PEN = 1;      //Initiate stop event
       log_error(ERR_I2C_BUSY1);
    }
    if(!I2C1STATbits.S){         //If bus is idle
        I2C1CONbits.SEN = 1;     //Initiate start event
        while(I2C1CONbits.SEN);  //Wait until the end of the start event
    }
    else{                        //If bus is still not idle
       log_error(ERR_I2C_BUSY2);
    }
}

void repeatStart_I2C(void){
    //log_error(ERR_I2C_RESTART);
    I2C1CONbits.RSEN = 1;        //Initiate repeat start event
    while(I2C1CONbits.RSEN);     //Wait until the end of the repeat start event
}

void stop_I2C(void){
    //log_error(ERR_I2C_STOP);
    I2C1CONbits.PEN = 1;        //Initiate stop event
    while(I2C1CONbits.PEN);     //Wait for the end of the stop event
}

/* Sends a single byte. Returns the slave's acknowledge response where 1 is NACK
 * (not-acknowledge).
 *    data is the byte to be sent  */
char sendOneByte_I2C(unsigned char data){
    long i=0;
    //log_error(ERR_I2C_WRITE);
    if(!I2C1STATbits.TBF){           //Check that transmit buffer is not full
        I2C1TRN = data;              //Load transmit buffer with data
        while(I2C1STATbits.TRSTAT && (i<I2C_TIMEOUT)){  //Wait for transmit to complete
            i++;
        }
        if(i==I2C_TIMEOUT){          //If the transmit times out
            log_error(ERR_I2C_TRNTMOUT); //log error
            return 1;
        }
        return I2C1STATbits.ACKSTAT; //Return slave's acknowledge response
    } else {                         //If the transmit buffer is full
        log_error(ERR_I2C_TBF);      //log error
        return 1;
    }
}    

/* Reads one byte and stores it in the location pointed to by data.
   Also, sends the Ack response where 1 is NACK (not-acknowledge).
   Returns a char that is zero if the data was received properly and
   1 if data was not received and the function timed out. */
char receiveOneByte_I2C(unsigned char *data, char Ack){
    long i=0;
    char error;
    //log_error(ERR_I2C_READ);
    I2C1CONbits.RCEN = 1;    //Enable recieve
    while(!I2C1STATbits.RBF && (i<I2C_TIMEOUT)){//Wait until rcv register is full
        i++;                                    // or timeout
    }
    if(i==I2C_TIMEOUT){
        log_error(ERR_I2C_RCVTMOUT);
        *data = 0;
        error = 1;
    } else {
        *data = I2C1RCV;         //Save recieved byte to data. Clears RCEN and RBF
        I2C1CONbits.ACKDT = Ack; //Load ACK or NACK
        I2C1CONbits.ACKEN = 1;   //Send ACK or NACK
        while(I2C1CONbits.ACKEN);//Wait for the end of acknowledge
        error = 0;
    }
    return error;
}

