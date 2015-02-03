#ifndef UART_H
#define	UART_H
#include "linkedlist.h"

void initialize_UART(void);
void clear_queue(void);
unsigned char dequeue(void);
void enqueue(unsigned char c);
unsigned char read_UART(void);
void write_UART(unsigned char data);
void write(unsigned char data);

extern volatile struct buffer_t uart_buffer;

#endif

