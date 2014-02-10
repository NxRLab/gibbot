#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "library.h"

extern int motoron;
int direction;
//Interrupt vector names are in Table 7-4 p101 of the MPLAB C30 User's Guide
//This interrupt triggers when the motor encoder changes state.
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    int state;
    state = (S3 << 2) | (S2 << 1) | S1; //Read encoders
    if(motoron == 1){//If the motor has been turned on
        commutate(state);//Change outputs based on inputs
        //Change LEDS
        LED1 = 0;
    } else {
        commutate(0);
    }
    LED4 = !LED4;
    // clear mismatch condition
    PORTD;
    IFS1bits.CNIF = 0; //Clear int flag
    return;
}

void Initialize_CN(void) {
    /* The change notification module detects when the state changes on any
     * of the three motor encoder outputs and triggers an interrupt. The
     * interrupt then decides how to commutate the motor by reading the new
     * state value.
     */
    CNENDbits.CNIED1 = 1; //Turn on CN for RD1
    CNENDbits.CNIED2 = 1; //Turn on CN for RD2
    CNENDbits.CNIED3 = 1; //Turn on CN for RD3
    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 0b111;  //Set priority to 7
    IEC1bits.CNIE = 1;      //Enable CN interrupts
}

void Initialize_PWM(void){
    /* The three pulse width modulation modules allows for changing the
     * input voltage to the motor by changing the amount of time that voltage
     * is applied. The PWM module is run at 20kHz in complementary mode to
     * work with the BLDC controller. In complementary mode each of the three
     * PWM modules controls two outputs that are on/off inverse to each other.
     * The module allows for dead time to be inserted between the falling edge
     * of one signal and the rising edge of the next to prevent shoot through.
     */
    PTCON2bits.PCLKDIV = 0b010; //PWM input clock prescaled by 1:4
    //Period = 80 MHz / (PTPER * Prescaler)
    //Period = 80 MHz / (20kHz * 4) = 1000
    PTPER = 1000;

    IOCON1bits.PMOD = 00; //Set PWM1 to Complementary Mode
    IOCON2bits.PMOD = 00; //Set PWM2 to Complementary Mode
    IOCON3bits.PMOD = 00; //Set PWM3 to Complementary Mode

    //Enable deadtime of 0.7us
    DTR1 = DTR2 = DTR3 = 10;
    //DTR = Fosc * Deadtime / Prescaler
    //DTR = 80MHz * 0.7us / 4
    ALTDTR1 = ALTDTR2 = ALTDTR3 = 10;

    //Enable PWM outputs
    IOCON1bits.PENH = 1;
    IOCON1bits.PENL = 1;
    IOCON2bits.PENH = 1;
    IOCON2bits.PENL = 1;
    IOCON3bits.PENH = 1;
    IOCON3bits.PENL = 1;
    //Set polarity of PWM registers
    IOCON1bits.POLH = 1; //PWM1H pin is active-low
    IOCON2bits.POLH = 1; //PWM1H pin is active-low
    IOCON3bits.POLH = 1; //PWM1H pin is active-low
    IOCON1bits.POLL = 0; //PWM1L pin is active-high
    IOCON2bits.POLL = 0; //PWM1L pin is active-high
    IOCON3bits.POLL = 0; //PWM1L pin is active-high

    //Set MDC register to provide duty cycle information
    PWMCON1bits.MDCS = 1;
    PWMCON2bits.MDCS = 1;
    PWMCON3bits.MDCS = 1;


    MDC = 100; // Sets master duty cycle at 10%. 100% is at MDC = 1000

    commutate(0); //Set all motor outputs to float

    PTCONbits.PTEN = 1; //Enable module
}

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

void Lights(void){
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED1 = 0;
    __delay32(8000000);
    LED1 = 1;
    LED2 = 0;
    __delay32(8000000);
    LED2 = 1;
    LED3 = 0;
    __delay32(8000000);
    LED3 = 1;
    LED4 = 0;
    __delay32(8000000);
    LED4 = 1;
    __delay32(2500000);
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    __delay32(10000000);
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
}
