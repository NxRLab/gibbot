/* Configure the UART1 module to facilitate wireless communication with the PC
 * through the XBee. Received data from the PC is stored in the linked list 
 * "uart_buffer". 
 * 
 * uart_buffer can be accessed with the clear_queue, enqueue and dequeue
 * functions.
 */
#include <stdio.h>
#include <p33EP512MC806.h>
#include "UART.h"
#include "initializeV6.h"
#include "debug.h"
#include "linkedlist.h"

volatile struct buffer_t uart_buffer;

unsigned char read_UART(void){
    return dequeue();
}

void read_string_UART(unsigned char *data, int n){
    int i = 0,j = 0;
    while(i < n && j != 1){
       data[i] = read_UART();
       if(data[i] == '\n'){
           j = 1;
       }
       else{
           j = 0;
       }
        i++;
    }
    data[i] = '\n';
}

void write_UART(unsigned char data){
    while(U1STAbits.UTXBF);
    U1TXREG = data;
}

void write_UART2(unsigned char data){
    while(U2STAbits.UTXBF);
    U2TXREG = data;
}

void write_string_UART(unsigned char *data, int n){
    int i = 0;
    while(data[i] != '\n' && i < n){
        write_UART(data[i]);
        i++;
    }
    //write_UART('\n');
}

void write_string_UART2(unsigned char *data, int n){
    int i = 0;
    while(data[i] != '\n' && i < n){
        write_UART2(data[i]);
        i++;
    }
    write_UART2('\n');
}

/* Clear every element in the uart_buffer and release the memory */
void clear_queue(void) {
    LinkedList *l;                      //Create temporary pointer

    while (uart_buffer.first != NULL) { //While elements remain in the buffer
        l = uart_buffer.first;          //Point temp ptr to first element
        uart_buffer.first = l->next;    //Change pointer to first element to
                                        //point to the second element
        free(l);                        //Clear the first element
    }
    uart_buffer.last = NULL;            //Clear pointer to last element
    uart_buffer.len = 0;                //Clear tally
}

/* Read value from the first element in the uart_buffer and remove that element
 */
unsigned char dequeue(void){
    unsigned char c = EOF;
    LinkedList *l;                   //Create temporary pointer

    if (uart_buffer.first != NULL) { //If elements remain in the buffer
        l = uart_buffer.first;       //Point temp ptr to first element
        uart_buffer.first = l->next; //Change pointer to first element to
                                     //point to the second element
        c = l->c;                    //Store value from first element
        free(l);                     //Clear the first element
        uart_buffer.len--;           //Decrement tally
    }

    return c;                        //If no elements remain return EOF,
                                     //otherwise return value in element
}

/* Add a new element to the uart_buffer */
void enqueue(unsigned char c) {
    LinkedList *l; //Create temporary pointer to a linked list

    l = (LinkedList *) malloc(sizeof (LinkedList)); //Try to allocate memory
    if (l == NULL) { //If pointer is empty there is no remaining memory
        read_error(); //Remove two entries from error buffer
        read_error();
        log_error(ERR_BUFF_FULL); //Add buffer full entry
        l = (LinkedList *) malloc(sizeof (LinkedList)); //Allocate memory
    }

    // add data
    l->c = c;       //Write data to variable in element

    // link
    l->next = NULL; //clear pointer
    if (uart_buffer.first == NULL) { //If no elements in uart_buffer
        uart_buffer.first = l;      //First and last both point to the only
        uart_buffer.last = l;       //  element
    } else {
        uart_buffer.last->next = l; //Set next ptr of last element to new element
        uart_buffer.last = l;       //Set last ptr to new element
    }
    uart_buffer.len++;              //Increment tally
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    while (U1STAbits.URXDA){ //If there is data in the recieve register
        enqueue(U1RXREG);    //Add data to uart_buffer
    }
    LED2 = !LED2;
    IFS0bits.U1RXIF = 0; //Clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    while (U2STAbits.URXDA){ //If there is data in the recieve register
        enqueue(U2RXREG);    //Add data to uart_buffer
    }
    LED3 = !LED3;
    IFS1bits.U2RXIF = 0; //Clear interrupt flag
}

void initialize_UART(void){
    
    // The UART module allows wireless communication with the computer via XBee
    /* XBee connections to the dsPIC are as follows:
     * RX   RP66/RD2
     * TX   RP65/RD1
     * CTS  RP70/RD6
     * RTS  RP71/RD7
     */

    // Unless issues with XBee communication prove that hardware flow
    // control is necessary, RTS and CTS will not be initialized.
    // Set TX pin as an output
    TRISDbits.TRISD1 = 0; //TX is output
    TRISDbits.TRISD2 = 1; //RX is input
    //Set RP registers for UART1 RX and TX to connect UART module to those pins
    RPINR18bits.U1RXR = 66;  //UART1 RX Tied to RP66 (RD2)
    RPOR0bits.RP65R = 1;     //RP65 (RD1) tied to UART1 TX

    ////Set RP registers for UART1 CTS and RTS
    //RPINR18bits.U1CTSR = 65; //UART1 CTS tied to RP70 (RD6)
    //RPOR3bits.RP71R = 2;     //RP71 tied to UART1 RTS (RD7)

    /* Set Baud Rate of 111,111. The XBee is not able to communicate
     * at the standard 115200 baud rate because of limitations with its internal
     * clock (Source: Footnote on table in "BD (Interface Data Rate) Command"
     * section of Product Manual v1.xEx - 802.15.4 Protocol).  */
    U1MODEbits.BRGH = 1; //Turn High Baud Rate Mode on
    // U1BRG = (Fcy/(4*16*Baud Rate)) - 1
    // U1BRG = (40MHz/(16*111,111)) - 1 = 89
    U1BRG = 89; //Baud Rate =112044 0.8% error

    //UxTX and UxRX pins are enabled and used
    //UxCTS and UxRTS pins are controlled by port latches
    //To use U1CTS and U1RTS pins with module: U1MODEbits.UEN = 0b10;
    U1MODEbits.UEN = 0b00;

    IPC2bits.U1RXIP = 7;     // Set RX interrupt priority to 5
    IFS0bits.U1RXIF = 0;     // Clear the Receive Interrupt Flag
    IEC0bits.U1RXIE = 1;     // Enable Receive Interrupts

    U1MODEbits.UARTEN = 1;   //enable the UART
    U1STAbits.UTXEN = 1;     //Enable transmitting
}

void initialize_UART2(void){
    //UART2 is used for communication between the two dsPICs
    /* UART2 connections to the dsPIC are as follows:
     * RX: RP101/RF5
     * TX: RP100/RF4
     */
    
    TRISFbits.TRISF4 = 0; //TX is output
    TRISFbits.TRISF5 = 1; //RX is input

    RPINR19bits.U2RXR = 101; //UART1 RX tied to RP101 (RF5)
    RPOR9bits.RP100R = 3; //RP100 (RF4) tied to UART2 TX

    U2MODEbits.BRGH = 1; //Turn High Baud Rate Mode On
    U2BRG = 89; //Baud Rate = 112044
    U2MODEbits.UEN = 0b00;

    IPC7bits.U2RXIP = 7; //Set RX interrupt priority to 7
    IFS1bits.U2RXIF = 0; //Clear the Receive Interrupt Flag
    IEC1bits.U2RXIE = 1; //Enable Receive Interrupts

    U2MODEbits.UARTEN = 1; //enable the UART
    U2STAbits.UTXEN = 1; //enable transmitting
}
