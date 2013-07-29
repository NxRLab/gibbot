#if 0
#include <plib.h>
#include <string.h>
#include <math.h>
#include "NU32_2012.h"

#define SYS_FREQ 80000000        // 80 MH0z
#define DIRECTION LATDbits.LATD1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0
#define DUTYCYCLE OC1RS

void main(void) {
    NU32_Startup();

    TRISDbits.TRISD1 = 0;
    DIRECTION = CLOCKWISE;

    /* clear current settings of peripherals */
    T2CON = 0; // this value will also turn off TMR2, T2CON<ON> = 0.
    OC1CON = 0; // this value will also turn off OC1, OC1CON<ON> = 0.

    /* configure the TMR2 options that aren't all zeros by default  */
    T2CONbits.TCKPS = 2; // set prescaler (PS) 1:4
    TMR2 = 0; // start TMR2 counting from zero.
    PR2 = 999; // set period match value
    /* now TMR2 has a period of (PR2 + 1) / PBCLK * PS = 50 us. */

    /* configure the OC1 options that aren't zero by default  */
    OC1CONbits.OCM = 0b110; // enable PWM mode with no fault protection
    DUTYCYCLE = 750; // set buffered PWM duty cycle in counts,
    // duty cycle is OC1RS/(PR2+1)
    OC1R = 750; // set initial PWM duty cycle in counts
    // don't write to OC1R while PWM is running (it's read-only),
    // instead use OC1RS.

    /* done configuring PWM, turn peripherals back on */
    T2CONbits.ON = 1; // turn on TMR2
    OC1CONbits.ON = 1; // turn OC1 back on

    /* some code ... */

    // now change the duty cycle to 50% by writing to OC1RS
    DUTYCYCLE = 600;
    while (1);
}

void _mon_putc(char c) {
    PutCharacter(UART1, c);
}
#endif