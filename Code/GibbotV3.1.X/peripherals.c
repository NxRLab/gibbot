#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "peripherals.h"

int error = 0;
int MOTCNT;
long LOWMAGCNT;
struct I2C_CONTROL_t I2C_CONTROL;

void Startup(void){
    //Set the calibration bits for phase lock loop
    //Clock frequency is set at 80MHz
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    PLLFBDbits.PLLDIV = 42;  // M = 44
    CLKDIVbits.PLLPOST = 0;  // N2 = 2

    TRISBbits.TRISB2 = 1;    //USER input
    //LED outputs
    TRISDbits.TRISD11 = 0;   //LED1
    TRISDbits.TRISD0 = 0;    //LED2
    TRISCbits.TRISC13 = 0;   //LED3
    TRISCbits.TRISC14 = 0;   //LED4
    //Magnet Control
    TRISDbits.TRISD10 = 0;   //Top Magnet

    TOPMAG = 0;

    Initialize_CN();
    Initialize_PWM();
    Initialize_UART();
    Initialize_QEI();
    Initialize_Timer1();
    Initialize_I2C_Master();
    Initialize_ADC();
    Lights();
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
    IOCON1bits.POLH = 1;
    IOCON2bits.POLH = 1;
    IOCON3bits.POLH = 1;
    IOCON1bits.POLL = 0;
    IOCON2bits.POLL = 0;
    IOCON3bits.POLL = 0;

    //Set MDC register to provide duty cycle information
    PWMCON1bits.MDCS = 1;
    PWMCON2bits.MDCS = 1;
    PWMCON3bits.MDCS = 1;


    MDC = 100; // Sets master duty cycle at 10%. 100% is at MDC = 1000

    commutate(0); //Set all motor outputs to float

    PTCONbits.PTEN = 1; //Enable module
}

void Initialize_ADC(void) {
    /* The analog-digital voltage converter reads the voltage output
     * from the current sensor which is proportional to the motor drive current.
     */
    AD1CON1bits.FORM    = 0;  // Unsigned integer output
    AD1CON1bits.AD12B   = 1;  // 12-bit data ouytput
    AD1CON2bits.ALTS    = 0;  // Disable alternate input selection
    AD1CON1bits.ASAM    = 0;  // Use manual sampling
    AD1CON1bits.SSRC    = 0b111; // Use an automatic trigger
    AD1CON1bits.SSRCG    = 0; // Use an automatic trigger
    AD1CON2bits.VCFG    = 0;  // Ensure AVDD and AVSS are used as Vref+ and Vref-
    AD1CON3bits.SAMC    = 15; //
    AD1CON3bits.ADCS = 9;     // Tad = 117.6ns = 10*Tcy,  Tcy = 12.5ns
    ANSELEbits.ANSE6 = 1;

    // Initialize MUXA Input Selection
    AD1CHS0bits.CH0SA = 30;
    AD1CON1bits.SAMP        = 0; // Ensure sampling is turned off
    AD1CON1bits.ADON        = 1; //Turn on the ADC converter
}

short ADC_Read(void) { //manual sampling and conversion function
    AD1CON1bits.SAMP = 1; //Start sampling, sampling is stopped after 1us
    while (!AD1CON1bits.DONE); //wait for sampling and conversion to finish
    return ADC1BUF0; //Return AN3
}

void Initialize_UART(void){
    // The UART module allows wireless communication with the computer via XBee

    TRISEbits.TRISE7 = 0;
    ANSELEbits.ANSE7 = 0;
    //RP5->RX  RP6->TX
    RPINR18bits.U1RXR = 118; //UART1 RX1 Tied to RP118 (RG6)
    RPOR6bits.RP87R = 1;     //RP87 tied to UART1 TX1 (RE7)
    //RP91->CTS RP96->RTS
    RPINR18bits.U1CTSR = 96; //UART1 CTS tied to R96 (RF0)
    RPOR7bits.RP97R = 2;     //RP97 tied to UART1 RTS (RF1)

    /* For Baud Rate of 115200 */
    U1MODEbits.BRGH = 0; //Turn High Baud Rate Mode off
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (40MHz/(16*115200)) - 1
    U1BRG = 21; //Baud rate 118694

    //UxTX and UxRX pins are enabled and used
    //UxCTS and UxRTS pins are controlled by port latches
    //To use U1CTS and U1RTS pins with module: U1MODEbits.UEN = 0b10;
    U1MODEbits.UEN = 0b00;
    IPC2bits.U1RXIP = 5;     // Set RX interrupt priority to 5
    IFS0bits.U1RXIF = 0;     // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;     // Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1;   //enable the UART
    U1STAbits.UTXEN = 1;     //Enable transmitting
}

