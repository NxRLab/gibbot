#include <gibbot.h>

/// @file

/// The PIC-to-PIC baud rate
//#define PIC_BAUD (16UL*115200UL)
#define PIC_BAUD (115200UL)
#define RX_PRIORITY 5 // low = 1, high = 7
#define TX_PRIORITY 5 // low = 1, high = 7
#define DMA_RX_IRQ 30
#define DMA_TX_IRQ 31
#define INTERRUPT_EVERY_CHAR 0
#define DMA_BYTE_TRFRS 1
#define DMA_ONE_SHOT 1
#define DMA_WRITE_TO_PERIPH 1
#define DMA4_RX_PRIORITY 5 // low = 1, high = 7
#define DMA5_TX_PRIORITY 5 // low = 1, high = 7

volatile __eds__ GIBDMA OtherPICsData rx_data, tx_data;
volatile OtherPICsData other_boards_data;

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

void enable_dma4_on_rx()
{
    // UART interrupt settings
    U2MODEbits.UARTEN = false;
    U2STAbits.URXISEL = INTERRUPT_EVERY_CHAR;

    // set up DMA for RX
    DMA4CONbits.SIZE = DMA_BYTE_TRFRS;
    DMA4CONbits.MODE = DMA_ONE_SHOT;
    DMA4REQbits.IRQSEL = DMA_RX_IRQ; 
    DMA4PAD = (VUI) &U2RXREG;
    DMA4STAL = __builtin_dmaoffset(&rx_data);
    DMA4CNT = sizeof(rx_data) - 1;

    _DMA4IP = DMA4_RX_PRIORITY;
    _DMA4IF = false;
    _DMA4IE = true;

    // enable the peripherals
    DMA4CONbits.CHEN = true;
    U2MODEbits.UARTEN = true;
    U2STAbits.UTXEN = true;
}

// took 0.975 us --- given baud rate 2 32-bit numbers would take 34.72 us
void GIBINT _DMA4Interrupt(void)
{
    _DMA4IF = false;

    // transfer data to buffered output
    other_boards_data = rx_data;

    // start DMA4 again
    DMA4STAL = __builtin_dmaoffset(&rx_data);
    DMA4CONbits.CHEN = true;
}

void enable_dma5_on_tx()
{
    // set up initial transfer
    tx_data.magnet_enc = my_magnet_enc.read();
    tx_data.motor_enc = my_motor_enc.read();

    // set TX to interrupt after every byte
    U2MODEbits.UARTEN = false;
    U2STAbits.UTXISEL0 = INTERRUPT_EVERY_CHAR;
    U2STAbits.UTXISEL1 = INTERRUPT_EVERY_CHAR;

    // set up DMA for TX
    DMA5CONbits.SIZE = DMA_BYTE_TRFRS;
    DMA5CONbits.MODE = DMA_ONE_SHOT;
    DMA5CONbits.DIR = DMA_WRITE_TO_PERIPH;
    DMA5REQbits.IRQSEL = DMA_TX_IRQ; 
    DMA5PAD = (VUI) &U2TXREG;
    DMA5STAL = __builtin_dmaoffset(&tx_data);
    DMA5CNT = sizeof(tx_data) - 1;

    // set up DMA5 interrupt
    _DMA5IP = DMA5_TX_PRIORITY;
    _DMA5IF = false;
    _DMA5IE = true;

    // enable the peripheral
    DMA5CONbits.CHEN = true;
    U2MODEbits.UARTEN = true;
    U2STAbits.UTXEN = true;
}

// interrupt took  2.35 us to run
void GIBINT _DMA5Interrupt(void)
{
    _DMA5IF = false;

    tx_data.magnet_enc = my_magnet_enc.read();
    tx_data.motor_enc = my_motor_enc.read();

    DMA5STAL = __builtin_dmaoffset(&tx_data);
    DMA5CONbits.CHEN = true;
    DMA5REQbits.FORCE = true;
}


// TODO make sure that all periphs that are not enabled do not get used since
// they're associated data types and functions may be null or undefined.

