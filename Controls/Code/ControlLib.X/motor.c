/* Configure modules to control the BLDC motor. Motor control utilizes the
 * change notification module to initiate commutation based on changes in
 * the state of the hall effect sensors. Pulse width modulation is used to
 * control the motor speed/torque.
 *
 * To change the motor direction write to the global variable "direction" with CW
 * or CCW. CW will cause the motor to spin Clock-wise when viewed from
 * the spinning back cover. Example:
 *     direction = CCW; //motor will spin counter-clockwise
 *
 * To change the motor speed/torque use the write_duty() function. A value of
 * 1000 corresponds to 100% duty cycle. A value of 0 corresponds to 0%.
 * Example:
 *     write_duty(200); //Motor runs at 20% duty cycle
 *
 * To read the duty cycle use the read_duty() function.
 * Example:
 *     duty = read_duty(); //returns an int duty cycle * 10
 *
 * To turn the motor on set the global variable "motoron". To turn the motor off
 * clear "motoron". Example:
 *     motoron = 1; //turns the motor on at the duty cycle set in MDC
 *
 */
#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "stdio.h"
volatile char motoron = 0;
char state = 0;
int direction = CW;

/* _CNInterrupt is the change notification interrupt trigger by a change in
 * state of the hall effect sensor inputs. The interrupt service routine reads
 * the hall effect sensor state and calls the commutate function to change the
 * motor lead outputs.
 *
 * Interrupt vector names are in Table 7-4 p101 of the MPLAB C30 User's Guide
 */
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    state = (S3 << 2) | (S2 << 1) | S1; //Read hall effect sensors
    if(motoron == 1){     //If the motor has been turned on
        commutate(state); //Change outputs based on hall effect sensor state
    } else {              //If the motor is off
        commutate(0);     //Set all motor outputs to float
    }
    LED1 = !LED1;
    //printf("%d",state);
    PORTD;                //Clear mismatch condition
    IFS1bits.CNIF = 0;    //Clear interrupt flag
}

/* read_duty() returns the current duty cycle value in MDC */
int read_duty(void){
    return MDC;
}

/* write_duty() assigns a proper input value into MDC */
void write_duty(int value){
    if(value>1000){
        MDC=1000;
    } else if (value<0){
        MDC=0;
    } else{
        MDC=value;
    }
}

/* The pulse width modulation module controls the motor torque by changing the
 * amount of time the on voltage is applied. The PWM module runs at 20kHz in
 * complementary mode to work with the HIP4086 BLDC driver.
 * In complementary mode each of the three PWM modules controls two outputs
 * whose states are the inverse of each other.
 * The module incorporates a dead time delay between the falling edge of one
 * signal and the rising edge of the next to prevent shoot through.
 */
void initialize_PWM(void){
    
    PTCON2bits.PCLKDIV = 0b010; //PWM input clock prescaled by 1:4
    //Period = 80 MHz / (PTPER * Prescaler)
    //PTPER = 80 MHz / (20kHz * 4) = 1000
    PTPER = 1000;
    //PTPER = 80 MHz / (50kHz * 4) = 400
    //PTPER = 400;

    IOCON1bits.PMOD = 0; //Set PWM1 to Complementary Mode
    IOCON2bits.PMOD = 0; //Set PWM2 to Complementary Mode
    IOCON3bits.PMOD = 0; //Set PWM3 to Complementary Mode

    //DTR = Fosc * Deadtime / Prescaler
    //DTR = 80MHz * 0.5us / 4
    DTR1 = DTR2 = DTR3 = 10; //Set deadtime of 0.5us
    ALTDTR1 = ALTDTR2 = ALTDTR3 = 10; //Set alternate deadtime of 0.5us

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

    //Use MDC register to provide duty cycle information for all PWM modules
    PWMCON1bits.MDCS = 1;
    PWMCON2bits.MDCS = 1;
    PWMCON3bits.MDCS = 1;

    MDC = 100; // Sets master duty cycle at 10%. 100% is at MDC = 1000

    commutate(0); //Set all motor outputs to float

    PTCONbits.PTEN = 1; //Enable PWM
}

