/// Board definitions for the v6 primary PCB
/** @file

@warning the resolution of the current sensor is unknown for this board.  You
should look it up and insert the value in the Board.resolution member field of
this file (pv6.c).
*/

#include <boards/pv6.h>
#include <gibbot.h>

#define LED_DELAY 200
#define NBLINKS 4

const Board pv6 = {
        .name = BOARD_NAME,
        .init_pins = pv6_init_pins, 
        .init_periphs = pv6_init_periphs,
        .flash_lights = pv6_flash_lights,
    }; // all other fields default to zero

/** maps the primary board's peripherals to their respective I/O pins.
* 
*/

void pv6_init_pins()
{
    /**************************************/

    // configure USER button as input
    TRISDbits.TRISD10 = 1; // USER

    /**************************************/

    // configure LEDs as outputs
    ANSELBbits.ANSB13 = 0;  // disable analog on B13
    ANSELBbits.ANSB12 = 0;  // disable analog on B12
    TRISBbits.TRISB13 = 0;  // LED1
    TRISBbits.TRISB12 = 0;  // LED2
    TRISDbits.TRISD11 = 0;  // LED3
    TRISDbits.TRISD0 = 0;   // LED4
    
    /**************************************/

    // configure MAG as output
    ANSELBbits.ANSB14 = 0;  // disable analog on B14
    TRISBbits.TRISB14 = 0;   // MAG
    
    /**************************************/

    // configure HALL as change notification pins
    CNENDbits.CNIED3 = true; // turn on CN for RD3
    CNENDbits.CNIED4 = true; // turn on CN for RD4
    CNENDbits.CNIED5 = true; // turn on CN for RD5

    /**************************************/

    // configure dsPIC <-> XBee
    TRISDbits.TRISD2 = 1;       // set UART1 RX pin as input
    TRISDbits.TRISD1 = 0;       // set UART1 TX pin as output
    RPINR18bits.U1RXR = 66;     // map UART1 RX to RP66 (RD2)
    RPOR0bits.RP65R = 1;        // map UART1 TX to RP65 (RD1)
    RPINR18bits.U1CTSR = 70;    // map UART1 CTS to RP70 (RD6)
    RPOR3bits.RP71R = 2;        // map UART1 RTS to RP71 (RD7)

    /**************************************/

    // configure dsPIC <-> dsPIC
    TRISFbits.TRISF5 = 1; // set UART2 RX as input
    TRISFbits.TRISF4 = 0; // set UART2 TX as output
    RPINR19bits.U2RXR = 101; // map UART2 RX to RP101 (RF5)
    RPOR9bits.RP100R = 3; // map UART2 TX to RP100 (RF4)

    /**************************************/

    // configure ADC1 inputs for current module to sample
    AD1CSSLbits.CSS7 = true; // enable scanning of AN7

    /**************************************/

    // configure QEI1 for magnet encoder
    RPINR14bits.QEA1R = 99; // map RP99 to QEI1 A (F3)
    RPINR14bits.QEB1R = 98; // map RP98 to QEI1 B (F2) 

    /**************************************/
}

void pv6_init_periphs()
{
    init_xbee();
    init_pic2pic();
    init_cur(ALLEGRO_ACS716_12CB);
    init_magnet_enc(US_DIGITAL_E3_1800_750_NE_H_D_B);
    init_motor_pwm();
}

void pv6_flash_lights(void)
{
    int i;

    LED1 = LED_ON;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
    __delay_ms(LED_DELAY);
    LED1 = LED_OFF;
    LED2 = LED_ON;
    __delay_ms(LED_DELAY);
    LED2 = LED_OFF;
    LED3 = LED_ON;
    __delay_ms(LED_DELAY);
    LED3 = LED_OFF;
    LED4 = LED_ON;
    __delay_ms(LED_DELAY);
    LED4 = LED_OFF;
    for(i = 0; i < NBLINKS; i++) {
        __delay_ms(LED_DELAY);
        LED1 = !LED1;
        LED2 = !LED2;
        LED3 = !LED3;
        LED4 = !LED4;
    }

    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
}
