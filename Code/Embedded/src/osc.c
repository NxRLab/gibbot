/// Sets the instruction clock frequency
/** @file
*/

#include <gibbot.h>

/// Macro to set FPLLI = FRC/2 = 7.37 MHz/2 = 3.685 MHz
#define FPLLI_3_685_MHZ 0
/// Macro to set FVCO = FPLLI * 44 = 162.14 MHz
#define FVCO_162_14_MHZ 42
/// Macro to set FPLLO = FVCO/2 = 81.07 MHz
#define FPLLO_81_07_MHZ 0

/** sets the clock's speed to 40 MHz
* 
* The registers are set so that the 40 MHz clock signal is generated from
* the internal FRC oscillator running at 7.37 MHz.
*
*/
void init_osc_40_MHz()
{
    // set clock speed
    CLKDIVbits.PLLPRE = FPLLI_3_685_MHZ;
    PLLFBDbits.PLLDIV = FVCO_162_14_MHZ;
    CLKDIVbits.PLLPOST = FPLLO_81_07_MHZ;

    // initiate clock switch (__builtin handles unlocking the OSCCON register)
    __builtin_write_OSCCONH(1); // new oscillator is FRC with PLL
    __builtin_write_OSCCONL(OSCCON | 0x01); // enable clock switch

    // wait for FRC with PLL to be clock source
    while (OSCCONbits.COSC != 1); 

    // wait for PLL to lock
    while (OSCCONbits.LOCK == false); 

    // and now FOSC ~= 80 MHz, FCY ~= 40 MIPS (MHz)
}

