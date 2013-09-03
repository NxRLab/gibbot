/* 
 * File:   main.c
 * Author: James
 *
 * Created on June 1, 2013, 11:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>

#define S1 PORTBbits.RB5
#define S2 PORTBbits.RB6
#define S3 PORTBbits.RB7

#define AIN PDC1
#define BIN PDC2
#define CIN PDC3

#define PCHANEN 1
#define NCHANEN 0


/*
 * 
 */


/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(FWDTEN_OFF)
_FPOR(FPWRT_PWR128)
_FICD(ICS_PGD2 & JTAGEN_OFF)


void High(int pin){
    if(pin == 1){
        LATAbits.LATA0 = 1;
        IOCON1bits.OVRENH = 0;  //Turns overide off for high pins
        IOCON1bits.OVRENL = 0;  //Same for low
        IOCON1bits.PENH = 1; //PWM controls PWM1H
        IOCON1bits.PENL = 1; //PWM controls PWM1L
    } else if(pin == 2){
        LATAbits.LATA1 = 1;
        IOCON2bits.OVRENH = 0;  //Turns overide off for high pins
        IOCON2bits.OVRENL = 0;  //Same for low
        IOCON2bits.PENH = 1; //PWM controls PWM1H
        IOCON2bits.PENL = 1; //PWM controls PWM1L
    } else if(pin == 3){
        LATAbits.LATA2 = 1;
        IOCON3bits.OVRENH = 0;  //Turns overide off for high pins
        IOCON3bits.OVRENL = 0;  //Same for low
        IOCON3bits.PENH = 1; //PWM controls PWM1H
        IOCON3bits.PENL = 1; //PWM controls PWM1L
    }
}

void Low(int pin){
    if(pin == 1){
        LATAbits.LATA0 = 0;
        IOCON1bits.OVRDAT0 = NCHANEN;   //Overide for L
        IOCON1bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON1bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON1bits.OVRENL = 1;          //Same for low
    } else if(pin == 2){
        LATAbits.LATA1 = 0;
        IOCON2bits.OVRDAT0 = NCHANEN;   //Overide for L
        IOCON2bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON2bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON2bits.OVRENL = 1;          //Same for low
    } else if(pin == 3){
        LATAbits.LATA2 = 0;
        IOCON3bits.OVRDAT0 = NCHANEN;   //Overide for L
        IOCON3bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON3bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON3bits.OVRENL = 1;          //Same for low
    }
}

void Float(int pin){
    if(pin == 1){
        LATAbits.LATA0 = 0;
        IOCON1bits.OVRDAT0 = !NCHANEN;   //Overide for L
        IOCON1bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON1bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON1bits.OVRENL = 1;          //Same for low
    } else if(pin == 2){
        LATAbits.LATA1 = 0;
        IOCON2bits.OVRDAT0 = !NCHANEN;   //Overide for L
        IOCON2bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON2bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON2bits.OVRENL = 1;          //Same for low
    } else if(pin == 3){
        LATAbits.LATA2 = 0;
        IOCON3bits.OVRDAT0 = !NCHANEN;   //Overide for L
        IOCON3bits.OVRDAT1 = !PCHANEN;  //Overide for H
        IOCON3bits.OVRENH = 1;          //Turns overide on for high pins
        IOCON3bits.OVRENL = 1;          //Same for low
    }
}

// looking into longer shaft, CCW rotation
void state1() {High(1); Float(2); Low(3);}
void state2() {Float(1); Low(2); High(3);}
void state3() {High(1); Low(2); Float(3);}
void state4() {Low(1); High(2); Float(3);}
void state5() {Float(1); High(2); Low(3);}
void state6() {Low(1); Float(2); High(3);}

void __attribute__((interrupt)) _CNInterrupt(void) {
    
   char state = 0;
    // Is this an CN interrupt?
    if (IFS1bits.CNIF) {
        state = (S1 << 2) | (S2 << 1) | S3;
        //LATAbits.LATA0 = !S1;
        //LATAbits.LATA1 = !S2;
        //LATAbits.LATA2 = !S3;
        switch(state) {
            case 1:
                //LATA = 1;
                state1();
                break;
            case 2:
                //LATA = 2;
                state2();
                break;
            case 3:
                //LATA = 3;
                state3();
                break;
            case 4:
                //LATA = 4;
                state4();
                break;
            case 5:
                //LATA = 5;
                state5();
                break;
            case 6:
                //LATA = 6;
                state6();
                break;
        }

        // clear mismatch condition
        PORTB;
        IFS1bits.CNIF = 0;      //Clear int flag
    }
    return;
}

