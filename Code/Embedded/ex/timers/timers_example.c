/// @file
#include <boards/pv7.h>
#include <gibbot.h>

#define N_PS 4

void print_ms(long double ms)
{
    int i;
    unsigned int ps;
    unsigned int cnts;
    long double c2ms;
    unsigned int psers[N_PS] = {1, 8, 64, 256};

    for(i = 0; i < N_PS; i++) {
        ps = psers[i];
        cnts = ms_to_ticks(ms, ps); 
        c2ms = ticks_to_ms(cnts, ps);
        printf("prescaler: %u desired: %1.2Lf ms ", ps, ms);
        printf("actual: %1.2Lf ms (%u counts)\n", c2ms, cnts);
    }
}

/// A simple example showing basic timer functionality
int main()
{
    int i;
    long double ms[] = {0.01, 1.0, 18.99, 247, 10000};

    initialize_board(&pv7);

    printf("main: testing ms_to_ticks and ticks_to_ms.\n");
    for(i = 0; i < sizeof(ms)/sizeof(long double); i++) {
        print_ms(ms[i]);
        printf("\n");
    }

    printf("main: setting 16-bit T3 in timer mode for %1.2Lf ms\n", ms[3]);
    printf("registers are originally: ");
    printf("T3CON: %u (T3CONbits.TCKPS = %u) PR3: %u TMR3: %u\n",
        T3CON, T3CONbits.TCKPS, PR3, TMR3);
    set_16_bit_timer(ms[3], &T3CON, &PR3, &TMR3);
    printf("registers are set to: ");
    printf("T3CON: %u (T3CONbits.TCKPS = %u) PR3: %u TMR3: %u\n",
        T3CON, T3CONbits.TCKPS, PR3, TMR3);

    // don't forget to turn the timer on and to set the interrupt register, if
    // necessary.


    printf("Done!\n");
    while(1);

    return 0;
}
