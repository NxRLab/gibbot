#include <libpic30.h>
#include <p33EP512MC806.h>
#include "I2CMaster.h"
#include "initialize.h"

#define SLAVEADDR 0b11011010
#define MOTENC    0b00000111
#define R 1
#define W 0
/* Initialize the I2C2 module at 400kHz for communicating with the secondary
   board. */

void Initialize_I2C_Master(void){
    //Configure I2C Master baud rate
    //Fcy is set to 40 MHz
    //FSCL should be 400kHz
    //I2C1BRG = (((1/FSCL)-120ns)*FCY)-2 = 94
    //BRG was recalibrated to 95 based on tests.
    I2C2BRG = 95;
    I2C2CONbits.I2CEN = 1;
}

void I2C_Start(void){
    //If bus state is not idle
    if(I2C2STATbits.S){
       //Initiate stop event
       I2C2CONbits.PEN = 1;
       //GENERATE ERROR
    }
    //Ensure bus state is now idle
    if(!I2C2STATbits.S){
        //initiate start event
        I2C2CONbits.SEN = 1;
        //wait until the end of the start event clears the start enable bit
        while(I2C2CONbits.SEN){
        }
    }
    else{
       //GENERATE ERROR
    }
}

void I2C_RepeatStart(void){
    //initiate repeat start event
    I2C2CONbits.RSEN = 1;
    //wait until the end of the start event clears the start enable bit
    while(I2C2CONbits.RSEN){
    }
}

void I2C_Stop(void){
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN){
    }
}

/* Sends a single byte that is passed to the function. Returns the slave's
   acknowledge response where 1 is NACK (not-acknowledge). */
char I2C_SendOneByte(unsigned char data){
    //Check that transmit buffer is not full
    if(!I2C2STATbits.TBF){
        //Load transmit buffer with data
        I2C2TRN = data;
        //Wait for transmit to complete
        while(I2C2STATbits.TRSTAT){
        }
        return I2C2STATbits.ACKSTAT;
    } else {
        //GENERATE ERROR
        return 1;
    }
}    

/* Reads one byte and stores it in the variable location pointed to by data.
   Also sends the Ack response where 1 is NACK (not-acknowledge). */
void I2C_ReceiveOneByte(unsigned char *data, char Ack){
    //Enable recieve
    I2C2CONbits.RCEN = 1;
    //Wait until recieve register is full.
    while(!I2C2STATbits.RBF){
    }
    //Save recieved data to variable. Automatically clears RCEN and RBF
    *data = I2C2RCV;
    //Respond with Acknowledge
    I2C2CONbits.ACKDT = Ack;
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN){
    }
}

void I2C_Write(unsigned char *data, unsigned char reg, int numbytes){
    unsigned char i;
    I2C_Start();
    I2C_SendOneByte(SLAVEADDR | W);
    I2C_SendOneByte(reg);
    for(i=0;i<numbytes;i++){
        I2C_SendOneByte(data[i]);
    }
    LED1 = !LED1;
    I2C_Stop();
}

void I2C_Read(unsigned char *data, unsigned char reg, int numbytes){
    unsigned char i = 0;
    I2C_Start();
    I2C_SendOneByte(SLAVEADDR | W);
    I2C_SendOneByte(reg);
    I2C_RepeatStart();
    I2C_SendOneByte(SLAVEADDR | R);
    for(i=0;i<(numbytes-1);i++){
        I2C_ReceiveOneByte(&data[i],0);
    }
    I2C_ReceiveOneByte(&data[i],1);
    LED1 = !LED1;
    I2C_Stop();
}