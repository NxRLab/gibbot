#ifndef __NU32_2012_H
#define __NU32_2012_H

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

#endif // NU32_STANDALONE

#define NU32LED1 LATAbits.LATA4
#define NU32LED2 LATAbits.LATA5
#define NU32USER PORTCbits.RC13
#define SYS_FREQ 80000000           // 80 million Hz

void NU32_Startup();
void NU32_ReadUART1(char* string,int maxLength);
void NU32_WriteUART1(const char *string);
void NU32_EnableUART1Interrupt();
void NU32_DisableUART1Interrupt();
void WriteString(UART_MODULE id, const char *string);
void PutCharacter(UART_MODULE id, const char character);

#endif // __NU32_2012_H
