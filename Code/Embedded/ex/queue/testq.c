/// @file
#include <boards/pv7.h>
#include <gibbot.h>

#define SMALL_LEN 12
#define MED_LEN 100
#define MAX_LEN 1024
char buf[MAX_LEN];

/// A simple example showing basic queue functionality
int main()
{
    int i;
    unsigned char c;
    RingBuffer rb;

    initialize_board(&pv7);


    printf("main: initializing the queue.\n");
    printf("main: allocating new ring buffer with %u bytes.\n", MED_LEN);
    printf("main: is it a power of two? %s.\n", 
        floor_power_of_two(MED_LEN) == MED_LEN ? "yes" : "no");
    printf("main: there should be no error message, if it's a power of two.\n");
    init_q(buf, MED_LEN, &rb);
    printf("\n");

    printf("main: testing print_q; it should print %u bytes from buffer.\n", 
        SMALL_LEN);
    print_q(SMALL_LEN, &rb);
    printf("\n");

    printf("main: requesting %u bytes, but it should print %u.\n", 
        MED_LEN, size_of_q(&rb));
    print_q(MED_LEN, &rb);
    printf("\n");

    printf("main: writing to the queue.\n");
    enq('1', &rb);
    print_q(SMALL_LEN, &rb);
    printf("\n");

    i = '1';
    while(enq(++i, &rb));
    print_q(SMALL_LEN, &rb);
    printf("\n");

    printf("main: reading from the queue.\n");
    for(i = 0; i < SMALL_LEN && deq(&c, &rb); i++);
    print_q(SMALL_LEN, &rb);
    printf("\n");

    printf("main: reading from the queue with NULL ptr.\n");
    for(i = 0; i < SMALL_LEN && deq(NULL, &rb); i++);
    print_q(SMALL_LEN, &rb);
    printf("\n");

    printf("main: queue state should not change after read with NULL ptr.\n");
    while(deq(&c, &rb));
    print_q(0, &rb);
    printf("\n");

    printf("main: allocating new ring buffer with %u bytes.\n", MAX_LEN);
    printf("main: is it a power of two? %s.\n", 
        floor_power_of_two(MAX_LEN) == MAX_LEN ? "yes" : "no");
    printf("main: there should be no error message, if it's a power of two.\n");
    init_q(buf, MAX_LEN, &rb);
    printf("\n");

    printf("main: testing edge cases of write and read indices.\n");
    printf("main: read_index > write_index.\n");
    rb.read_index = -3; // @ index len - 3
    rb.write_index = 32; // @ index 32
    print_q(0, &rb);
    printf("\n");

    printf("main: write_index about to rollover.\n");
    rb.read_index = -3; // @ index len - 3
    rb.write_index = -1; // @ index len - 1
    print_q(0, &rb);
    printf("\n");

    enq('a', &rb);
    print_q(0, &rb);
    printf("\n");

    printf("main: queue full tests at size_t limits.\n");
    rb.read_index = 0; // @ index len - 3
    rb.write_index = -1; // @ index len - 1
    print_q(0, &rb);
    printf("\n");

    rb.read_index = -1; // @ index len - 3
    rb.write_index = -2; // @ index len - 1
    print_q(0, &rb);
    printf("\n");

    printf("Done!\n");
    while(1);

    return 0;
}
