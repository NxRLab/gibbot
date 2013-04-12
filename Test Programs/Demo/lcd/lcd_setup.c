// LCD Setup for JVP002 Board rev B

#include <jvp002.h>
#include <misc.h>


void LCDConfig(void)
{
// PMCON
	// Turn off PMP Module
	PMCONbits.ON = 0;
/*
The following list illustrates an example setup for a typical Master mode 2 operation:
1.Select Master mode 2: MODE<1:0> bits (PMMODE<9:8>) = 10.
2.Select 16-bit Data mode: MODE16 bit (PMMODE<10>) = 0.
3.Select partially multiplexed addressing: ADRMUX<1:0> bits (PMCON<12:11>) = 01.
4.Select auto address increment: INCM<1:0> bits (PMMODE<12:11>) = 01.
5.Enable Interrupt Request mode: IRQM<1:0> bits (PMMODE<14:13>) = 01.
6.Enable PMRD strobe: PTRDEN bit (PMCON<8>) = 1.
7.Enable PMWR strobe: PTWREN bit (PMCON<9>) = 1.
8.Enable PMCS2 and PMCS1 Chip Selects: CSF<1:0> bits (PMCON<7:6>) = 10.
9.Select PMRD active-low pin polarity: RDSP bit (PMCON<0>) = 0.
10.Select PMWR active-low pin polarity: WRSP bit (PMCON<1>) = 0.
11.Select PMCS2, PMCS1 active-low pin polarity: CS2P bit (PMCON<4>) =0 and CS1P bit (PMCON<3>) = 0.
12.Select 1 wait cycle for data setup: WAITB<1:0> bits (PMMODE<7:6>) = 00.
13.Select 2 wait cycles to extend PMRD/PMWR: WAITM<3:0> bits (PMMODE<5:2>) = 0001.
14.Select 1 wait cycle for data hold: WAITE<1:0> bits (PMMODE<1:0>) = 00.
15.Enable upper 8 PMA<15:8> address pins: PMAEN<15:8> =1 (the lower 8 bits can be used as general purpose I/O).
*/


// PMMODE
	// Set the mode to master mode 1 (page 13-47 on PMP)
	PMMODEbits.MODE = 0x3;
	// Set the MODE16 bit off
	PMMODEbits.MODE16 = 0;
	// Select fully demultiplexed data/address
	PMCONbits.ADRMUX = 0x00;
	// Select no increment
	PMMODEbits.INCM = 0x00;
	// Disable Interrupt Request mode
	PMMODEbits.IRQM = 0x00;
	// Enable PMRD Strobe
	PMCONbits.PTRDEN = 1;
	// Enable PMWR strobe
	PMCONbits.PTWREN = 1;
	// Disable Chip selects
	PMCONbits.CSF = 0x00;
	// Select PMRD active high pin polarity
	PMCONbits.RDSP = 1;
	// Select PMEN active high pin polarity
	PMCONbits.WRSP = 1;
	// Set the wait delays as long as possible
	PMMODEbits.WAITB = 0x03;
	PMMODEbits.WAITM = 0x0F;
	PMMODEbits.WAITE = 0x03;
	
	// Set A0 as the only active address pin
	PMAENbits.PTEN = 0x0001;

// PMCON
	// Turn on PMP Module
	PMCONbits.ON = 1;		
}

void LCDSetup(void)
{
// Begin Writing to LCD
	// Set the address to write commands
	PMADDR = 0x00;
	
// Configure the LCD
	// Clear the display
	PMDIN = 0x01;
	wait(1000);
	// Turn display off
	PMDIN = 0x08;
	wait(1000);
	// Set the interface to two rows,8 bit interface, 5x10 dots
	PMDIN = 0x3C;
	wait(1000);
	// Turn on display, cursor, and blinking
	PMDIN = 0x0F;
	wait(1000);
}


void WriteLCD(int line, char* characters)
{
	int i = 0;
	int j = 0;
	int letter;
	PMADDR = 0x00;
	switch(line)
	{
		case 0:
		case 1:
			PMDIN = 0x02;
			PMADDR = 0x01;
			letter = (int)(characters[i]);
			while(letter != 0 && i<16)
			{
				wait(1000);
				PMDIN = letter;
				i++;
				letter = (int)(characters[i]);
			}
			if(i != 16)
				break;
			else
			{
				PMADDR = 0x00;
				wait(1000);
			}
		case 2:
			PMDIN = 0xC0;
			PMADDR = 0x01;
			letter = (int)(characters[i]);
			while(letter != 0 && j<16)
			{
				wait(1000);
				PMDIN = letter;
				i++;
				j++;
				letter = (int)(characters[i]);
			}
			break;
	}
}


void ClearLCDScreen(void)
{
	// Set the address to write commands
	PMADDR = 0x00;
	// Clear the display
	PMDIN = 0x01;
	wait(1000);	
}
