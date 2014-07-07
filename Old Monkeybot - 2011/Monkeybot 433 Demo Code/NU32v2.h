#ifndef __NU32v2_H
#define __NU32v2_H

#define LED0     LATGbits.LATG12
#define LED1     LATGbits.LATG13
#define SW       PORTGbits.RG6

#define EMAG1	LATCbits.LATC1
#define EMAG2	LATEbits.LATE7

#define GSEL1 LATEbits.LATE2
#define GSEL2 LATCbits.LATC13

#define FALL1 PORTAbits.RA0
#define FALL2 PORTAbits.RA4

#define DIR LATAbits.LATA9

#define ACC1X ReadADC10(3)
#define ACC1Y ReadADC10(0)
#define ACC2X ReadADC10(14)
#define ACC2Y ReadADC10(12)

#define GYRO1LO ReadADC10(1) //i.e. 4z, high speed/low resolution
#define GYRO1HI ReadADC10(5)
#define GYRO2LO ReadADC10(13)
#define GYRO2HI ReadADC10(9)

#define CURRENT ReadADC10(15)

#define SYS_FREQ 80000000  				// 80 MHz

#define DESIRED_BAUDRATE_NU32 38400	// wireless baudrate
int timesec;
void initLEDs(void);
void delaysec(int tref);
// Serial Functions
void initSerialNU32v2();
void WriteString(UART_MODULE id, const char *string);
void PutCharacter(UART_MODULE id, const char character);


char RS232_Out_Buffer[32];  // Buffer for sprintf in serial communication

#endif // __NU32v2_H


