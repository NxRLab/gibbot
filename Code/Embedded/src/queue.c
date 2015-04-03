#include <gibbot.h>

#define CHARS_PER_LINE 12

void init_q(void *buffer, size_t len, RingBuffer *r)
{
    size_t n = floor_power_of_two(len);

    if(r == NULL) {
        printf("init_q: the ring buffer pointer is null.\n");
        return;
    }

    r->mask = n - 1;
    r->read_index = 0;
    r->write_index = 0;
    r->buffer = (unsigned char *) buffer;

    if(buffer == NULL) {
        printf("init_q: the input buffer pointer is null.\n");
        r->mask = 0;
        return;
    }

    if(n != len) {
        // make this a warning
        printf("init_q: %u is not a power of two, ", len);
        printf("using a buffer length of %u instead.\n", n);
    }
}

void print_q(size_t n, RingBuffer *r)
{
    int i;
    int N;

    printf("*********************************************\n");
    if(num_bytes_in_q(r) == 1) {
        printf("there is %u byte in the queue.\n", num_bytes_in_q(r));
    }
    else {
        printf("there are %u bytes in the queue.\n", num_bytes_in_q(r));
    }

    printf("the queue is using %u bytes of the buffer.\n", size_of_q(r));
    printf("it has a capacity of %u bytes.\n", r->mask);
    printf("is the queue empty? %s.\n", is_q_empty(r) ? "yes" : "no");
    printf("is the queue full? %s.\n", is_q_full(r) ? "yes" : "no");
    printf("read index: %u * write index %u * mask %u.\n", 
        r->read_index, r->write_index, r->mask);
    
    if(n) {
        N = size_of_q(r) > n ? n : size_of_q(r);
        printf("the first min(%u, %u) bytes are:\n", size_of_q(r), n);
        for(i = 0; i < N; i++) {
            printf("0x%x ", r->buffer[i]);
            if((i+1) % CHARS_PER_LINE == 0) {
                printf("\n");
            }
        }

        if(i % CHARS_PER_LINE != 0) {
            printf("\n");
        }
    }
    printf("*********************************************\n");
}

size_t size_of_q(RingBuffer *r)
{
    return r->mask + 1;
}

size_t num_bytes_in_q(RingBuffer *r)
{
    return (r->write_index - r->read_index) & r->mask;
}

bool is_q_full(RingBuffer *r)
{
    return num_bytes_in_q(r) == r->mask;
}

bool is_q_empty(RingBuffer *r)
{
    return num_bytes_in_q(r) == 0;
}

bool enq(unsigned char c, RingBuffer *r)
{
    if(is_q_full(r)) {
        return false;
    }

    // modulo write into the buffer
    r->buffer[r->write_index & r->mask] = c;
    r->write_index++;
    return true;
}

bool deq(unsigned char *c, RingBuffer *r)
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
