#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "interrupts.h"
#include "peripherals.h"

struct I2C_CONTROL_t I2C_CONTROL; 
int state;
char command;

void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {
    /* I2C module will read to detect the address 1101XXXX being sent by the
     * master. The first four bits are a header that must be recognized. The
     * next three bits are masked and so are ignored by the module. They are
     * used as command bits in the code below. The final bit is the Read/Write
     * bit which is interpreted by the module.
     *   1101ABCR
     * A: 1 turns the magnet on, 0 turns the magnet off
     * B: If 1 the slave will send two bytes with the motor encoder position
     * C: If 1 the slave will send two bytes with the magnet encoder position
     * R: Indicates a read or a write
    */
    int MTRCNT;
    int LOWMAGCNTL;
    int LOWMAGCNTH;
    char timeout;
    char data;
    switch(state){
        case 0:
            //Read address byte
            command = I2C2RCV;
            //If the A bit equals 1 turn on the magnet
            if(command & 0b00001000){
                LOWMAG = 1;
            //If the A bit is 0 turn off the magnet
            } else{
                LOWMAG = 0;
            }
            //If a read command has been sent
            if(I2C2STATbits.R_W){
                //Save encoder values to ensure they don't change during transmission
                MTRCNT = POS1CNTL;
                LOWMAGCNTL = POS2CNTL;
                LOWMAGCNTH = POS2CNTH;

                //If the B bit equals 1 send the motor encoder value
                if(command & 0b00000100){
                    data = MTRCNT>>8;
                    timeout = sendandwait(data);
                    if(!timeout){
                        data = MTRCNT;
                        timeout = sendandwait(data);
                    }
                }
                //If the C bit equals 1 send the magnet encoder value
                if((command & 0b00000010) && !timeout){
                    data = LOWMAGCNTH>>8;
                    timeout = sendandwait(data);
                    if(!timeout){
                        data = LOWMAGCNTH;
                        timeout = sendandwait(data);
                    }
                    if(!timeout){
                        data = LOWMAGCNTL>>8;
                        timeout = sendandwait(data);
                    }
                    if(!timeout){
                        data = LOWMAGCNTL;
                        timeout = sendandwait(data);
                    }
                }
            //If a write command has been sent
            } else {
                I2C2CONbits.SCLREL = 1;
                //If the B bit equals 1 reset the motor encoder value
                if(command & 0b00000100){
                    POS1CNTL = 1800;
                }
                //If the C bit equals 1 reset the magnet encoder value
                if(command & 0b00000010){
                    POS2CNTL = 0;
                }
                LED3 = 0;
            }
    }
    IFS3bits.SI2C2IF = 0;
}