/* The change notification module detects when the state changes on any
 * of the three motor encoder outputs and triggers _CNInterrupt. The
 * interrupt then decides how to commutate the motor by reading the hall
 * effect sensor inputs.
 */
void initialize_CN(void) {
    CNENDbits.CNIED3 = 1; //Turn on CN for RD3
    CNENDbits.CNIED4 = 1; //Turn on CN for RD4
    CNENDbits.CNIED5 = 1; //Turn on CN for RD5
    IFS1bits.CNIF = 0;     //Clear interrupt flag
    IPC4bits.CNIP = 0b100; //Set priority to 4
    IEC1bits.CNIE = 1;     //Enable CN interrupt
}


/* Turns on High state PWM on one the three MOSFETs bridges controlling the BLDC
 * motor leads. The motor lead that is set high is determined by the
 * input variable "pin". The MOSFETs are set high by turning off the override
 * setting for the PWM module associated with the chosen pair of outputs.
 */
void High(int pin){
    if(pin == 1){
        IOCON1bits.OVRENH = 0;  //Turn overide off for PWM1 high pin
        IOCON1bits.OVRENL = 0;  //Turn overide off for PWM1 low pin
    } else if(pin == 2){
        IOCON2bits.OVRENH = 0;  //Turn overide off for PWM2 high pin
        IOCON2bits.OVRENL = 0;  //Turn overide off for PWM2 low pin
    } else if(pin == 3){
        IOCON3bits.OVRENH = 0;  //Turn overide off for PWM3 high pin
        IOCON3bits.OVRENL = 0;  //Turn overide off for PWM3 low pin
    }
}

/* Turns on the low side MOSFET driving one of the three BLDC motor leads low.
 * The motor lead that is set low is determined by the input variable "pin".
 * The MOSFET bridge is pulled low by turning on the override setting for the
 * PWM module associated with the chosen pair of outputs, turning the high
 * side MOSFET off and turning the low side MOSFET on.
 *
 * Note: The high side control is active low and the low side control is active
 * high as specified in the HIP4086 datasheet and set in the Initialize_PWM
 * function.
 */
void Low(int pin){
    if(pin == 1){
        IOCON1bits.OVRDAT1 = 0; //Change PWM1 high pin override state to off
        IOCON1bits.OVRDAT0 = 1; //Change PWM1 low pin override state to on
        IOCON1bits.OVRENH = 1;  //Turn overide on for PWM1 high pin
        IOCON1bits.OVRENL = 1;  //Turn overide on for PWM1 low pin
    } else if(pin == 2){
        IOCON2bits.OVRDAT1 = 0; //Change PWM2 high pin override state to off
        IOCON2bits.OVRDAT0 = 1; //Change PWM2 low pin override state to on
        IOCON2bits.OVRENH = 1;  //Turn overide on for PWM2 high pin
        IOCON2bits.OVRENL = 1;  //Turn overide on for PWM2 low pin
    } else if(pin == 3){
        IOCON3bits.OVRDAT1 = 0; //Change PWM3 high pin override state to off
        IOCON3bits.OVRDAT0 = 1; //Change PWM3 low pin override state to on
        IOCON3bits.OVRENH = 1;  //Turn overide on for PWM3 high pin
        IOCON3bits.OVRENL = 1;  //Turn overide on for PWM3 low pin
    }
}

/* Turns off both MOSFETs leaving one of the three BLDC motor leads floating.
 * The motor lead that is floating is determined by the input variable "pin".
 * The MOSFET bridge is set to float by turning on the override setting for the
 * PWM module associated with the chosen pair of outputs and turning both
 * MOSFETs off.
 *
 * Note: The high side control is active low and the low side control is active
 * high as specified in the HIP4086 datasheet and set in the Initialize_PWM
 * function.
 */
