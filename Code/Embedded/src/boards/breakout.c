/// Board definitions for the dsPIC breakout board 
/** @file
*/

#include <boards/breakout.h>
#include <gibbot.h>

/// Sets current readings so 0 V = -1.5 mA and 3.3 V = 1.5 mA
#define SCALED_VOLTS (2.0/3.3*VOLTS_PER_12BIT_COUNT)
#define LED_DELAY 200
#define NBLINKS 8
#define CPR 1800

const Board breakout = {
        .name = BOARD_NAME,
        .init_pins = breakout_init_pins, 
        .init_periphs = breakout_init_periphs,
        .flash_lights = breakout_flash_lights,
    };

/** maps the primary breakoutard's peripherals to their respective I/O pins.
* 
*/

void breakout_init_pins()
{
    /**************************************/

    // configure USER button as input
    TRISDbits.TRISD10 = 1; // USER

    /**************************************/

    // configure LEDs as outputs
    TRISCbits.TRISC14 = 0;  // LED1
    TRISCbits.TRISC13 = 0;  // LED2
    TRISDbits.TRISD0 = 0;   // LED3
    TRISDbits.TRISD11 = 0;  // LED4
    
    /**************************************/

    // configure MAG as output
    ANSELBbits.ANSB14 = 0;  // disable analog on B14
    TRISBbits.TRISB14 = 0;   // MAG
    
    /**************************************/

    // configure dsPIC <-> XBee
    TRISDbits.TRISD2 = 1;       // set UART1 RX pin as input
    TRISDbits.TRISD1 = 0;       // set UART1 TX pin as output
    RPINR18bits.U1RXR = 66;     // map UART1 RX to RP66 (RD2)
    RPOR0bits.RP65R = 1;        // map UART1 TX to RP65 (RD1)

    /**************************************/

    // configure dsPIC <-> dsPIC
    TRISFbits.TRISF5 = 1; // set UART2 RX as input
    TRISFbits.TRISF4 = 0; // set UART2 TX as output
    RPINR19bits.U2RXR = 101; // map UART2 RX to RP101 (RF5)
    RPOR9bits.RP100R = 3; // map UART2 TX to RP100 (RF4)

    /**************************************/

    // configure ADC1 inputs for current module to sample
    AD1CSSLbits.CSS3 = true; // enable scanning of AN1

    /**************************************/

    // configure QEI1 for magnet encoder
    RPINR14bits.QEA1R = 68; // map RP68 to QEI1 A (D4)
    RPINR14bits.QEB1R = 69; // map RP69 to QEI1 B (D5) 

    /**************************************/
}

void breakout_init_periphs()
{
    init_xbee();
    init_pic2pic();
    init_cur(SCALED_VOLTS);
    init_motor_pwm();
    init_magnet_enc(CPR);
}

void breakout_flash_lights(void)
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
