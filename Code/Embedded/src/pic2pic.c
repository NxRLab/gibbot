#include <gibbot.h>

/// @file

/// The PIC-to-PIC baud rate
#define PIC_BAUD 115200UL

#define RXE_PRIORITY 5 // low = 1, high = 7

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

    _U2RXIP = RXE_PRIORITY - 1;
    _U2RXIF = false;
    _U2RXIE = true;
    
    /*
    IPC16bits.U2EIP = RXE_PRIORITY; // set RX error interrupt priority
    IFS4bits.U2EIF = false; // clear the Receive Interrupt Flag
    IEC4bits.U2EIE = true; // enable RX error interrupts
    */

    U2MODEbits.UARTEN = true; // enable the UART
    U2STAbits.UTXEN = true; // enable transmitting
}

int pic2pic_write(void *buffer, unsigned int len)
{
    // disable FERR int

    // transmit break
    // package
    // transmit break
    // wait for ack
    // next step or retransmit

    // wait for break
    // package
    // wait for break
    // send ack

    // enable FERR int
    return EOF;
}

int pic2pic_read(void *buffer, unsigned int len)
{
    // must give prio = 6 for desi == 0 to be valid 
    // i.e., pic2pic_write might have reset desi.

    // disable FERR int

    // wait for break
    // package
    // wait for break
    // send ack

    // proc command: read or write data
    //assert(desi > 0);

    // transmit break
    // package
    // transmit break
    // wait for ack
    // next step or retransmit

    // enable FERR int
    return EOF;
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
    // char *b = (char *) buffer;

    // read buffer

    return 0;
}

//#define SOT 0 // start of transmission byte
#define MAX_DISI 0x3fff // max permissible time to disable interrupt
#define BUF_LEN 256
#if 0
void read_protocol()
{
    packet c;
    // when this is working make rb and buf global and just reset read and write
    RingBuffer rb;
    unsigned char buf[BUF_LEN];

    init_q(buf, BUF_LEN, &rb);
    // is it a legit new frame?
    c.data = U2RXREG;
    if(c.data == SOT) {
        printB("legit new frame %d\n", DISICNT);
        // a new frame is being sent
        while (!U2STAbits.URXDA && DISICNT);
        c.cmd = DISICNT ? U2RXREG : NUM_HANDLES;
        printB("is it a legit handle? %d (cmd = %d) %d\n", c.handle, c.cmd,
            DISICNT);
        // does the command have a valid handle?
        if(c.handle < NUM_HANDLES) {
            printB("legit handle %d\n", DISICNT);
            // handle is valid; store data until the end of frame
            while (!U2STAbits.FERR && DISICNT) {
                while (!U2STAbits.URXDA && DISICNT);
                if(DISICNT) {
                    c.data = U2RXREG;
                    enq(c.data, &rb);
                    printB("data: %d %d\n", c.data, DISICNT);
                }
            }
            printB("exiting %d %d\n", U2STAbits.FERR, DISICNT);

            if(DISICNT) {
                // check the crc and ack frame
            }
        }
    }

    while(1) {
        while (!U2STAbits.URXDA);
        c.data = U2RXREG;
        printf("reg: %d ferr: %d\n", c.data, U2STAbits.FERR);
    }
}
#endif

void GIBINT _U2ErrInterrupt(void)
{
    unsigned char c;

    // we need to ensure that an entire frame is always received
    // without any race conditions, so monopolize UART

    /*
    while (U2STAbits.URXDA) {
        c = U2RXREG;
        printf("reg: %d ferr: %d\n", c, U2STAbits.FERR);
    }

    if (U2STAbits.OERR) {
        // the fifo buffer was full, clear the flag.
        U2STAbits.OERR = false;
        printR("_U2RXInterrupt: overrun error.\n");
    }
    */

    _U2EIF = false;
    return;


    // disable interrupts and start timer
    __builtin_disi(MAX_DISI);

    info("_U2RXInterrupt: in the interrupt.\n");
    // we only care about bytes with FERRs
    while (U2STAbits.URXDA && !U2STAbits.FERR) {
        c = U2RXREG;
    }

    if (U2STAbits.URXDA && U2STAbits.FERR) {
        error("_U2RXInterrupt: frame error.\n");
        // get info
        //read_protocol();

        // do some processing

        // and now send info back
    }

    if (U2STAbits.PERR) {
        // data is corrupt
        error("_U2RXInterrupt: parity error.\n");
    }

    if (U2STAbits.OERR) {
        // the fifo buffer was full, clear the flag.
        U2STAbits.OERR = false;
        error("_U2RXInterrupt: overrun error.\n");
    }

    // log how long it took to run

    // reenable interrupts and clear interrupt flag
    __builtin_disi(0);
    _U2EIF = false;
}

/// The inter-PIC UART interrupt
// FERR corresponds to the current character in U2RXREG

#define SOT 'a'
#define OCCURANCES 2
volatile int sot = 0, eot, pkt;
volatile unsigned char p;
void GIBINT _U2RXInterrupt(void)
{
    unsigned char c = U2RXREG;
    printf("%c \t \t p: %c sot: %d pkt: %d eot: %d \t", c, p, sot, pkt, eot);

    if(pkt) {
        printf("saving packets");
    }
    
    if(c == SOT && p == SOT) {
        sot++;
    }
    else {
        sot = 0;
    }

    p = c;

    if(sot == OCCURANCES) {
        sot = 0;
        p = 0;
        pkt = !pkt;
        if(pkt)
            printf("\nstart transmission");
        else
            printf("\nend transmission");
    }

    printf("\n");

    _U2RXIF = false;
    return;
}
