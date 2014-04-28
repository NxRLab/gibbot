#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"

int direction =0;

/* Turns on High state PWM on one the MOSFETs bridges controlling the BLDC
 * motor leads. The motor lead that is set high is determined by the
 * input variable. The MOSFETs are set high by turning off the override
 * setting for the PWM module associated with the chosen pair of outputs.
 */
void High(int pin){
    if(pin == 1){
        IOCON1bits.OVRENH = 0;  //Turn overide off for high pin
        IOCON1bits.OVRENL = 0;  //Turn overide off for low pin
    } else if(pin == 2){
        IOCON2bits.OVRENH = 0;  //Turn overide off for high pin
        IOCON2bits.OVRENL = 0;  //Turn overide off for low pin
    } else if(pin == 3){
        IOCON3bits.OVRENH = 0;  //Turn overide off for high pin
        IOCON3bits.OVRENL = 0;  //Turn overide off for low pin
    }
}

/* Turns on the low side MOSFET driving one of the BLDC motor leads low.
 * The motor lead that is set low is determined by the input variable.
 * The MOSFET bridge is pulled low by turning on the override setting for the
 * PWM module associated with the chosen pair of outputs, turning the high
 * side MOSFET off and turning the low side MOSFET on.
 *
 * Note: The high side control is active low and the low side control is active
 * high as set in the Initialize_PWM function.
 */
void Low(int pin){
    if(pin == 1){
        IOCON1bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON1bits.OVRDAT0 = 1; // PWM Low Pin override output is on
        IOCON1bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON1bits.OVRENL = 1;  //Turn overide on for low pin
    } else if(pin == 2){
        IOCON2bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON2bits.OVRDAT0 = 1; // PWM Low Pin override output is on
        IOCON2bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON2bits.OVRENL = 1;  //Turn overide on for low pin
    } else if(pin == 3){
        IOCON3bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON3bits.OVRDAT0 = 1; // PWM Low Pin override output is on
        IOCON3bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON3bits.OVRENL = 1;  //Turn overide on for low pin
    }
}

/* Turns off both MOSFETs leaving one of the BLDC motor leads floating.
 * The motor lead that is floating is determined by the input variable.
 * The MOSFET bridge is set to float by turning on the override setting for the
 * PWM module associated with the chosen pair of outputs, turning the high
 * side MOSFET off and turning the low side MOSFET off.
 *
 * Note: The high side control is active low and the low side control is active
 * high as set in the Initialize_PWM function.
 */
void Float(int pin){
    if(pin == 1){
        IOCON1bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON1bits.OVRDAT0 = 0; // PWM Low Pin override output is on
        IOCON1bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON1bits.OVRENL = 1;  //Turn overide on for low pin
    } else if(pin == 2){
        IOCON2bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON2bits.OVRDAT0 = 0; // PWM Low Pin override output is on
        IOCON2bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON2bits.OVRENL = 1;  //Turn overide on for low pin
    } else if(pin == 3){
        IOCON3bits.OVRDAT1 = 0; // PWM High Pin override output is off
        IOCON3bits.OVRDAT0 = 0; // PWM Low Pin override output is on
        IOCON3bits.OVRENH = 1;  //Turn overide on for high pin
        IOCON3bits.OVRENL = 1;  //Turn overide on for low pin
    }
}

/* Utilizes the High, Low and Float functions to set to commutate the motor by
 * changing the output levels based on the input state as well as the global
 * variable direction. The commutation pattern is derived from the commutation
 * diagram found on p32 of Maxon's E-Paper Catalog. The commutation pattern is:
 *
 *  Switches | 101 | 100 | 110 | 010 | 011 | 001 |
 *   State   |  5  |  4  |  6  |  2  |  3  |  1  |
 * --------- |-----|-----|-----|-----|-----|-----|
 * 1 -  Red  |  +  |  +  |  0  |  -  |  -  |  0  |
 * 2 - Black |  -  |  0  |  +  |  +  |  0  |  -  |
 * 3 - White |  0  |  -  |  -  |  0  |  +  |  +  |
 *
 * On the current board the wires are arranged incorrectly. For this
 * configuration the pattern is:
 *
 *  Switches | 101 | 100 | 110 | 010 | 011 | 001 |
 *   State   |  5  |  4  |  6  |  2  |  3  |  1  |
 * --------- |-----|-----|-----|-----|-----|-----|
 * 1 - White |  0  |  -  |  -  |  0  |  +  |  +  |
 * 2 - Black |  -  |  0  |  +  |  +  |  0  |  -  |
 * 3 -  Red  |  +  |  +  |  0  |  -  |  -  |  0  |
 *
 * The hall effect sensor inputs are also incorrect. The correct arrangement
 * is:
 * SW1 = D3
 * SW2 = D2
 * SW3 = D1
 * The connections should be reconfigured for the next board iteration.
 *
 */

void commutate(int state){
    switch(state){
        case 0:
            Float(1); Float(2); Float(3);
            break;
        case 1:
            if(direction){
                High(1); Low(2); Float(3);
            } else{
                Low(1); High(2); Float(3);
            }
            break;
        case 2:
            if(direction){
                Float(1); High(2); Low(3);
            } else {
                Float(1); Low(2); High(3);
            }
            break;
        case 3:
            if(direction){
                High(1); Float(2); Low(3);
            } else {
                Low(1); Float(2); High(3);
            }
            break;
        case 4:
            if(direction){
                Low(1); Float(2); High(3);
            } else {
                High(1); Float(2); Low(3);
            }
            break;
        case 5:
            if(direction){
                Float(1); Low(2); High(3);
            } else{
                Float(1); High(2); Low(3);
            }
            break;
        case 6:
            if(direction){
                Low(1); High(2); Float(3);
            } else {
                High(1); Low(2); Float(3);
            }
            break;
        default:
            Float(1); Float(2); Float(3);
            break;
    }
}

/* If the motor is not rotating the change notification interrupt will not
 * trigger and the commutate function will not be called. To get the motor
 * to spin initially the kick function needs to be called to change the
 * motor encoder inputs. 
 */
void kick(void){
    char kick;
    char state;
    state = (!S3 << 2) | (!S2 << 1) | !S1;
    kick = ~state & 0b111;
    commutate(kick);
}