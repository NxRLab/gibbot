#include <libpic30.h>
#include <p33EP512MC806.h>
#include "initializeV5.h"
#include "motor.h"
#include "UART.h"
#include "encoder.h"
#include "ADC.h"
#include "I2CMaster.h"
#include "MPU.h"


/* Configuration Bit Settings */
//To avoid setting the PLL bits while PLL is being used the oscillator is
//initially configured to use the FRC oscillator without phase lock loop
_FOSCSEL(FNOSC_FRC)
//OSC2 (pin 40) is clock output
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE)
//Watchdog timer not automatically enabled
_FWDT(FWDTEN_OFF)
//Programming on PGEC1 (pin 17) and PGED1 (pin 18)
//If programming pn PGEC2 and PGED2 change to ISC_PGD2
_FICD(ICS_PGD2 & JTAGEN_OFF)
//Wait 1ms after power-on to initialize
_FPOR(FPWRT_PWR128)

unsigned short resetStat;

/* The initialize function configures the PLL to set the internal clock
 * frequency. It also configures the digital IO and calls the initialization
 * functions for each of the modules. A light sequence signals the end of
 * initialization.
 */
void initialize(void){
    /* Configure Phase Lock Loop for  the system clock reference at 40MHz */
    // Fosc (Clock frequency) is set at 80MHz
    // Fin is 7.37 MHz from internal FRC oscillator
    // FPLLI = Fin/N1 = 3.685 MHz
    CLKDIVbits.PLLPRE = 0;   // N1 = 2
    // FVCO = FPLLI*M1 = 162.14MHz
    PLLFBDbits.PLLDIV = 42;  // M = 44
    // FPLLO = FVCO/N2 = 81.07 MHz
    // FOSC ~= 80MHz, FCY ~= 40MHz
    CLKDIVbits.PLLPOST = 0;  // N2 = 2

    /* Initiate Clock Switch */
    //The __builtin macro handles unlocking the OSCCON register
    __builtin_write_OSCCONH(1); //New oscillator is FRC with PLL
    __builtin_write_OSCCONL(OSCCON | 0x01); //Enable clock switch

    while (OSCCONbits.COSC!= 1); //Wait for FRC with PLL to be clock source
    while (OSCCONbits.LOCK!= 1); //Wait for PLL to lock

    /* Configure IO*/
    TRISDbits.TRISD10 = 1;   //USER input
    //LED outputs
    ANSELBbits.ANSB13 = 0;  //Disable Analog on B13
    TRISBbits.TRISB13 = 0;  //LED1
    ANSELBbits.ANSB12 = 0;  //Disable Analog on B12
    TRISBbits.TRISB12 = 0;  //LED2
    TRISDbits.TRISD11 = 0;  //LED3
    TRISDbits.TRISD0 = 0;   //LED4
    //Magnet Control
    TRISBbits.TRISB14 = 0;   //Top Magnet

    //Store bits indicating reason for reset
    resetStat = RCON;
    //Clear reset buffer so next reset reading is correct
    RCON = 0;

    /* Initialize peripherals*/
    initialize_PWM();
    initialize_CN();
    initialize_ADC();
    initialize_QEI();
    initialize_UART();
    initialize_UART2();
    initialize_I2C_Master();
    lights();
    __delay32(10000000);
    initialize_MPU();
    initialize_encoder_values(1600,1700,1800);
}

void lights(void){
    LED1 = 0;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
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
    LED1 = !(resetStat & RST_POR);
    LED2 = !(resetStat & RST_BOR);
    LED3 = !(resetStat & RST_EXTR);
    LED4 = !(resetStat & RST_CM);
    __delay32(10000000);
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
}