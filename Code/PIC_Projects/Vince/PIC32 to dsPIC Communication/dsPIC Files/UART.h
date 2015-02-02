#ifndef UART_H
#define	UART_H
#include "linkedlist.h"

void initialize_UART2(void);
void clear_queue(void);
unsigned char dequeue(void);
void enqueue(unsigned char c);
unsigned char read_UART2(void);
void write_UART2(unsigned char data);
void write(unsigned char data);
void read_string_UART2(int n);
void UART2_task(void);
void write_string_UART2(unsigned char *data, int n);

extern volatile struct buffer_t uart_buffer;

#endif

