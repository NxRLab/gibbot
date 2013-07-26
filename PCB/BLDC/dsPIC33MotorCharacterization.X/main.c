/* 
 * File:   main.c
 * Author: ajgriesemer
 *
 * Created on July 26, 2013, 3:30 PM
 */

#include <stdio.h>/*
 * File:   main.c
 * Author: ajgriesemer
 *
 * Created on June 18, 2013, 2:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>

#define S3 PORTBbits.RB7
#define S2 PORTBbits.RB8
#define S1 PORTBbits.RB9

/* Configuration Bit Settings */
_FBS(BWRP_WRPROTECT_OFF) //Boot segment is not write protected (for debugging)
_FOSCSEL(FNOSC_FRC) //Use internal FRC Oscillator at 7.37 MHz no PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
//Clock switching is enabled, Fail-Safe Clock Monitor is disabled
//OSC2 pin does not output the clock, it has digital I/O function
_FWDT(FWDTEN_OFF)
//Watchdog timer not enabled automaticatally, enabled/disabled by user software
_FPOR(FPWRT_PWR128 & LPOL_ON & HPOL_OFF)
//Power on Reset Timer is enabled for 128ms to allow system power to stablize
//PWM module low side output pins have active-high output polarity
//PWM module high side output pins have active-low output polarity
_FICD(ICS_PGD3 & JTAGEN_OFF)
//Communicate on PGC1/EMUC3 and PGD1/EMUD3
//JTAG is Disabled

/* Function Declarations */
void init_pwm(void);
void init_cn(void);
void High(int pin);
void Float(int pin);
void Low(int pin);
void init_uart (void);

/*Commutation pattern for the Maxon Motor*/
void state5() {High(1);  Low(2);   Float(3); }
void state1() {High(1);  Float(2); Low(3);   }
void state3() {Float(1); High(2);  Low(3);   }
void state2() {Low(1);   High(2);  Float(3); }
void state6() {Low(1);   Float(2); High(3);  }
void state4() {Float(1); Low(2);   High(3);  }


/*Commutation pattern for the Pittman Motor*/
//void state1() {High(1); Float(2); Low(3);}
//void state2() {Float(1); Low(2); High(3);}
//void state3() {High(1); Low(2); Float(3);}
//void state4() {Low(1); High(2); Float(3);}
//void state5() {Float(1); High(2); Low(3);}
//void state6() {Low(1); Float(2); High(3);}

//This interrupt is triggered every time the dsPIC recieves data
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) {

        char echo = U1RXREG;
        if (echo=='a'){
            LATAbits.LATA2 = !LATAbits.LATA2;
        }

        while(U1STAbits.UTXBF){//wait for buffer to not be full
        }
        U1TXREG = 0x61;

        LATAbits.LATA3 = !LATAbits.LATA3;
	IFS0bits.U1RXIF = 0;
}

//We don't care about a transmit interrupt
void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
	IFS0bits.U1TXIF = 0; 
}

// This interrupt reads the Change Notification pins that are connected to
// the hall effect sensors of the Maxon Motor. This function is responsible
// for commutating the motor.
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {

    char state = 0;
    // Is this a CN interrupt?
    if (IFS1bits.CNIF) {
        //Read the state of the hall effect sensors
        state = (!S3 << 2) | (!S2 << 1) | !S1;
        switch(state) {
            case 1:
                state1();
                break;
            case 2:
                state2();
                break;
            case 3:
                state3();
                break;
            case 4:
                state4();
                break;
            case 5:
                state5();
                break;
            case 6:
                state6();
                break;
        }

        // clear mismatch condition
        PORTA;
        PORTB;
        IFS1bits.CNIF = 0;      //Clear int flag
    }
    return;
}


int main(void){
    init_pwm();
    init_cn();
    init_uart();
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    Float(1);
    Float(2);
    Float(3);
    while(1){
    }
    return 0;
}