int main() {
    int state;
    ADPCFG = 0xFFFF; //Set all pins as digital
    TRISA = 0xFFFF;  //Set all pins as inputs
    TRISB = 0xFFFF;

    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 0;
    LATAbits.LATA2 = 0;
    
    //Configure oscillator freq Fosc through external crystal
    // Fin = External oscillater clock = 8 MHz
    // Fosc = Fin*M/(N1*N2)
    // 8MHz*40/(2*2) = 80 MHz
    // Fcy = Fosc/2 = 40 MIPS

    //TRISBbits.TRISB15 = 0;
    //LATBbits.LATB15 = 1;
    CLKDIVbits.PLLPRE=2;        
    CLKDIVbits.PLLPRE -= 2;     // N1 = PLLPRE+2 = 2
    PLLFBD = 40;
    PLLFBD -= 2;                // M = PLLFBD+2 = 40
    CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0= DIV_2


    __builtin_write_OSCCONH(0x01);	/* New Oscillator FRC w/ PLL */
    __builtin_write_OSCCONL(0x01);  	/* Enable clock switch Switch */
    
    RCONbits.SWDTEN = 0; // Disable Watch Dog Timer
    
    while(OSCCONbits.COSC != 0b001); //Wait for new Oscillator to become FRC w/ PLL */
    while(!OSCCONbits.LOCK);    // wait for PLL ready

    ACLKCONbits.FRCSEL = 1;	/* FRC provides input for Auxiliary PLL (x16) */
    ACLKCONbits.SELACLK = 1;	/* Auxiliary Oscillator provides clock source for PWM & ADC */
    ACLKCONbits.APSTSCLR = 7;	/* Divide Auxiliary clock by 1 */
    ACLKCONbits.ENAPLL = 1;	/* Enable Auxiliary PLL */

    while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */



    //init PWMs

    //PWM period  = PTPER*1.04ns*PCLKDIV
    PTCON2bits.PCLKDIV = 0b101; //PCLKDIV = 32
    PTPER = 3004; // PWM period = 100 us => freq = 10kHz

    //PWM1
    PWMCON1bits.FLTIEN = 0; // disable fault int
    PWMCON1bits.CLIEN = 0; //Current limit int disabled
    PWMCON1bits.TRGIEN = 0; //trigger in disabled
    PWMCON1bits.ITB = 0; //use PTPER for period;
    PWMCON1bits.MDCS = 0; //use PDC1 for duty cycle
    PWMCON1bits.DTC = 0b00;// enable dead time
    IOCON1bits.PENH = 1; //PWM controls PWM1H
    IOCON1bits.PENL = 1; //PWM controls PWM1L
    IOCON1bits.POLH = 1; //PWMxH active high
    IOCON1bits.POLL = 1; //PWMxL active high
    IOCON1bits.PMOD = 0; //Complementary output mode
    PDC1 = 1502; //50% duty cycle

    //Dead time for actual DsPIC we will use
    //DTA = dead time/(PS*Tcy)
    //DTCON1bits.DTAPS = 0b11; //Prescaler = 8
    //DTA = 0b111111; //Dead time = 12 us (max for 6 bit register)

    DTR1 = 450; //15us dead time
    ALTDTR1 = 450;
    PHASE1 = 0; //No phase shift

    
    //PWM2
    PWMCON2bits.FLTIEN = 0; // disable fault int
    PWMCON2bits.CLIEN = 0; //Current limit int disabled
    PWMCON2bits.TRGIEN = 0; //trigger in disabled
    PWMCON2bits.ITB = 0; //use PTPER for period;
    PWMCON2bits.MDCS = 0; //use PDC1 for duty cycle
    PWMCON2bits.DTC = 0b00;// enable dead time
    IOCON2bits.PENH = 1; //PWM controls PWM1H
    IOCON2bits.PENL = 1; //PWM controls PWM1L
    IOCON2bits.POLH = 1; //PWMxH active high
    IOCON2bits.POLL = 1; //PWMxL active high
    IOCON2bits.PMOD = 0; //Complementary output mode
    PDC2 = 1502; //50% duty cycle
    DTR2 = 30; //1% dead time
    ALTDTR2 = 30;
    PHASE2 = 0; //No phase shift
    
    /*
    //PWM2 in Independent mode
    IOCON2bits.PENH = 1; //PWM controls PWM1H
    IOCON2bits.PENL = 1; //PWM controls PWM1L
    IOCON2bits.POLH = 1; //PWMxH active high
    IOCON2bits.POLL = 1; //PWMxL active high
    IOCON2bits.PMOD = 0b11; //Independent output mode
    PDC2 = 1502; //50% PWM2H duty cycle
    SDC2 = 751; //25% PWM2L duty cycle
    DTR2 = 30; //1% dead time
    ALTDTR2 = 30;
    PHASE2 = 0; //No phase shift
    SPHASE2 = 376; //12.5 us phase shift
    */
    
    //PWM3
    PWMCON3bits.FLTIEN = 0; // disable fault int
    PWMCON3bits.CLIEN = 0; //Current limit int disabled
    PWMCON3bits.TRGIEN = 0; //trigger in disabled
    PWMCON3bits.ITB = 0; //use PTPER for period;
    PWMCON3bits.MDCS = 0; //use PDC1 for duty cycle
    PWMCON3bits.DTC = 0b00;// enable dead time
    IOCON3bits.PENH = 1; //PWM controls PWM1H
    IOCON3bits.PENL = 1; //PWM controls PWM1L
    IOCON3bits.POLH = 1; //PWMxH active high
    IOCON3bits.POLL = 1; //PWMxL active high
    IOCON3bits.PMOD = 0; //Complementary output mode
    PDC3 = 1502; //50% duty cycle
    DTR3 = 30; //1% dead time
    ALTDTR3 = 30;
    PHASE3 = 0; //No phase shift

    PTCONbits.PTEN = 1; //enable pwm

    //Change Notification
    // Turn change notification on for CN5, CN6, and CN7
    CNEN1bits.CN5IE = 1;
    CNEN1bits.CN6IE = 1;
    CNEN1bits.CN7IE = 1;

    IFS1bits.CNIF = 0;      //Clear interrupt flag
    IPC4bits.CNIP = 0b111;  //Set priority to 7
    IEC1bits.CNIE = 1;      //Enable interrupts


    while(1){
    };
}

