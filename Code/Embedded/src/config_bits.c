#include <xc.h>
// set the configuration bits for the project

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

// will eventually switch to #pragma, once I figure out what they mean.

/*

// 'C' source line config statements

#include <xc.h>

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit
(General Segment may be written)
#pragma config GSS = OFF                // General Segment Code-Protect bit
(General Segment Code protect is disabled)
#pragma config GSSK = OFF               // General Segment Key bits (General
Segment Write Protection and Code Protection is Disabled)

// FOSCSEL
#pragma config FNOSC = FRC              // Initial Oscillator Source Selection
bits (Internal Fast RC (FRC))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable
bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits
(Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock
output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration
(Allow only one reconfiguration)
#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock
switching and Fail-safe Clock Monitor are enabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits
(1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Wait Enable bit (Clock
switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit
(Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog
timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // Power-on Reset Timer Value Select
bits (128ms)
#pragma config BOREN = ON               // Brown-out Reset (BOR) Detection
Enable bit (BOR is enabled)
#pragma config ALTI2C1 = OFF            // Alternate I2C pins for I2C1
(SDA1/SCK1 pins are selected as the I/O pins for I2C1)

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select bits
(Communicate on PGEC2 and PGED2)
#pragma config RSTPRI = PF              // Reset Target Vector Select bit
(Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FAS
#pragma config AWRP = OFF               // Auxiliary Segment Write-protect bit
(Aux Flash may be written)
#pragma config APL = OFF                // Auxiliary Segment Code-protect bit
(Aux Flash Code protect is disabled)
#pragma config APLK = OFF               // Auxiliary Segment Key bits (Aux Flash
Write Protection and Code Protection is Disabled)

*/