void init_pwm(void){
    P1DC1 = 371; //Set initial duty cycle as 50% on pin 1
    P1DC2 = 371; //Set initial duty cycle as 50% on pin 2
    P1DC3 = 371; //Set initial duty cycle as 50% on pin 2
    //PxTPER = (Fcy / (Fpwm * PxTMR Prescaler)) - 1
    //PxTPER = (3.685 MHz / (20kHz * 1)) - 1
    P1TPER = 184;//Set PWM freq as 20kHz

    P1DTCON1bits.DTAPS = 0b00; //Set deadtime prescaler as 1:1
    // DT = Dead Time / (Prescaler * Tcy)
    // DT = 1 us / (1 *
    // DT = 2
    P1DTCON1bits.DTA = 2;

    P1DTCON2bits.DTS1A = 0; //Deadtime before PWM1H1 is from unit A
    P1DTCON2bits.DTS1I = 0; //Deadtime before PWM1L1 is from unit A
    P1DTCON2bits.DTS2A = 0; //Deadtime before PWM1H2 is from unit A
    P1DTCON2bits.DTS2I = 0; //Deadtime before PWM1L2 is from unit A
    P1DTCON2bits.DTS3A = 0; //Deadtime before PWM1H2 is from unit A
    P1DTCON2bits.DTS3I = 0; //Deadtime before PWM1L2 is from unit A

    // Enable all PWM pins
    PWM1CON1bits.PEN1H = 1;
    PWM1CON1bits.PEN1L = 1;
    PWM1CON1bits.PEN2H = 1;
    PWM1CON1bits.PEN2L = 1;
    PWM1CON1bits.PEN3H = 1;
    PWM1CON1bits.PEN3L = 1;
    //Enable PWM timer
    P1TCONbits.PTEN = 1;
}

void init_uart (void){
    /* Setup Peripheral Pin Select */
    /* RP5->RX  RP6->TX            */
    RPINR18bits.U1RXR = 5; // UART1 RX Tied to RP5  datasheet p122
    RPOR3bits.RP6R = 3;    // RP6 tied to UART1 TX datasheet p123

    /* Setup UART             */
    /* For Baud Rate of 38400 */
    // U1MODEbits.BRGH = 1; // Turn on High Baud Rate Mode
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (3.685MHz/(4*38400)) - 1
    // U1BRG = 23

    /* For Baud Rate of 9600 */
    U1MODEbits.BRGH = 0; // Turn off High Baud Rate Mode
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (3.685MHz/(16*9600)) - 1
    U1BRG = 23; //Baud rate ~9600

    IPC3bits.U1TXIP = 5; //Set interrupt priority of 5
    IPC2bits.U1RXIP = 5; //Set interrupt priority of 5

    IFS0bits.U1TXIF = 0; // Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 1; // Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1; // Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1; //enable the UART
    U1STAbits.UTXEN = 1;   //enable UART transmit
}

void init_cn(void){
    // Turn change notification on
    CNEN2bits.CN21IE = 1;
    CNEN2bits.CN22IE = 1;
    CNEN2bits.CN23IE = 1;
    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 0b111;  //Set priority to 7
    IEC1bits.CNIE = 1;      //Enable interrupts
}


void High(int pin){
    if(pin == 1){
        P1OVDCONbits.POVD1H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD1L = 1;  //Turn overide off for low pin
    } else if(pin == 2){
        P1OVDCONbits.POVD2H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD2L = 1;  //Turn overide off for low pin
    } else if(pin == 3){
        P1OVDCONbits.POVD3H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD3L = 1;  //Turn overide off for low pin
    }
}

void Low(int pin){
    if(pin == 1){
        P1OVDCONbits.POUT1H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT1L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD1H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD1L = 0; // Turn overide on for low pin
    } else if(pin == 2){
        P1OVDCONbits.POUT2H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT2L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD2H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD2L = 0; // Turn overide on for low pin
    } else if(pin == 3){
        P1OVDCONbits.POUT3H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT3L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD3H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD3L = 0; // Turn overide on for low pin
    }
}

void Float(int pin){
    if(pin == 1){
        P1OVDCONbits.POUT1H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT1L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD1H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD1L = 0; // Turn overide on for low pin
    } else if(pin == 2){
        P1OVDCONbits.POUT2H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT2L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD2H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD2L = 0; // Turn overide on for low pin
    } else if(pin == 3){
        P1OVDCONbits.POUT3H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT3L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD3H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD3L = 0; // Turn overide on for low pin
    }
}

void Duty(int pin, int duty){
    int assign;
    assign = 744*duty/1000;
    if (pin == 1){
        P1DC1 = assign;
    } else if (pin == 2){
        P1DC2 = assign;
    } else if (pin == 3){
        P2DC1 = assign;
    }
}
