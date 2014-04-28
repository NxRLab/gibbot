/* Configure the ADC module to read the analog output from the current sensor.
 */
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "currentsensor.h"

void initialize_ADC(void) {
    /* The analog-digital voltage converter reads the voltage output
     * from the current sensor which is proportional to the motor drive current.
     */
    AD1CON1bits.FORM    = 0;  // Unsigned integer output
    AD1CON1bits.AD12B   = 1;  // 12-bit data output
    AD1CON2bits.ALTS    = 0;  // Disable alternate input selection
    AD1CON1bits.ASAM    = 0;  // Use manual sampling
    AD1CON1bits.SSRC    = 0b111; // Use an automatic trigger
    AD1CON1bits.SSRCG    = 0; // Use an automatic trigger
    AD1CON2bits.VCFG    = 0;  // Ensure AVDD and AVSS are used as Vref+ and Vref-
    AD1CON3bits.SAMC    = 15; //
    AD1CON3bits.ADCS = 9;     // Tad = 117.6ns = 10*Tcy,  Tcy = 12.5ns

    // Initialize MUXA Input Selection
    AD1CHS0bits.CH0SA = 8;
    AD1CON1bits.SAMP        = 0; // Ensure sampling is turned off
    AD1CON1bits.ADON        = 1; //Turn on the ADC converter
}

int ADC_Read(void) { //manual sampling and conversion function
    AD1CON1bits.SAMP = 1; //Start sampling, sampling is stopped after 1us
    while (!AD1CON1bits.DONE); //wait for sampling and conversion to finish
    return ADC1BUF0;
}