#ifndef TIMERS_H
#define TIMERS_H
/// @file

enum TMR32Bit {
TIMER23,
TIMER45,
TIMER67,
TIMER89
};

typedef enum TMR32Bit TMR32Bit;

/// Returns the TxCONbits register, 0 < x < 10
#define TxCONbits(x) T ## x ## CONbits
/// Returns the TxCON register, 0 < x < 10
#define TxCON(x) T ## x ## CON
/// Returns the PRx register, 0 < x < 10
#define PR(x) PR ## x
/// Returns the TMRx register, 0 < x < 10
#define TMR(x) TMR ## x
/// Returns the TxIF bit, 0 < x < 10
#define TxIF(x) _T ## x ## IF

/// Starts a timer for profiling code.
/** 
    @param x The timer to use, 0 < x < 10
    @param  msg A string for identifying the timer
    @param max The maximum duration the timer should run for in milliseconds;
    The value can be a double or long double type.

    #TxTICK and #TxTOCK are used to time code snippets.

    @see #TxTOCK
    @ingroup prof
*/
#define TxTICK(x, msg, max) \
    do { \
        if(strncmp((msg), "", sizeof(""))) { \
            printf("%s: TMR%u Tick (max: %Lg ms)\n", \
                (msg), (x), (long double) (max)); \
        } \
         \
        TxCONbits(x).TON = false; \
        TxIF(1) = false; \
        set_16_bit_timer((max), &TxCON(x), &PR(x), &TMR(x));  \
        TxCONbits(x).TON = true; \
    } while(0)

/// Stops a timer from profiling code and optionally prints a summary.
/** 
    @param x The timer used by #TxTICK, 0 < x < 10
    @param  msg The string passed to #TxTICK for identifying the timer

    #TxTICK and #TxTOCK are used to time code snippets.

    @warning If set, the timer's interrupt flag is \b not cleared.
    @see #TxTICK
    @ingroup prof
*/
#define TxTOCK(x, msg) \
    do { \
        TxCONbits(x).TON = false; \
        if(strncmp((msg), "", sizeof(""))) { \
            unsigned int ps[] = {1, 8, 64, 256}; \
            printf("%s: TMR%u Tock ", (msg), (x)); \
            printf("%Lg ms ", ticks_to_ms(TMR(x), ps[TxCONbits(x).TCKPS])); \
            printf("(%u ticks, overflow? %u)\n", TMR(x), TxIF(x)); \
        } \
    } while(0)

/// @}

extern long double ticks_to_ms(unsigned long int , int);
extern unsigned long int ms_to_ticks(long double, int, bool);
extern void set_16_bit_timer(long double, VUI *, VUI *, VUI *);
extern void set_32_bit_timer(long double, TMR32Bit);


#endif /* TIMERS_H */