void Float(int pin){
    if(pin == 1){
        IOCON1bits.OVRDAT1 = 0; //Change PWM1 high pin override state to off
        IOCON1bits.OVRDAT0 = 0; //Change PWM1 low pin override state to off
        IOCON1bits.OVRENH = 1;  //Turn overide on for PWM1 high pin
        IOCON1bits.OVRENL = 1;  //Turn overide on for PWM1 low pin
    } else if(pin == 2){
        IOCON2bits.OVRDAT1 = 0; //Change PWM2 high pin override state to off
        IOCON2bits.OVRDAT0 = 0; //Change PWM2 low pin override state to off
        IOCON2bits.OVRENH = 1;  //Turn overide on for PWM2 high pin
        IOCON2bits.OVRENL = 1;  //Turn overide on for PWM2 low pin
    } else if(pin == 3){
        IOCON3bits.OVRDAT1 = 0; //Change PWM3 high pin override state to off
        IOCON3bits.OVRDAT0 = 0; //Change PWM3 low pin override state to off
        IOCON3bits.OVRENH = 1;  //Turn overide on for PWM3 high pin
        IOCON3bits.OVRENL = 1;  //Turn overide on for PWM3 low pin
    }
}

/* The commutate function uses the High, Low and Float functions to commutate
 * the motor. The input to the function is the motor state from the hall effect 
 * sensors. Depending on the value of the global variable "direction" the
 * function sets the motor outputs according to the motor's commutation pattern.
 * The commutation pattern is derived from the commutation diagram found on p32
 * of Maxon's E-Paper Catalog and is shown below.
 *
 * Hall Sen 321 | 101 | 001 | 011 | 010 | 110 | 100 |
 *     State    |  5  |  1  |  3  |  2  |  6  |  4  |
 * -------------|-----|-----|-----|-----|-----|-----|
 * 1 -   Red    |  +  |  +  |  0  |  -  |  -  |  0  |
 * 2 -  Black   |  -  |  0  |  +  |  +  |  0  |  -  |
 * 3 -  White   |  0  |  -  |  -  |  0  |  +  |  +  |
 *
 * An input of 0 to the commutate function will turn off the motor.
 */
void commutate(int state){
    switch(state){
        case 0:
            Float(1); Float(2); Float(3);
            break;
        case 1:
            if(direction){
                High(1); Float(2); Low(3);
            } else{
                Low(1); Float(2); High(3);
            }
            break;
        case 2:
            if(direction){
                Low(1); High(2); Float(3);
            } else{
                High(1); Low(2); Float(3);
            }
            break;
        case 3:
            if(direction){
                Float(1); High(2); Low(3);
            } else{
                Float(1); Low(2); High(3);
            }
            break;
        case 4:
            if(direction){
                Float(1); Low(2); High(3);
            } else{
                Float(1); High(2); Low(3);
            }
            break;
        case 5:
            if(direction){
                High(1); Low(2); Float(3);
            } else{
                Low(1); High(2); Float(3);
            }
            break;
        case 6:
            if(direction){
                Low(1); Float(2); High(3);
            } else{
                High(1); Float(2); Low(3);
            }
            break;
        //case 7:
          //  Low(1); High(2);
            //break;
        default:
            Float(1); Float(2); Float(3);
            break;
    }
}

/* The kick function needs to be called when the motor is starting from rest.
 * If the motor is not rotating the change notification interrupt will not
 * trigger and the commutate function will not be called. The kick function
 * drives the motor to change the hall effect sensor inputs.
 */
void kick(void){
    int kick;
    int state;
    int CWtable[6] = {5,3,1,6,4,2};
    int CCWtable[6] = {3,6,2,5,1,4};
    state = (S3 << 2) | (S2 << 1) | S1;
    if(direction==CW){
        kick = CWtable[state-1];
    } else{ //direction == CCW
        kick = CCWtable[state-1];
    }
    printf("%d",kick);
    commutate(kick);
}