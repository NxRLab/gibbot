/* 
 * File:   gibbot.h
 * Author: ajgriesemer
 *
 * Created on July 30, 2013, 10:39 AM
 */

#ifndef GIBBOT_H
#define	GIBBOT_H
#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>

#define SYSFREQ 7370000
#define S3 PORTBbits.RB7
#define S2 PORTBbits.RB8
#define S1 PORTBbits.RB9

/* Configuration Bit Settings */
//_FBS(BWRP_WRPROTECT_OFF) //Boot segment is not write protected (for debugging)
//_FGS(GWRP_OFF & GSS_OFF) //general segment is not write protected (for debugging)
_FOSCSEL(FNOSC_FRC) //Use internal FRC Oscillator at 7.37 MHz no PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
//Clock switching is enabled, Fail-Safe Clock Monitor is disabled
//OSC2 pin has digital I/O function
_FWDT(FWDTEN_OFF)
//Watchdog timer enabled/disabled by user software
_FPOR(FPWRT_PWR128 & LPOL_ON & HPOL_OFF)
//Power on Reset Timer is enabled for 128ms to allow system power to stablize
//PWM module low side output pins have active-high output polarity
//PWM module high side output pins have active-low output polarity
_FICD(ICS_PGD2 & JTAGEN_OFF)
//Communicate on PGC1/EMUC1 and PGD1/EMUD1
//JTAG is Disabled

void init_pwm(void);
void init_cn(void);
void init_uart (void);
void init_qei(void);

void duty(int duty);
void High(int pin);
void Float(int pin);
void Low(int pin);

void state1(void);
void state2(void);
void state3(void);
void state4(void);
void state5(void);
void state6(void);

char store;
char array[100];
char direction = 1;
int turncount = 500;

#endif	/* GIBBOT_H */

