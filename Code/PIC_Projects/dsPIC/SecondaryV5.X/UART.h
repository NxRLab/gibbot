#ifndef UART_H
#define	UART_H
#include "linkedlist.h"

void initialize_UART2(void);
void clear_queue(void);
unsigned char dequeue(void);
void enqueue(unsigned char c);
unsigned char read_UART(void);
void write_UART2(unsigned char data);
void write(unsigned char data);
unsigned char * readstring_UART(int n);
void UART_task(void);
void writestring_UART2(char *data, int n);

extern volatile struct buffer_t uart_buffer;

#endif

