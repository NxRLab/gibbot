#ifndef QUEUE_H
#define	QUEUE_H

/// @file

struct RingBuffer {
    size_t mask;
    size_t read_index;
    size_t write_index;
    unsigned char *buffer;
};

typedef struct RingBuffer RingBuffer;

extern void init_q(void *buffer, size_t len, RingBuffer *r);
extern void print_q(size_t n, RingBuffer *r);
extern size_t size_of_q(RingBuffer *r);
extern size_t num_bytes_in_q(RingBuffer *r);
extern bool is_q_full(RingBuffer *r);
extern bool is_q_empty(RingBuffer *r);
extern bool enq(unsigned char c, RingBuffer *r);
extern bool deq(unsigned char *c, RingBuffer *r);

#endif /* QUEUE_H */
