#ifndef __DATA_H_
#define __DATA_H_

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

#define ACC1X ReadADC10(3)
#define ACC1Y ReadADC10(0)
#define ACC2X ReadADC10(14) // B14
#define ACC2Y ReadADC10(12) // B12

#define GYRO1LO ReadADC10(1) // B1 (4z)
#define GYRO1HI ReadADC10(5) // B5 (z)
#define GYRO2LO ReadADC10(13) // B12 (4z)
#define GYRO2HI ReadADC10(9) // B9 (z)

#define CURRENT ReadADC10(15)

#define SYS_FREQ 80000000  		// 80 MHz

#define DESIRED_BAUDRATE_NU32 38400	// wireless baudrate

#define COUNTERBYTES 2

int timesec;
char RS232_Out_Buffer[32];  // Buffer for sprintf in serial communication
int HBridgeDuty;
unsigned char readbuf[COUNTERBYTES];
int start;
int delay1;
int delay2;
int delay3;

#endif /* __DATA_H_ */
