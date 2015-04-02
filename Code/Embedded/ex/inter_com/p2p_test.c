/// @file
#include <boards/pv7.h>
#include <gibbot.h>

/// A simple example showing basic input/output functionality
int main()
{
    initialize_board(&pv7);


    packet c;
    c.cmd = -1;
    c.data = 127;
    printf("packet c is: %d %d %d %d\n", c.cmd, c.handle, c.is_read, c.data);


    // set up loopback interface
    U2MODEbits.LPBACK = 1;

    //printf("testing U2IE interrupt\n");
    //IFS4bits.U2EIF = true; // clear the Receive Interrupt Flag

    // tricky thing about testing function is getting DISICNT to not time out.
    // here we'll setup a timer to keep DISICNT at it's max value so
    // if statements will go through

    T1CONbits.TCKPS = 0;
    PR1 = 0x3000;
    TMR1 = 0;

    set_16_bit_timer(1000, &T1CON, &PR1, &TMR1);

    IPC0bits.T1IP = 7;
    IFS0bits.T1IF = 0;
    //IEC0bits.T1IE = 1;

    //T1CONbits.TON = 1;

    while(1) {
        unsigned char c;
        read_xbee(&c, 1);
        //printf("%c\n", c);
        U2TXREG = c;
    }

    printf("Done!\n");
    while(1);

    return 0;
}

volatile int state = 2;
void GIBINT _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
    if(INTCON2bits.DISI) {
        __builtin_disi(0x3fff);
        LED2 = LED_ON;
    }
    else {
        LED2 = LED_OFF;
    }

    if(!U2STAbits.UTXBF) {
        switch(state) {
            case 0:
                U2TXREG = 0x55;
                state++;
                break;
            case 1:
                U2TXREG = 0x56;
                state++;
                break;
            case 2:
                U2TXREG = 0x57;
                state++;
                break;
            case 3:
                U2TXREG = 0x58;
                state++;
                break;
            case 4:
                U2TXREG = 0xAA;
                state++;
                break;
            case 5:
                U2TXREG = 0xAB;
                state++;
                break;
            default:
                state = 0;
        }
    }
}
