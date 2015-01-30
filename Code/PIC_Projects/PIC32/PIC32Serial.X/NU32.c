#include "NU32.h"

#define NU32_DESIRED_BAUD 112044//115200//230400 // Baudrate for RS232

// Perform startup routines:
//  Make NU32_LED1 and NU32_LED2 pins outputs (NU32USER is by default an input)
//  Initialize the serial port - UART1 (no interrupt) 
//  Enable interrupts

void NU32_Startup() {
    // disable interrupts
    NU32_DisableInterrupts();

    // enable the cache
    NU32_EnableCache();

    // set the prefectch cache wait state to 2, as per the
    // electrical characteristics data sheet
    CHECONbits.PFMWS = 0x2;

    //enable prefetch for cacheable and noncacheable memory
    CHECONbits.PREFEN = 0x3;

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get A4 and A5 back
    DDPCONbits.JTAGEN = 0;

    TRISACLR = 0x0030; // Make A5 and A4 outputs (LED2 and LED1)
    NU32_LED1 = 1; // LED1 is off
    NU32_LED2 = 0; // LED2 is on

    // turn on UART1 without an interrupt
    U1MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
    U1BRG = ((NU32_SYS_FREQ / NU32_DESIRED_BAUD) / 16) - 1;

    // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

    // configure TX & RX pins as output & input pins
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    // configure using RTS and CTS
    U1MODEbits.UEN = 2;

    // enable the uart
    U1MODEbits.ON = 1;

    NU32_EnableInterrupts();
}

// Enable UART1 interrupt.

void NU32_EnableUART1Interrupt(void) {
    // disable interrupts
    unsigned int status = NU32_DisableInterrupts();
    // turn off the module to change the settings
    U1MODEbits.ON = 0;

    // Clear the RX interrupt Flag
    IFS0bits.U1RXIF = 0;

    // Configure UART1 RX Interrupt
    // configure RX to interrupt whenever a character arrives
    U1STAbits.URXISEL = 0;
    IPC6bits.U1IP = 2;
    IPC6bits.U1IS = 0;
    IEC0bits.U1RXIE = 1;

    // turn on the UART
    U1MODEbits.ON = 1;

    //only re-enable interrupts if they were enabled prior to calling
    //this function
    if (status & 0x1) {
        NU32_EnableInterrupts();
    }
}

// Disable UART1 interrupt, so you can use NU32_ReadUART1 again

void NU32_DisableUART1Interrupt(void) {
    unsigned int status = NU32_DisableInterrupts();
    // turn off the module to change the settings
    U1MODEbits.ON = 0;

    // Configure UART1 RX Interrupt to off
    IEC0bits.U1RXIE = 0;

    // turn on the UART
    U1MODEbits.ON = 1;
    //only re-enable interrupts if they were enabled prior to calling
    //this function
    if (status & 0x1) {
        NU32_EnableInterrupts();
    }
}

// Read from UART1
// block other functions until you get a '\r' or '\n'
// send the pointer to your char array and the number of elements in the array

void NU32_ReadUART1(char * message, int maxLength) {
    char data = 0;
    int complete = 0, num_bytes = 0;
    // loop until you get a '\r' or '\n'
    while (!complete) {
        if (U1STAbits.URXDA) { // if data is available
            data = U1RXREG; // read the data
            if ((data == '\n') || (data == '\r')) {
                complete = 1;
            } else {
                message[num_bytes] = data;
                ++num_bytes;
                // roll over if the array is too small
                if (num_bytes >= maxLength) {
                    num_bytes = 0;
                }
            }
        }
    }
    // end the string
    message[num_bytes] = '\0';
}

// Write a charater array using UART1

void NU32_WriteUART1(const char * string) {
    while (*string != '\0') {
        while (U1STAbits.UTXBF) {
            ; // wait until tx buffer isn't full
        }
        U1TXREG = *string;
        ++string;
    }
}

// Read the value from the core timer (the timer that is part of the cpu)

