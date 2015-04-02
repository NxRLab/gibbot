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

static inline size_t size_of_q(RingBuffer *r)
{
    return r->mask + 1;
}

static inline size_t num_bytes_in_q(RingBuffer *r)
{
    return (r->write_index - r->read_index) & r->mask;
}

static inline bool is_q_full(RingBuffer *r)
{
    return num_bytes_in_q(r) == r->mask;
}

static inline bool is_q_empty(RingBuffer *r)
{
    return num_bytes_in_q(r) == 0;
}

static inline bool enq(unsigned char c, RingBuffer *r)
{
    if(is_q_full(r)) {
        return false;
    }

    // modulo write into the buffer
    r->buffer[r->write_index & r->mask] = c;
    r->write_index++;
    return true;
}

static inline bool deq(unsigned char *c, RingBuffer *r)
{
    if(c == NULL) {
        printf("deq: destination buffer is null.\n");
        return false;
    }
    else if(is_q_empty(r)) {
        return false;
    }

    // modulo read from the buffer
    *c = r->buffer[r->read_index & r->mask];
    r->read_index++;
    return true;
}

extern void init_q(void *buffer, size_t len, RingBuffer *r);
extern void print_q(size_t n, RingBuffer *r);

#endif /* QUEUE_H */
