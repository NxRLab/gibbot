#include <gibbot.h>

/// @file

/// The PIC-to-PIC baud rate
//#define PIC_BAUD (16UL*115200UL)
#define PIC_BAUD (115200UL)

/// Returns true if the PIC-to-PIC peripheral is present and enabled
bool is_pic2pic_on()
{
    return U2MODEbits.UARTEN;
}

/// Initializes the inter-board communication module
void init_pic2pic() 
{
    // set up UART2 to receive requests from other PIC
    U2MODEbits.BRGH = true; // turn High Baud Rate Mode On
    U2BRG = calc_baud(PIC_BAUD, true);

    U2MODEbits.UARTEN = true; // enable the UART
    U2STAbits.UTXEN = true; // enable transmitting
}

/** Sends the content of the buffer to the other PIC
    @param buffer the input buffer
    @param len the number of bytes to send from the buffer

    @note If there's a bug here don't forget to check write_xbee(),
    which has similar code.
*/
int write_pic2pic(void *buffer, unsigned int len)
{
    int i;
    if (U2MODEbits.UARTEN == false || U2STAbits.UTXEN == false) {
        return EOF;
    }

    for (i = len; i; --i) {
        while ((U2STAbits.TRMT) == false);
        U2TXREG = *(char*)(buffer)++;
    }

    return len - i;
}

/** Reads data sent from the other PIC into the buffer
    @param buffer the destination buffer
    @param len the number of bytes to write into the buffer

    @note If there's a bug here don't forget to check read_xbee(),
    which has similar code.
*/
int read_pic2pic(void *buffer, unsigned int len)
{
    int i;
    char b;

    if (!is_pic2pic_on()) {
        return EOF;
    }
    else if(_U2RXIE) {
        warn("read_pic2pic: can't poll for data wth an enabled interrupt.\n");
        return 0;
    }
    else if (U2STAbits.OERR) {
        // clear overrun flag to keep receiving. clearing the flag before
        // reading the UART, deletes all data in fifo; this is fine since we
        // want the newest data
        U2STAbits.OERR = false;
        error("read_pic2pic: overrun error.\n");
    }

    b = 0;
    for (i = len; i; i--) {
        if (U2STAbits.FERR) {
            warn("read_pic2pic: frame error.\n");
            break; 
        }

        while ((U2STAbits.URXDA) == false);
        b = U2RXREG;
        *(char *) (buffer++) = b;
    }

    // return number of bytes read
    return len - i;
}

// TODO make sure that all periphs that are not enabled do not get used since
// they're associated data types and functions may be null or undefined.

