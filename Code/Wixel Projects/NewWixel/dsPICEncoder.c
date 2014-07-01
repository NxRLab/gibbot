#include <p33FJ64MC802.h>
#include <stdio.h>

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC) // Use Internal Fast RC oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON) // Clock switching enabled and OSC2 pin is IO
_FWDT(FWDTEN_OFF) // watchdog timer controlled in software
//_FPOR(FPWRT_PWR128) // power on reset timer value
_FICD(ICS_PGD3 & JTAGEN_OFF) // using PGD3 programming pins and no jtag

enum {
    READ_ENC1_HI = 1,
    READ_ENC1_LO,
    READ_ENC2_HI,
    READ_ENC2_LO,
    RESET_ENC1,
    RESET_ENC2
};

unsigned int QEI_read(int);
void QEI_enable(int, int);
void QEI_disable(int);
void QEI_reset(int);
void init_clock_and_pins(void);
void init_UART(void);

int main() {
    unsigned int c;

    init_clock_and_pins();
    AD1PCFGL = 0xFFFF; // turn off ADC
    init_UART();
    QEI_enable(1, 0xFFFF);
    QEI_enable(2, 0xFFFF);
    QEI_reset(1);
    QEI_reset(2);

    while (1) {
        // wait for data to be received.
        while (!U1STAbits.URXDA);
        c = U1RXREG;

        // transmit data
        //while (U1STAbits.UTXBF);
        //U1TXREG = c;
        printf("%u\r\n", QEI_read(1));
    }
}

void init_clock_and_pins() {
    /* Configure Oscillator to operate the device at 40Mhz
     * Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
     * Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz
     */

    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 41; // M = 43
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2

    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);

    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);

    // set the pins
    __builtin_write_OSCCONL(OSCCON & (~(1 << 6))); // clear bit 6

    // Pin Select for QEI1
    RPINR14bits.QEB1R = 0b01000; // QEA1B Pin Select (RP8)
    RPINR14bits.QEA1R = 0b00111; // QEA1A Pin Select (RP7)
    RPINR15bits.INDX1R = 0b11111; // INDX1R (VSS)

    RPINR16bits.QEB2R = 0b00001; // QEA2B Pin Select (RP8)
    RPINR16bits.QEA2R = 0b00010; // QEA2A Pin Select (RP7)
    RPINR17bits.INDX2R = 0b11111; // INDX2R (VSS)

    // Pin Select for UART1
    RPINR18bits.U1RXR = 0b01100; // U1RX on RP12
    RPOR6bits.RP13R = 0b00011; // U1TX on RP13

    __builtin_write_OSCCONL(OSCCON | (1 << 6)); // Set bit 6
}

void init_UART(void) {
    U1MODEbits.UARTEN = 0; // UART1 disabled

    U1BRG = 259; // Baud Rate settings for 9600bps @ 40MIPS
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.STSEL = 0; // 1 Stop bit
    U1MODEbits.UEN = 0; // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
    U1MODEbits.ABAUD = 0; // Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0; // Low speed

    U1MODEbits.UARTEN = 1; // UART1 enabled
    U1STAbits.UTXEN = 1; // UARTx transmitter enabled
}

/***********************************************************
 *  read returns the count value of the QEI specified
 * If argument QEI is equal to 1, then the count value is
 *	returned from POS1CNT.  If QEI is a 2 then the
 *	value is returned from POS2CNT.
 * TODO: What if CNTERR is true?  Should return +'ve # if no err,
 * -'ve # otherwise.
 ***********************************************************/
unsigned int QEI_read(int QEI) {
    unsigned int QEI_Count = 0;

    // If there is no count error and QEI is 1 or 2, then we can continue.
    if ((1 == QEI) && 0 == QEI1CONbits.CNTERR)
        QEI_Count = POS1CNT; // Set the  count to POS1CNT or POS2CNT depending on QEI
    if ((2 == QEI) && 0 == QEI2CONbits.CNTERR)
        QEI_Count = POS2CNT; // Set the  count to POS1CNT or POS2CNT depending on QEI

    return QEI_Count;
}

/************************************************************
 * QEI enable turns the QEI device on which makes the
 *	device count pulses.
 * If the QEI1 argument is a 0 then QEI2 is enabled
 *	QEI1 is enabled.
 * The threshold is set for when the count should be reset
 * Return value is used to report any count errors.  If any
 * exist, then the QEI_reset function should be called.
 ************************************************************/
void QEI_enable(int QEI, int threshold) {

    if (1 == QEI && !QEI1CONbits.CNTERR) {
        QEI1CONbits.QEIM = 0b111;
        MAX1CNT = threshold >= 0 ? threshold : 0xFFFF; // The threshold is used to determine when to reset the clock
    }
    if (2 == QEI && !QEI2CONbits.CNTERR) {
        QEI2CONbits.QEIM = 0b111;
        MAX2CNT = threshold >= 0 ? threshold : 0xFFFF; // The threshold is used to determine when to reset the clock
    }
}

/***********************************************************
 * QEI disable turns the QEI device off.					*
 * If the QEI argument is a 1 then QEI1 is disabled		  	*
 *	if the QEI argument is a 2 then QEI2 is disabled		*
 * Return value is used to report any count errors.  If any	*
 * exist, then the QEI_reset function should be called.	 	*
 ***********************************************************/
void QEI_disable(int QEI) {
    if (QEI == 1) {
        QEI1CONbits.QEIM = 0;
    }
}

/***********************************************************
 * QEI reset cleares the count value and the count error.	*
 * If the QEI argument is a 1 then QEI1 is reset			*
 *	if the argument is a 2 then QEI2 is reset				*
 * Return value is used to report if any errors existed		*
 *	before calling the reset.								*
 ***********************************************************/
void QEI_reset(int QEI) {
    if (1 == QEI) {
        POS1CNT = 32768;
        QEI1CONbits.CNTERR = 0;
    }
    if (2 == QEI) {
        POS2CNT = 32768;
        QEI2CONbits.CNTERR = 0;
    }
}