/*
typedef struct queue_t queue;

struct queue_t {
    int head;
    int tail;
    int buffer[1024];
};


// UART3 interrupt handler, priority level 2
void __ISR(_UART_3_VECTOR, ipl2) IntUart3Handler(void) {
    // Is this an RX interrupt?
    if (INTGetFlag(INT_SOURCE_UART_RX(UART3))) {
        char data = UARTGetDataByte(UART3);
        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(UART3));
    }

    // We don't care about TX interrupt
    if (INTGetFlag(INT_SOURCE_UART_TX(UART3))) {
        INTClearFlag(INT_SOURCE_UART_TX(UART3));
    }
}
*/