void Initialize_QEI(void){
    /* The QEI module reads the two outputs from the quadrate encoder and
     * converts it into a count that represents the rotational position
     * of the magnet. */
    RPINR14bits.QEA1R = 32; //Set RP32 (B0) as QEI1 A
    RPINR14bits.QEB1R = 33; //Set RP33 (B1) as QEI1 B
    POS1CNTL = 0;           //Set initial position of magnet
    QEI1CONbits.QEIEN = 1; //Turn on QEI1
}

void Initialize_Timer1(void){
    //The timer 1 interrupt triggers at 1kHz
    T1CONbits.TON = 0; //Turn off Timer1
    //Freq = 40MHz / Prescaler / PR1
    T1CONbits.TCKPS = 0b11; //Set prescaler as 256:1
    TMR1 = 0;  //Clear Timer1
    PR1 = 157; //Load Timer1 period value 1439

    IPC0bits.T1IP = 7; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt

    T1CONbits.TON = 1; //Turn on Timer1
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


void Initialize_I2C_Master(void){
    //Fcy = 40 MHz
    //F SCL = 400kHz
    I2C2BRG = 95;
    IFS3bits.MI2C2IF = 0;      //Clear interrupt flag
    IPC12bits.MI2C2IP = 0b110;  //Set priority to 6
    IEC3bits.MI2C2IE = 1;      //Enable I2C 2 Master interrupts

    I2C_CONTROL.state = 0;
    I2C2CONbits.I2CEN = 1;

}

void I2C_Write(char command){
    /* I2C module will read to detect the address 1101XXXX being sent by the
     * master. The first four bits are a header that must be recognized. The
     * next three bits are masked and so are ignored by the module. They are
     * used as command bits. The final bit is the Read/Write bit which is
     * interpreted by the module.
     *   1101ABCR
     * A: 1 turns the magnet on, 0 turns the magnet off
     * B: If 1 the slave will send two bytes with the motor encoder position
     * C: If 1 the slave will send two bytes with the magnet encoder position
     * R: Indicates a read or a write
     * The R/W bit is appended to the address by the interrupt transmit function
     */
    I2C_CONTROL.cmd = I2C_WRITE;
    I2C_CONTROL.numbytes = 0;
    I2C_CONTROL.slaveaddr = 0b1101000 | command;
    //Trigger interupt
    IFS3bits.MI2C2IF = 1;
}

void I2C_Read(char command){
    /* I2C module will read to detect the address 1101XXXX being sent by the
     * master. The first four bits are a header that must be recognized. The
     * next three bits are masked and so are ignored by the module. They are
     * used as command bits. The final bit is the Read/Write bit which is
     * interpreted by the module.
     *   1101ABCR
     * A: 1 turns the magnet on, 0 turns the magnet off
     * B: If 1 the slave will send two bytes with the motor encoder position
     * C: If 1 the slave will send four bytes with the magnet encoder position
     * R: Indicates a read or a write
     * The R/W bit is appended to the address by the interrupt transmit function
     */
    I2C_CONTROL.cmd = I2C_READ;
    if((command & 0b0000011) == 3){
        I2C_CONTROL.numbytes = 6;
    } else if(command & 0b0000010){
        I2C_CONTROL.numbytes = 2;
    } else if(command & 0b0000001){
        I2C_CONTROL.numbytes = 4;
    } else {
        I2C_CONTROL.numbytes = 0;
    }

    I2C_CONTROL.slaveaddr = 0b1101000 | command;
    //Trigger interupt
    IFS3bits.MI2C2IF = 1;
}