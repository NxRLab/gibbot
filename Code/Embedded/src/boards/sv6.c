#include <boards/sv6.h>
#include <gibbot.h>

#define LED_DELAY 200
#define NBLINKS 4

const Board sv6 = {
        .name = BOARD_NAME,
        .init_pins = sv6_init_pins, 
        .init_periphs = sv6_init_periphs,
        .flash_lights = sv6_flash_lights,
    };

/** maps the secondary board's peripherals to their respective I/O pins.
* 
* This dsPIC's connections to a another PIC are as follows:
* RX   RP100/RF4
* TX   RP101/RF5
*
*/
void sv6_init_pins()
{
    /**************************************/

    // configure USER button as input
    TRISDbits.TRISD8 = 1; // USER

    /**************************************/

    // configure LEDs as outputs
    TRISDbits.TRISD9 = 0;  // LED1
    TRISDbits.TRISD10 = 0;  // LED2
    TRISDbits.TRISD11 = 0;  // LED3
    TRISDbits.TRISD0 = 0;   // LED4

    /**************************************/

    // configure MAG as output
    TRISBbits.TRISB15 = 0;   // MAG

    /**************************************/

    // configure dsPIC <-> dsPIC
    TRISFbits.TRISF4 = 1;       // set UART2 RX pin as input
    TRISFbits.TRISF5 = 0;       // set UART2 TX pin as output
    RPINR19bits.U2RXR = 100;     // map UART2 RX to RP100 (RF4)
    RPOR9bits.RP101R = 3;        // map UART2 TX to RP101 (RF5)

    /**************************************/

    // configure QEI1 for magnet encoder
    ANSELBbits.ANSB9 = 0;  // disable analog on B9
    ANSELBbits.ANSB10 = 0;  // disable analog on B10
    RPINR14bits.QEA1R = 42; // map RP42 to QEI1 A (B10)
    RPINR14bits.QEB1R = 41; // map RP41 to QEI1 B (B9) 

    /**************************************/

    // configure QEI2 for motor encoder
    RPINR16bits.QEA2R = 99; // map RP99 to QEI1 A (F3)
    RPINR16bits.QEB2R = 98; // map RP98 to QEI1 B (F2) 

    /**************************************/
}

void sv6_init_periphs()
{
    init_pic2pic();
    init_magnet_enc(US_DIGITAL_E3_1800_750_NE_H_D_B);
    init_motor_enc(US_DIGITAL_E3_1800_750_NE_H_D_B);
}

void sv6_flash_lights(void)
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
