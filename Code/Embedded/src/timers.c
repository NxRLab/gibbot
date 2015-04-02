/// @file

#include <gibbot.h>

/// Number of prescaler options available for the timers.
#define N_PS 4

/// Converts timer counts to milliseconds
/**
    @param tcnts The number of timer counts
    @param prescaler The prescaler used
    @return The corresponding time in milliseconds
*/
long double ticks_to_ms(unsigned int tcnts, int prescaler)
{
    long double x = 1000ULL * tcnts * prescaler;
    return x / FCY;
}

/// Converts milliseconds to timer counts
/**
    @param ms The number of milliseconds
    @param prescaler The desired prescaler 
    @return The corresponding time in timer counts

    @warning If \a ms is too large to represent in a 16-bit timer, the value is
    automatically capped at UINT16_MAX.  It is up to the user to determine
    whether UINT16_MAX means ms is too large given the prescaler or if ms maps
    to UINT16_MAX in timer counts.
*/
unsigned int ms_to_ticks(long double ms, int prescaler)
{
    unsigned long x = (unsigned long) (ms * FCY / 1000 / prescaler);

    if(x > UINT16_MAX) {
        x = UINT16_MAX;
    }

    return (unsigned int) x;
}


/**  Sets up TMR1-TMR9 as 16-bit timers in timer mode.
    @param ms the desired period in milliseconds
    @param con Tx's control register TxCONbits
    @param prd Tx's period register PRx
    @param tmr Tx's timer register TMRx

    This function assumes reset conditions for TMRx and sets the timer's SFRs 
    as follows:

    - TxCONbits.TCKPS = ps;
    - PR2 = timer_cnts;
    - TMRx = 0;

    where ps is the smallest prescaler that minimizes the error between desired
    period of time in milliseconds and the actual period in milliseconds,
    timer_cnts is the corresponding value of milliseconds in clock ticks given
    prescaler ps, and the timer is set to count from zero.

    The timer is \b not started and no interrupts are set and must still be 
    done after this function is called.

    It is up to the caller to ensure that the amount of error between desired
    and actual value are acceptable.  If a value of ms is given outside the
    numerical range that the PIC can do, then the timer is set to the maximum
    value possible and \b no \b error is given.

    @warning The timer is \b not activated.  TxCONbits.TON must still be set
    after calling this function.

    @warning No error or warning is given if \b ms is outside the range of what
    the PIC can do.
*/
void set_16_bit_timer(long double ms, VUI *con, VUI *prd, VUI *tmr)
{
    int i, j;
    long double err, min_error;
    unsigned int tcnts[N_PS];
    unsigned int ps[N_PS] = {1, 8, 64, 256};

    // compute the counts given the desired amount of time in ms
    for(i = 0; i < N_PS; i++) {
        tcnts[i] = ms_to_ticks(ms, ps[i]);
    }
    
    // find the prescaler that gives a count closest to the desired value
    j = 0;
    min_error = LDBL_MAX; // max value for unsigned int
    for(i = 0; i < N_PS; i++) {
        err = fabsl(ms - ticks_to_ms(tcnts[i], ps[i]));
        if(err < min_error) {
            min_error = err;
            j = i;
        }
    }

    // set the registers
    *con |= (j << _T1CON_TCKPS_POSITION); // all timers have same TCKPS position
    *prd = tcnts[j];
    *tmr = 0;
}