unsigned int NU32_ReadCoreTimer(void) {
    // the core timer count is the Coprocessor 0 (cp0) COUNT register
    // This is part of the cpu.  For details see
    // Section 2 Cpu For Devices with the M4k Core of the PIC32 reference manual
    return _CP0_GET_COUNT();
}

// write a value to the core timer (the timer that is part of the cpu)

void NU32_WriteCoreTimer(unsigned int value) {
    // the core timer updates the cp0 COUNT register, so set that
    _CP0_SET_COUNT(value);
}

// enable interrupts, and return the previous value of the cp0 STATUS register

unsigned int NU32_EnableInterrupts(void) {
    return __builtin_enable_interrupts();
}

// disable interrupts and return the previous value of the cp0 STATUS register

unsigned int NU32_DisableInterrupts(void) {
    return __builtin_disable_interrupts();
}


// Enable the cache

void NU32_EnableCache(void) {
    // This command sets the CP0 CONFIG register
    // the lower 4 bits can be either 0b0011 (0x3) or 0b0010 (0x2)
    // to indicate that kseg0 is cacheable (0x3) or uncacheable (0x2)
    // see Chapter 2 "CPU for Devices with M4K Core" of the PIC32 reference manual
    // most of the other bits have prescribed values
    // microchip does not provide a _CP0_SET_CONFIG macro, so we directly use
    // the compiler built-in command _mtc0
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
}

// Disable the cache

void NU32_DisableCache(void) {
    // Set the CP0 CONFIG register to make kseg0 uncacheable
    // (See NU32_EnableCache())
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210582);
}

/******************** Gibbot Changes ********************************/

// see p. 28 of Lynch, Marchuk, and Elwin ME 333 Book.
// UART2 RX - pin F4
// UART2 TX - pin F5

void NU32_EnableUART2WithInterrupt(void) {
    // disable interrupts
    unsigned int status = NU32_DisableInterrupts();
    // turn off the module to change the settings
    U2MODEbits.ON = 0;

    // Clear the RX interrupt Flag
    IFS1bits.U2RXIF = 0;

    // turn on UART2
    U2MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
    U2BRG = ((NU32_SYS_FREQ / NU32_DESIRED_BAUD) / 16) - 1;

    // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    // configure TX & RX pins as output & input pins
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // configure using RTS and CTS
    // U2MODEbits.UEN = 2;

    // enable the uart
    U2MODEbits.ON = 1;

    // Configure UART2 RX Interrupt
    // configure RX to interrupt whenever a character arrives
    U2STAbits.URXISEL = 0;
    IPC8bits.U2IP = 2;
    IPC8bits.U2IS = 0;
    IEC1bits.U2RXIE = 1;

    // turn on the UART
    U2MODEbits.ON = 1;

    //only re-enable interrupts if they were enabled prior to calling
    //this function
    if (status & 0x1) {
        NU32_EnableInterrupts();
    }
}

void __ISR(_UART_1_VECTOR, IPL2SOFT) UART1Interrupt() {
    char data = 0;
    if (IFS0bits.U1RXIF) {
        // Clear the RX interrupt Flag
        IFS0bits.U1RXIF = 0;

        if (U1STAbits.URXDA) { // if data is available
            data = U1RXREG; // read the data
            while(U2STAbits.UTXBF); // wait until tx buffer isn't full
            // send PC byte on through from UART2 to XBEE
            U2TXREG = data;
            
            NU32_LED1 = !NU32_LED1; // toggle the LEDs
        }
    }
    else {
        IFS0bits.U1TXIF = 0;
    }
}

void __ISR(_UART_2_VECTOR, IPL2SOFT) UART2Interrupt() {
    char data = 0;
    if (IFS1bits.U2RXIF) {
        // Clear the RX interrupt Flag
        IFS1bits.U2RXIF = 0;
        if (U2STAbits.URXDA) { // if data is available
            data = U2RXREG; // read the data
            while (U1STAbits.UTXBF); // wait until tx buffer isn't full
            // send XBEE byte on through from UART2 to PC
            U1TXREG = data;

            NU32_LED2 = !NU32_LED2;
        }
    }
    else {
        IFS1bits.U2TXIF = 0;
    }
}