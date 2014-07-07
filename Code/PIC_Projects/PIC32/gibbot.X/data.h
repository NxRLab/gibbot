#ifndef __DATA_H_
#define __DATA_H_

/*Pound defines for system config*/
#define SYS_FREQ 80000000  		// 80 MHz
#define DESIRED_BAUDRATE_NU32 38400	// wireless baudrate
/*Pound defines for system config*/


/*Pound defines for digital outputs*/
#define LED0 LATGbits.LATG12
#define LED1 LATGbits.LATG13
#define SW PORTGbits.RG6

#define EMAG1 LATCbits.LATC1
#define EMAG2 LATEbits.LATE7

#define GSEL1 LATEbits.LATE2
#define GSEL2 LATCbits.LATC13

#define FALL1 PORTAbits.RA0
#define FALL2 PORTAbits.RA4

#define DIR LATAbits.LATA9

#define MOT_SS LATDbits.LATD1
#define MAG1_SS LATEbits.LATE6
#define MAG2_SS LATEbits.LATE9
/*Pound defines for digital outputs*/


/*Pound defines for ADC Macro reads*/
#define ACC1X ReadADC10(3)
#define ACC1Y ReadADC10(0)
#define ACC2X ReadADC10(14) // B14
#define ACC2Y ReadADC10(12) // B12
#define GYRO1LO ReadADC10(1) // B1 (4z)
#define GYRO1HI ReadADC10(5) // B5 (z)
#define GYRO2LO ReadADC10(13) // B12 (4z)
#define GYRO2HI ReadADC10(9) // B9 (z)
#define CURRENT ReadADC10(15)
/*Pound defines for ADC Macro reads*/

//Use the following to specifity the number of bytes the counter is
// Valid range is 1-4
// Issues here. which one are they using?
#define COUNTER_BYTES 2
#define COUNTERBYTES 2

//1,2,3,4 for SPI1, SPI2, SPI3, or SPI4
#define SPICHN 1

/* Configuration words - Use at most ONE per group */
//Count modes
#define NON_QUADRATURE 0
#define QUADRATURE_X1 0x01
#define QUADRATURE_X2 0x02
#define QUADRATURE_X4 0x03
//Running modes
#define FREE_RUN 0
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C
//Index modes
#define DISABLE_INDX 0
#define INDX_LOADC 0x10
#define INDX_RESET 0x20
#define INDX_LOADO 0x30
//Index synchronous modes
#define ASYNCH_INDX 0
#define SYNCH_INDX 0x80
//Clock filter modes
#define FILTER_1 0
#define FILTER_2 0x80
/* Configuration words - Use at most ONE per group */


/* Valid flags- Any of these config words can be ORed together */
#define NO_FLAGS 0
#define IDX_FLAG 0x10;
#define CMP_FLAG 0x20;
#define BW_FLAG 0x40;
#define CY_FLAG 0x80;
/* Valid flags- Any of these config words can be ORed together */


/* Register list: for use with write_7366, read_7366, and clear_reg_7366 functions */
#define MDR0 0x1
#define MDR1 0x2
#define DTR 0x3		//1-4 bytesw
#define CNTR 0x4	//1-4 bytesw
#define OTR 0x5		//1-4 bytesw
#define STR 0x6
/* Register list: for use with write_7366, read_7366, and clear_reg_7366 functions */


/* Differentiating between 7366 chips */
enum{MOT, MAG1, MAG2};

/* enum is a better fit in this case
#define MOT 1
#define MAG1 2
#define MAG2 3
*/
/* Differentiating between 7366 chips */


// Global variables
int timesec;
char RS232_Out_Buffer[32];  // Buffer for sprintf in serial communication
int HBridgeDuty;
unsigned char readbuf[COUNTERBYTES];
int start;
int delay1;
int delay2;
int delay3;

#endif /* __DATA_H_ */
