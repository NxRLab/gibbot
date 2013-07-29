#include <p33Fxxxx.h>
#include <libpic30.h>

void ADC_INIT(void);

signed int ADResultAN3_1 = 0;
signed int ADResultAN3_2 = 0;
signed int ADResultAN4 = 0;
signed int ADResultAN5 = 0;

int main(void) {
    ADC_Init();
    while (1)
    {
        AD1CON1bits.SAMP = 1;
        __delay_us(10);
        AD1CON1bits.SAMP = 0;
        while(!AD1CON1bits.DONE);
        ADResultAN3_1 = ADC1BUF0;
        ADResultAN3_2 = ADC1BUF1;
        ADResultAN4 = ADC1BUF2;
        ADResultAN5 = ADC1BUF3;
    }

    return 1;
}

void ADC_Init(void) {
    AD1CON1bits.FORM    = 1;
    AD1CON1bits.AD12B   = 0; // Select 10-bit mode
    AD1CON2bits.CHPS    = 3; // Select 4-channel mode
    AD1CON1bits.SIMSAM  = 1; // Enable Simultaneous Sampling
    AD1CON2bits.ALTS    = 0; // Disable Alternate Input Selection
    AD1CON1bits.ASAM    = 0; // Manual Sampling
    AD1CON1bits.SSRC    = 0; // Manual Trigger

    // Initialize MUXA Input Selection
    AD1CHS0bits.CH0SA       = 3; // Select AN3 for CH0 +ve input
    AD1CHS0bits.CH0NA       = 0; // Select VREF- for CH0 -ve input    //1 is AN1
    AD1CHS123bits.CH123SA   = 1; // Select CH1 +ve = AN3, CH2 +ve = AN4, CH3 +ve = AN5
    AD1CHS123bits.CH123NA   = 0; // Select VREF- for CH1/CH2/CH3 -ve inputs
    AD1CON1bits.SAMP        = 0;
    AD1CON1bits.ADON        = 1;

}