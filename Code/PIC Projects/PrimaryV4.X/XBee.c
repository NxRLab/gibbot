/* Configure the UART1 module to facilitate wireless communication with the PC
 * through the XBee. Received data from the PC initiates an RX interrupt. */
#include <libpic30.h>
#include <p33EP512MC806.h>
#include "XBee.h"

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    while (U1STAbits.URXDA){ // If there is data in the recieve register
        unsigned char data = U1RXREG; //save data
        U1TXREG = data; //echo data
    }
	IFS0bits.U1RXIF = 0;
}

void initialize_UART(void){
    // The UART module allows wireless communication with the computer via XBee
    /* XBee connections to the dsPIC are as follows:
     * RX   RP71/RD7
     * TX   RP70/RD6
     * CTS  RP65/RD1
     * RTS  RP66/RD2
     */
    // Unless issues with XBee communication prove that hardware flow
    // control is necessary, RTS and CTS will not be initialized.
    // Set TX pin as an output
    TRISDbits.TRISD6 = 0;
    //Set RP registers for UART1 RX and TX to connect UART module to those pins
    RPINR18bits.U1RXR = 71; //UART1 RX Tied to RP71 (RD7)
    RPOR3bits.RP70R = 1;     //RP70 (RD6) tied to UART1 TX
    ////Set RP registers for UART1 CTS and RTS
    //RPINR18bits.U1CTSR = 65; //UART1 CTS tied to RP65 (RD1)
    //RPOR1bits.RP66R = 2;     //RP66 tied to UART1 RTS (RD2)

    /* Set Baud Rate of 111,111. The XBee is not able to communicate
     * at the standard 115200 baud rate because of limitations with its internal
     * clock (Source: Footnote on table in "BD (Interface Data Rate) Command"
     * section of Product Manual v1.xEx - 802.15.4 Protocol).  */
    U1MODEbits.BRGH = 0; //Turn High Baud Rate Mode off
    // U1BRG = (Fcy/(16*Baud Rate)) - 1
    // U1BRG = (40MHz/(16*111,111)) - 1
    U1BRG = 22; //Baud Rate 108695 2.1% error
    //U1BRG = 21; Baud rate 113636 -2.3% error

    //UxTX and UxRX pins are enabled and used
    //UxCTS and UxRTS pins are controlled by port latches
    //To use U1CTS and U1RTS pins with module: U1MODEbits.UEN = 0b10;
    U1MODEbits.UEN = 0b00;

    IPC2bits.U1RXIP = 5;     // Set RX interrupt priority to 5
    IFS0bits.U1RXIF = 0;     // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;     // Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1;   //enable the UART
    U1STAbits.UTXEN = 1;     //Enable transmitting
}
