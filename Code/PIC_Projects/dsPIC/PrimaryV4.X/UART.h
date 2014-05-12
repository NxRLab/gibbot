#ifndef UART_H
#define	UART_H

#define N 256

void initialize_UART(void);
void clear_queue(void);
unsigned char dequeue(void);
void enqueue(unsigned char c);
unsigned char read_UART(void);
void write_UART(unsigned char data);


struct linked_list_t {
    unsigned char c;            //Variable stored in linked list
    struct linked_list_t *next; //Pointer to next element in linked list
};

typedef struct linked_list_t LinkedList; //Shorten declaration of a new struct
                                         //to the syntax LinkedList name

struct uart_buffer_t { //Create uart_buffer
    LinkedList *first; //Pointer to first element in buffer
    LinkedList *last;  //Pointer to last element in buffer
    int len;           //Tally of elements in buffer
};

extern volatile struct uart_buffer_t uart_buffer;

#endif	/* XBEE_H */

