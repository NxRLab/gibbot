#include <p33FJ64MC802.h>

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC) // Use Internal Fast RC oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON) // Clock switching enabled and OSC2 pin is IO
_FWDT(FWDTEN_OFF) // watchdog timer controlled in software
//_FPOR(FPWRT_PWR128) // power on reset timer value
_FICD(ICS_PGD3 & JTAGEN_OFF) // using PGD3 programming pins and no jtag

void init_SPI(void);
void write_SPI(short);
unsigned int QEI_read(int);
void QEI_enable(int, int);
void QEI_disable(int);
void QEI_reset(int);
void init_UART(void);

int main() {

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
  while (OSCCONbits.LOCK != 1) {
  };

  // set the pins
  __builtin_write_OSCCONL(OSCCON & (~(1 << 6))); // clear bit 6
  // Pin Select for QEI1
  RPINR14bits.QEB1R = 0b01000; // QEA1B Pin Select (RP8)
  RPINR14bits.QEA1R = 0b00111; // QEA1A Pin Select (RP7)
  RPINR15bits.INDX1R = 0b11111; // INDX1R (VSS)

  RPINR16bits.QEB2R = 0b00001; // QEA2B Pin Select (RP8)
  RPINR16bits.QEA2R = 0b00010; // QEA2A Pin Select (RP7)
  RPINR17bits.INDX2R = 0b11111; // INDX2R (VSS)



  // Pin Select for SPI1
  //RPINR20bits.SCK1R = 0b01100; // SCK1 Pin Select (RP12)
  //RPINR20bits.SDI1R = 0b01101; // SDI1 Pin Select (RP13)
  //RPOR7bits.RP14R = 0b00111; // SDO1 Pin Select (RP14)
  //RPINR21bits.SS1R = 0b01111; // SS1 Pin Select (RP15)

  RPINR18bits.U1RXR = 0b01100; // U1RX on RP12
  RPOR7bits.RP14R = 0b00011; // U1TX on RP13

  RPOR1bits.RP3R = 0b10010; // OC1 on B3

  __builtin_write_OSCCONL(OSCCON | (1 << 6)); // Set bit 6

  AD1PCFGL = 0xFFFF;

  QEI_enable(1, 0xFFFF);
  QEI_enable(2, 0xFFFF);
  QEI_reset(1);
  QEI_reset(2);



  //init_SPI();
  init_UART();

  // Put a 50% 1kHz PWM on B3 to use as a heartbeat and know the board is working
  // Initialize Output Compare Module
  OC1CONbits.OCM = 0b000; // Disable Output Compare Module
  OC1R = 2500; // Write the duty cycle for the first PWM pulse
  OC1RS = 2500; // Write the duty cycle for the second PWM pulse
  OC1CONbits.OCTSEL = 0; // Select Timer 2 as output compare time base
  OC1R = 2500; // Load the Compare Register Value, 50%
  OC1CONbits.OCM = 0b110; // Select the Output Compare mode

  // Initialize and enable Timer2
  T2CONbits.TON = 0; // Disable Timer
  T2CONbits.TCS = 0; // Select internal instruction cycle clock
  T2CONbits.TGATE = 0; // Disable Gated Timer mode
  T2CONbits.TCKPS = 0b01; // Select 1:8 Prescaler
  TMR2 = 0x00; // Clear timer register
  PR2 = 5000; // Load the period value, so 40000000/8/5000 = 1000hz
  T2CONbits.TON = 1; // turn on timer2

  short read = 0;

  short pos;

  while (1) {

    //U1TXREG = 'U';
    //while (!U1STAbits.TRMT); // wait for the data to be sent out

    // if the RX buffer is full
    if(U1STAbits.URXDA == 1 & U1STAbits.TRMT==1) {
      read = U1RXREG;
      if (read == 1) {
          pos=1;
        //pos = QEI_read(1);
        U1TXREG = pos;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }

      if (read == 2) {
          pos=2;
        U1TXREG = pos;
                //pos>>8;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }

      if (read == 3) {
          pos=3;
        //pos = QEI_read(2);
        U1TXREG = pos;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
     }

      if (read == 4) {
          pos=4;
        U1TXREG = pos;
                //pos>>8;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }

      if (read == 5) {

        QEI_reset(1);
      }
      if (read == 6) {

        QEI_reset(2);
      }
      /*
      if (read == 1) {
        pos = QEI_read(1);

        U1TXREG = 10;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }
      if (read == 2) {

        U1TXREG = 11;//(pos>>8)&0xFF;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }
      if (read == 3) {
        pos = QEI_read(1);

        U1TXREG = pos;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }
      if (read == 4) {
        U1TXREG = (pos>>8)&0xFF;
        while (!U1STAbits.TRMT); // wait for the data to be sent out
      }
       * */
    }




/*
    // if the RX buffer is full
    if(SPI1STATbits.SPIRBF == 1) {
      read = SPI1BUF;

      // if 1 return encoder
      if (read == 1) {
        pos = QEI_read(1);
        SPI1BUF = (pos>>8)&0xFF;
        while (!SPI1STATbits.SPITBF); // wait for the data to be sent out
        SPI1BUF = pos&0xFF;
        while (!SPI1STATbits.SPITBF); // wait for the data to be sent out
      }

      // if 0 reset encoder to half and return encoder
      else if (read == 0) {
        QEI_reset(1);
        pos = QEI_read(1);
        SPI1BUF = (pos>>8)&0xFF;
        while (!SPI1STATbits.SPITBF); // wait for the data to be sent out
        SPI1BUF = pos&0xFF;
        while (!SPI1STATbits.SPITBF); // wait for the data to be sent out
      }
    }
     */
  }
}
/*
void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void) {
  unsigned int buffer;

  // Retrieve data from receive buffer
  IFS0bits.SPI1IF = 0; //Clear the interrupt flag
  SPI1STATbits.SPIROV = 0; //Clear any errors
  buffer = SPI1BUF; //Read in SPI1 buffer

  if (buffer == 1) {
    write_SPI(QEI_read(1));
  } else if (buffer == 2) {
    QEI_reset(1);
    write_SPI(QEI_read(1));
  }
}
*/

void init_UART(void) {
  U1MODEbits.UARTEN = 0; // UART1 disabled

U1BRG = 259;                    // Baud Rate settings for 9600bps @ 40MIPS
U1MODEbits.PDSEL = 0;      // 8-bit data, no parity
U1MODEbits.STSEL = 0;      // 1 Stop bit
U1MODEbits.UEN = 0;         // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
U1MODEbits.ABAUD = 0;      // Baud rate measurement disabled or completed
U1MODEbits.BRGH = 0;        // Low speed

U1MODEbits.UARTEN = 1;   // UART1 enabled
U1STAbits.UTXEN = 1;       // UARTx transmitter enabled
}
void init_SPI(void) {
  // setup the SPI peripheral
  //SPI1STAT = 0x0; // disable the SPI module (just in case)
  //SPI1CON1 = 0x0161; // FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
  //SPI1CON1bits.CKE = 0x01;
  //SPI1CON1bits.CKP = 0x00;
  //SPI1STAT = 0x8000; // enable the SPI module

  // CN pins are shared, turn them off
  CNEN1 = 0;
  CNEN2 = 0;

  /* The following code shows the SPI register configuration for Slave mode */
  SPI1BUF = 0;
  IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
  IEC0bits.SPI1IE = 0; // Disable the Interrupt
  // SPI1CON1 Register Settings
  SPI1CON1bits.DISSCK = 0; // Internal Serial Clock is Enabled
  SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module

  SPI1CON1bits.SSEN = 1; // use the slave select pin

  SPI1CON1bits.MODE16 = 0; // Communication is word-wide (16 bits)
  SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data
  // output time
  SPI1CON1bits.CKE = 0; // Serial output data changes on transition
  // from Idle clock state to active clock state
  SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; active
  // state is a high level
  SPI1CON1bits.MSTEN = 0; // Master mode Disabled
  SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred
  SPI1STATbits.SPIEN = 1; // Enable SPI module
  // Interrupt Controller Settings
  //IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
  //IEC0bits.SPI1IE = 1; // Enable the Interrupt
}

void write_SPI(short command) {
  short temp;

  //PORTGbits.RG15 = 0; // lower the slave select line
  temp = SPI1BUF; // dummy read of the SPI1BUF register to clear the SPIRBF flag
  SPI1BUF = command; // write the data out to the SPI peripheral
  while (!SPI1STATbits.SPIRBF); // wait for the data to be sent out
  //PORTGbits.RG15 = 1; // raise the slave select line
}

/***********************************************************
 *  read returns the count value of the QEI specified	*
 * If argument QEI is equal to 1, then the count value is	*
 *	returned from POS1CNT.  If QEI is a 2 then the			*
 *	value is returned from POS2CNT.							*
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
 * QEI enable turns the QEI device on which makes the		*
 *	device count pulses.									*
 * If the QEI1 argument is a 0 then QEI2 is enabled		  	*
 *	QEI1 is enabled.										*
 * The threshold is set for when the count should be reset 	*
 * Return value is used to report any count errors.  If any	*
 * exist, then the QEI_reset function should be called.	 	*
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




