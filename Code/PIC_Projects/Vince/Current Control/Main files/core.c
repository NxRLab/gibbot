
#include "core.h"
#include <p33EP512MC806.h>
//#include "dee_emulation_pic32.h" /// emulates an eeprom using program flash (thanks microchip!)

#define AVERAGES 20	/// the number of averages we take when reading the ADC

//enum State core_state = IDLE; // the current state
int core_state = COAST; // the current state


/// @brief Initialized the analog to digital converter for
///	   manual sampling, automatic conversion, on AN0 only
///	   Tad = 75 ns, Sampling time = 3 * Tad = 225 ns
static void adc_init(void);




/// @brief Communcicates with the encoder
///
/// @param read - if 1 reads the current value, if 0 sends a reset command
/// @return the response from the encoder
static int encoder_send(int read);

void core_init(void)
{
	//DataEEInit();		//initialize eeprom emulation
        //TODO in future: establish eeprom to save gains to memory
	core_state = COAST;	//initialize the state
	adc_init();     	//initialize the analog to digital converter
	//initialize_QEI(); 	//initialize the encoders
        //TODO: see encoder_init function below
};

short core_adc_read() 
{
    int avg = 0;
    int i = 0;

    for (i = 0; i != AVERAGES; ++i) // read from the ADC AVERAGES times
    {
        /*
        AD1CON1bits.SAMP = 1;	    // start sampling
        while (!AD1CON1bits.DONE)   // wait for conversion to complete
	{
		;
	}
        */
        avg += ADC1BUF0;	    // accumulate the current reading
    }

    return avg / AVERAGES;	    // return the average of all readings
}

void core_encoder_reset(void)
{
	encoder_send(0);
}

int core_encoder_read(void)
{
	encoder_send(1);	//we need to read twice to get a valid reading
	return encoder_send(1);
}

static void adc_init(void)
{
    /*
	// setup the analog to digital converter
	//AD1PCFG = 0xFFFE; 		// bit 1 is zero, so AN0 is input
	AD1CHS0bits.CH0SA = 7; 		// connect bit 0 as input
        // The above value was changed from 0 to 7 (see old ADC.c)
	AD1CON1bits.ASAM = 0;		// start sampling manually
	AD1CON1bits.SSRC = 0b111;	// automatic conversion after sampling
	AD1CON3bits.ADRC = 0;		// use the peripheral bus clock, which is at 80 MHz
	AD1CON3bits.ADCS = 9; 		// ADC clock period is Tad = 2 * (ADCS+1) * Tpb = 75 ns, (Tbp = 12.5 ns)
        // The above value was changed from 2 to 9 (see old ADC.c)
	AD1CON3bits.SAMC = 15;		// sampling is 3 * Tad = 225 ns
        // The above value was changed from 3 to 15 (see old ADC.c)
	AD1CON1bits.ADON = 1; 		// turn on A/D converter
   */
}

/*static void encoder_init(void) //TODO: make this work with new encoder
 * when finished, uncomment all encoder functions and calls
 * THIS FUNCTION HAS BEEN REPLACED WITH initialize_QEI() in encoder.c
{
	// Author:  Nick Marchuck
	// SPI initialization for reading from the encoder chip
	SPI4CON = 0; 		 // stop and reset SPI4
	volatile int data = 0;
	data = SPI4BUF;		 // clear the rex buffer
	
	SPI4BRG = 0x4; 		 // bit rate to 8MHz, SPI4BRG = 80000000/(2*desired)-1
	SPI4STATCLR = 0x40; 	 // clear overflow
	SPI4CON = 0x100086A0; 	 // MSSEN ON to enable SS, SPI ON, 16 bit xfer, SMP=1, Master Mode
}
*/

static int encoder_send(int read)
{
	// Author: Nick Marchuck
	int data = 0, temp = 0;
	
	SPI4BUF = read; // request the encoder position
	/*
	while (!SPI4STATbits.SPIRBF)
	{
		;
	}

	data = SPI4BUF; // garbage was transfered over, ignore it
	SPI4BUF = 5;   // write garbage, but the corresponding read will have the data
	while (!SPI4STATbits.SPIRBF)
	{
		;
	}
    	temp = SPI4BUF;
        */
	return temp;
}

#define MAX_REGISTERS 10
static int * registered_ints[MAX_REGISTERS];
static float * registered_floats[MAX_REGISTERS];
static int nints = 0;
static int nfloats = 0;

void core_register_int(int * a)
{
	if(a && nints < MAX_REGISTERS)
	{
		registered_ints[nints] = a;
		++nints;
	}
}

void core_register_float(float * a)
{
	if (a && nfloats < MAX_REGISTERS)
	{
		registered_floats[nfloats] = a;
		++nfloats;
	}
}

/*void core_gains_save()
{
	INTDisableInterrupts();
	DataEEWrite(0xDEAD,0);
	
	int i = 0;
	for(i = 0; i != nints; ++i)
	{
		DataEEWrite(*registered_ints[i],i+1);
	}

	for(i = 0; i != nfloats; ++i)
	{
		DataEEWrite(*((unsigned int*)registered_floats[i]),i+1+nints);
	}
	INTEnableInterrupts();
}

void core_gains_load()
{
	INTDisableInterrupts();
	unsigned int data = 0;
	DataEERead(&data,0);
	if(data == 0xDEAD) //we have written to flash before
	{
		int i = 0;
		for(i = 0; i != nints; ++i)
		{
			DataEERead((unsigned int *)registered_ints[i],i+1);
		}

		for(i = 0; i != nfloats; ++i)
		{
			DataEERead((unsigned int*)registered_floats[i],i+1+nints);
		}
	}
	INTEnableInterrupts();
}
*/
//TODO: make the gain saving and loading function properly