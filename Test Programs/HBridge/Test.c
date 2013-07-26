#include <p32xxxx.h>
#include <plib.h>

#define SYS_FREQ 80000000        // 80 MHz
#define BAUDRATE 38400

void main(void) {
    TRISDbits.TRISD0 = 0;

    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableSystemMultiVectoredInt();

    // set baudrate to 115,200 bps
    U2MODEbits.BRGH = 0;


    // transmit 8 data bits, no parity bit, and 1 stop bit (a.k.a 8N1 setup)
    U2MODEbits.PDSEL = 0;   //pg 225
    U2MODEbits.STSEL = 0;

    // configure U1TX & U1RX pins as output & input pins
    U2STAbits.UTXEN = 1;    //pg 227
    U2STAbits.URXEN = 1;

    // configure interrutps
    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;  // interrupt whenever a character arrives

    // set priority levels & enable rx interrupt
    IPC8bits.U2IP = 2;  //to use UART 1, do IPC6bits.U1IP=2;
    IPC8bits.U2IS = 0;  //to use UART 1, do IPC6bits.U1IS=0;

    IEC1bits.U2TXIE = 0; //to use UART 1, do IEC0bits.U1TXIE=0;
    IEC1bits.U2RXIE = 1; //to use UART 1, do IEC0bits.U1RXIE=0;

    // finally, turn on the UART
    U2MODEbits.ON = 1;     //in dspic, .UARTEN=1;

    while(1);

}

// UART1 interrupt handler, priority level 2

void __ISR(_UART_2_VECTOR, ipl2) IntUart2Handler(void) {
    // Is this an RX interrupt?
    if (IFS1bits.U2RXIF) {
        char echo = U2RXREG;

        if (echo=='a') //0x61
        {
            LATDbits.LATD0=!LATDbits.LATD0;
        }

        // echo data
        while (U2STAbits.UTXBF); // wait until tx buffer isn't full
        //U2TXREG = echo;

        // Clear the RX interrupt Flag
        IFS1bits.U2RXIF = 0;
    }
}