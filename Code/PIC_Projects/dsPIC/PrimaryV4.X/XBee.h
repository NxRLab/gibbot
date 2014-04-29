#ifndef XBEE_H
#define	XBEE_H

void initialize_UART(void);
void clear_queue(void);
char dequeue(void);
void enqueue(unsigned char c);

#endif	/* XBEE_H */

