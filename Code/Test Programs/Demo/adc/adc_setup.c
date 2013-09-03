// Library functions for ADC setup

#include <jvp002.h>
#include <misc.h>


void ADCSetup(void)
{
/*
To configure the ADC module, perform the following steps:
	1.Configure the analog port pins in AD1PCFG<15:0> (see 17.4.1).
	2.Select the analog inputs to the ADC multiplexers in AD1CHS<32:0> (see 17.4.2).
	3.Select the format of the ADC result using FORM<2:0> (AD1CON1<10:8>) (see 17.4.3).
	4.Select the sample clock source using SSRC<2:0> (AD1CON1<7:5>) (see 17.4.4).
	5.Select the voltage reference source using VCFG<2:0> (AD1CON2<15:13>) (see 17.4.7).
	6.Select the Scan mode using CSCNA (AD1CON2<10>) (see 17.4.8).
	7.Set the number of conversions per interrupt SMP<3:0> (AD1CON2<5:2>), if interrupts are to be used (see 17.4.9).
	8.Set Buffer Fill mode using BUFM (AD1CON2<1>) (see 17.4.10).
	9.Select the MUX to be connected to the ADC in ALTS AD1CON2<0> (see 17.4.11).
	10.Select the ADC clock source using ADRC (AD1CON3<15>) (see 17.4.12).
	11.Select the sample time using SAMC<4:0> (AD1CON3<12:8>), if auto-convert is to be used (see 17-2).
	12.Select the ADC clock prescaler using ADCS<7:0> (AD1CON3<7:0>) (see 17.4.12).
	13.Turn the ADC module on using AD1CON1<15> (see 17.4.14).
	14.To configure ADC interrupt (if required):
	a) Clear the AD1IF bit (IFS1<1>) (see 17.7).
	b) Select ADC interrupt priority AD1IP<2:0> (IPC<28:26>) and subpriority AD1IS<1:0>
	(IPC<24:24>) if interrupts are to be used (see 17.7).
	15.Start the conversion sequence by initiating sampling (see 17.4.15).
*/
	// Turn off the ADC module
	AD1CON1bits.ON = 0;
	// Configure the pins as analog input
	AD1PCFGbits.PCFG = 0x1200;
	// Configure TRIS as input
	TRISBbits.TRISB12 = 1;
	TRISBbits.TRISB9 = 1;
	// Negative input selections
	AD1CHSbits.CH0NB = 0;
	AD1CHSbits.CH0NA = 0;
	// Positive input selections
	AD1CHSbits.CH0SB = 0x09;
	AD1CHSbits.CH0SA = 0x0C;
	// Select the form of the ADC output (32 bit unsigned)
	AD1CON1bits.FORM = 0x04;
	// Select the sampling mode to auto conversion
	AD1CON1bits.SSRC = 0x00;
	// Voltage Reference Configuration bits, select AVDD and AVSS for reference
	AD1CON2bits.VCFG = 0x00;
	// Do not scan inputs of MUX A
	AD1CON2bits.CSCNA = 0x00;
	// Configure buffer as one 16-bit word
	AD1CON2bits.BUFM = 0x00;
	// Alternate between the two muxes
	AD1CON2bits.ALTS = 0;
	// Use peripheral bus clock
	AD1CON3bits.ADRC = 0;
	// Prescaler for the ADC clock
	AD1CON3bits.ADCS = 0x00;
	// No offset calibration at the moment
	AD1CON2bits.OFFCAL = 0x00;
	// Turn on the ADC module
	AD1CON1bits.ON = 1;	
}



void ReadADC(int* adc1, int* adc2)
{
	// Start sampling the ADC
	AD1CON1bits.SAMP = 1;
	
	// Wait for acq time
	wait(100);

	// End sampling the ADC
	AD1CON1bits.SAMP = 0;

	// Wait for conversion
	while(AD1CON1bits.DONE != 1);	
	
	// Manually clear the done bit
	AD1CON1bits.DONE = 0;

	*adc1 = ADC1BUF0;

	// Change to the other POT
	AD1CHSbits.CH0SA = 0x09;

	wait(100);

	// Start sampling the ADC
	AD1CON1bits.SAMP = 1;
	
	// Wait for acq time
	wait(100);

	// End sampling the ADC
	AD1CON1bits.SAMP = 0;
	
	// Wait for conversion
	while(AD1CON1bits.DONE != 1);	
	
	// Manually clear the done bit
	AD1CON1bits.DONE = 0;

	*adc2 = ADC1BUF0;

	// Change to the other POT
	AD1CHSbits.CH0SA = 0x0C;

	return;
}


