/********************************************************************
 * 7366_lib.c : Library functions for using the 7366R SPI decoder
 *
 * Creation date: 16-APR-2010
 * Last modified: 16-APR-2010
 *
 * Thomas Peterson
 *
 * Modified 30-MAY-2011 by Andy Wilson for NU32v2 Monkeybot with multiple LS7366R counters
 *
 *
 *
 * LIMS
 ********************************************************************/
 
#include <plib.h>
#include "7366.h"
#include "data.h"

void ss_low(int module) {
        if (module == MOT) {
                MOT_SS = 0;
        }
        if (module == MAG1) {
                MAG1_SS = 0; 
        }       
		if (module == MAG2) {
                MAG2_SS = 0; 
        }     
}

void ss_high(int module) {
        if (module == MOT) {
                MOT_SS = 1;
        }
        if (module == MAG1) {
                MAG1_SS = 1; 
        }       
		if (module == MAG2) {
                MAG2_SS = 1; 
        }     
}

/* enable_7366(): enables counting on 7366, sends configuration words
					and optionally turns on flags */
void enable_7366(int module, int config1, int flags) {
	unsigned char writebyte;
	writebyte = config1;	//config word 1
	write_7366(module, MDR0, &writebyte);
	writebyte = flags | (4-COUNTER_BYTES); //config word 2
	write_7366(module, MDR1, &writebyte);
}

void disable_7366_counting(int module) {
	//send disable to MDR1
	unsigned char writebyte;
	writebyte = COUNTER_BYTES;
	write_7366(module, MDR1, &writebyte);
}

/* write_7366(): Writes bytes in array "bytearray" to register "reg".
				 The number of bytes written depends on the reister and mode.
				 Config registers will write 1 byte. Other registers will
				 write the number of bytes specified by COUNTER_BYTES */
void write_7366(int module, int reg,unsigned  char *bytearray) {
	unsigned char ir = (0x2 << 6 ) | (reg << 3); //Instruction
	unsigned char ReadData;
	if ( (reg == MDR0) || (reg == MDR1) || (reg == STR) ) {
		//One byte to write
		ss_low(module);
		delay();							//Setup time
		SpiChnPutC(SPICHN, ir);				//Write instruction after TX buffer empty
        while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (nothing)
		SpiChnPutC(SPICHN, bytearray[0]);	//Clock out write byte after TX buffer empty
		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (garbage /dont care)
		ss_high(module);					//End comm
		return;		
	}
	if ( (reg == DTR) || (reg == CNTR) || (reg == OTR) ) {
		//1-4 bytes to read
		ss_low(module);
		delay();							//Setup time
		SpiChnPutC(SPICHN, ir);				//Write instruction after TX buffer empty
 		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (nothing)
		//Do reads
		int i;
		for (i=0;i<COUNTER_BYTES;i++) {
			SpiChnPutC(SPICHN, bytearray[i]);	//Clock out byte after TX buffer empty
    		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full
			ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (don't care)
		}	
		ss_high(module);		//End comm
		return;
	}
}


/* read_7366(): Reads bytes to array "bytearray" from register "reg".
				 The number of bytes read depends on the reister and mode.
				 Config registers will read 1 byte. Other registers will
				 read the number of bytes specified by COUNTER_BYTES */
void read_7366(int module, int reg, unsigned char *bytearray) {
	unsigned char ir = (0x1 << 6 ) | (reg << 3); //Instruction
	unsigned char ReadData;
	if ( (reg == MDR0) || (reg == MDR1) || (reg == STR) ) {
		//One byte to read
		ss_low(module);
		delay();							//Setup time
		SpiChnPutC(SPICHN, ir);				//Write instruction after TX buffer empty
 		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full	
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (nothing)
		SpiChnPutC(SPICHN, 0);				//Clock out dummy byte after TX buffer empty
 		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full	
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (register)
		*bytearray = ReadData;
		ss_high(module);		//End comm
		return;
	}
	if ( (reg == DTR) || (reg == CNTR) || (reg == OTR) ) {
		//1-4 bytes to read
		ss_low(module);
		delay();							//Setup time
		SpiChnPutC(SPICHN, ir);				//Write instruction after TX buffer empty
		while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full	
		ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (nothing)
		//Do reads
		int i;
		for (i=0;i<COUNTER_BYTES;i++) {
			SpiChnPutC(SPICHN, 0);				//Clock out dummy byte after TX buffer empty
 			while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full		
			ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (register)
			bytearray[i] = ReadData;
		}	
		ss_high(module);		//End comm
		return;
	}
}

/* clear_reg_7366(): Clears the given register */
void clear_reg_7366(int module, int reg) {
	char ReadData;
	char ir = (reg << 3);				//Instruction
	ss_low(module);	
	delay();							//Setup time
	SpiChnPutC(SPICHN, ir);				//Write instruction after TX buffer empty
    while(SpiChnRxBuffFull(SPICHN)==0); //Wait for RX buffer full
	ReadData = SpiChnGetC(SPICHN);		//Read what was clocked in during last write (nothing)
	ss_high(module);
}


void setup_counters() {
	//Init I/O
	//D1 has been set to slave select in 7366.h
	TRISDbits.TRISD1 = 0;	//Output for SS3
    TRISEbits.TRISE9 = 0;   //Output for SS2
    TRISEbits.TRISE6 = 0;   //Output for SS1

    ss_high(MOT); ss_high(MAG1); ss_high(MAG2);  // start all slave selects on high    

	//SPI setup
	int rData = SPI1BUF;    //Clears receive buffer
	IFS0CLR = 0x03800000;   //Clears any existing event (rx / tx/ fault interrupt)
	SPI1STATCLR = 0x40;      //Clears overflow
	//Enables the SPI channel (channel, master mode enable | use 8 bit mode | turn on, clock divider)
	SpiChnOpen(SPICHN, SPI_CON_MSTEN | SPI_CON_MODE8 | SPI_CON_ON|SPI_CKE_ON, 128);   // divide fpb by 128, configure the I/O ports.
	
	//Init 7366R
	enable_7366(MAG1,QUADRATURE_X4 | MODULO_N | DISABLE_INDX,NO_FLAGS);
    enable_7366(MAG2,QUADRATURE_X4 | MODULO_N | DISABLE_INDX,NO_FLAGS);
    enable_7366(MOT,QUADRATURE_X4 | MODULO_N | DISABLE_INDX,NO_FLAGS);
	
	unsigned char writebuf[COUNTER_BYTES];
	//Note that MSB should be in slot 0
	writebuf[1] = 0x58;
	writebuf[0] = 0x98;
	//Sets up DTR to contain 0x9858 = 39,000 (ticks/rev)
	write_7366(MAG1,DTR, writebuf);
	write_7366(MAG2,DTR, writebuf);
	write_7366(MOT,DTR, writebuf);
	clear_reg_7366(MAG1,STR);
	clear_reg_7366(MAG2,STR);
	clear_reg_7366(MOT,STR);
    clear_reg_7366(MAG1,CNTR);
	clear_reg_7366(MAG2,CNTR);
	clear_reg_7366(MOT,CNTR);
}


