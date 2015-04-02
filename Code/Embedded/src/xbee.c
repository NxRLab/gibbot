/// Provides wireless communication over UART1
/** @file

    The XBee radio is configured for communicating at #XBEE_BAUD bps with no
    parity and 1 stop bit.  The lines for CTS/RTS are present, but not
    configured for use in software.  Extra code will have to be written if flow
    control is needed.

    The read and write functions a blocking.  They will not return unless the
    requested number of bytes have been read or written.  Additionally, the read
    function may return with fewer bytes if a new line #LF or carriage return
    #CR is received.
*/

#include <gibbot.h>

/** The XBee's baud rate.

    @note The XBee is not able to communicate at the standard 115200 baud rate
    because of limitations with its internal clock (Source: Footnote on table in
    "BD (Interface Data Rate) Command" section of Product Manual v1.xEx -
    802.15.4 Protocol).  
*/
#define XBEE_BAUD 111111UL 

/// Returns true if the XBee UART is present and enabled
bool is_xbee_on()
{
    return U1MODEbits.UARTEN;
}

/// Initializes the xbee communication UART
void init_xbee()
{
    U1MODEbits.BRGH = true; //Turn High Baud Rate Mode on
    U1BRG = calc_baud(XBEE_BAUD, true); //Baud Rate =112044 0.8% error

    // according to UART reference maual UTXEN must come after UARTEN
    U1MODEbits.UARTEN = true;   //enable the UART
    U1STAbits.UTXEN = true;     //Enable transmitting
}

/** Sends the content of the buffer to the XBee
    @param buffer the input buffer
    @param len the number of bytes to send from the buffer

    @note If there's a bug here don't forget to check write_pic2pic(),
    which has similar code.
*/
int write_xbee(void *buffer, unsigned int len)
{
    int i;
    char p, c;
    if (U1MODEbits.UARTEN == false || U1STAbits.UTXEN == false) {
        return EOF;
    }

    p = *(char *)(buffer);
    c = *(char *)(buffer);
    for (i = len; i; --i) {
        if(c == LF && p != CR) {
            while ((U1STAbits.TRMT) == false);
            U1TXREG  = CR;
        }

        while ((U1STAbits.TRMT) == false);
        U1TXREG  = c;
        
        p = c;
        c = *(char *)(++buffer);
    }

    return len - i;
}

/** Reads data sent from the XBee into the buffer
    @param buffer the destination buffer
    @param len the number of bytes to write into the buffer

    @note If there's a bug here don't forget to check read_pic2pic(),
    which has similar code.
    @note carriage returns (\r) are treated as line feeds (\n) characters
*/
int read_xbee(void *buffer, unsigned int len)
{
    int i;
    char b;

    if (!is_xbee_on()) {
        printf("read_xbee: the xbee is \"off.\" Major bug if this prints.\n");
        return EOF;
    }
    else if(_U1RXIE) {
        printf("read_xbee: can't poll for data while interrupt is active.\n");
        return 0;
    }
    else if (U1STAbits.OERR) {
        // clear overrun flag to keep receiving. clearing the flag before
        // reading the UART, deletes all data in fifo; this is fine since we
        // want the newest data
        U1STAbits.OERR = false;
        printf("read_xbee: overrun error.\n");
    }

    b = 0;
    for (i = len; (b != LF) && i; i--) {
        if (U1STAbits.FERR) {
            printf("read_xbee: frame error.\n");
            break; 
        }

        while ((U1STAbits.URXDA) == false);
        b = U1RXREG;

        if(b == CR) {
            b = LF;
        }

        *(char *) (buffer++) = b;
    }

    // return number of bytes read
    return len - i;
}
