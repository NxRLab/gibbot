#ifndef NU32__H__
#define NU32__H__

#include <xc.h>                      // processor SFR definitions
#include <stdio.h>                   // sprintf
#include <cp0defs.h>                 // _CP0 macros
#include <sys/attribs.h>             // __ISR macro

#ifdef NU32_STANDALONE              // config bits if not set by bootloader

#pragma config DEBUG = OFF          // Background Debugger disabled
#pragma config FPLLMUL = MUL_20     // PLL Multiplier: Multiply by 20
#pragma config FPLLIDIV = DIV_2     // PLL Input Divider:  Divide by 2
#pragma config FPLLODIV = DIV_1     // PLL Output Divider: Divide by 1
#pragma config FWDTEN = OFF         // WD timer: OFF
#pragma config POSCMOD = HS         // Primary Oscillator Mode: High Speed xtal
#pragma config FNOSC = PRIPLL       // Oscillator Selection: Primary oscillator w/ PLL
#pragma config FPBDIV = DIV_1       // Peripheral Bus Clock: Divide by 1
#pragma config BWP = OFF            // Boot write protect: OFF
#pragma config ICESEL = ICS_PGx2    // ICE pins configured on PGx2, Boot write protect OFF.
#pragma config FSOSCEN = OFF        // Disable second osc to get pins back
#pragma config FSRSSEL = PRIORITY_7 // Shadow Register Set for interrupt priority 7

#endif // NU32_STANDALONE

#define NU32_LED1 LATAbits.LATA4    // LED1 on the NU32 board
#define NU32_LED2 LATAbits.LATA5    // LED2 on the NU32 board
#define NU32_USER PORTDbits.RD13    // user button on the NU32 board
#define NU32_SYS_FREQ 80000000ul    // 80 million Hz

void NU32_Startup(void);
void NU32_EnableUART1Interrupt(void);
void NU32_DisableUART1Interrupt(void);
void NU32_ReadUART1(char * string, int maxLength);
void NU32_WriteUART1(const char * string);
void NU32_EnableUART2WithInterrupt(void);
unsigned int NU32_ReadCoreTimer(void);
void NU32_WriteCoreTimer(unsigned int value);
unsigned int NU32_EnableInterrupts(void);
unsigned int NU32_DisableInterrupts(void);
void NU32_EnableCache(void);
void NU32_DisableCache(void);
#endif // NU32__H__
