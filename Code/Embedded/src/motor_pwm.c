/// Gives the commutation functions for driving the BLDC motor.
/** @file 
 * The commutate function uses the High, Low and Float functions to commutate
 * the motor. The input to the function is the motor state from the hall effect 
 * sensors. Depending on the value of the global variable "direction" the
 * function sets the motor outputs according to the motor's commutation pattern.
 * The commutation pattern is derived from the commutation diagram found on p32
 * of Maxon's E-Paper Catalog and is shown below.
 *
 * Hall Sen 321 | 101 | 001 | 011 | 010 | 110 | 100 |
 * -------------|-----|-----|-----|-----|-----|-----|
 *     State    |  5  |  1  |  3  |  2  |  6  |  4  |
 * 1 -   Red    |  +  |  +  |  0  |  -  |  -  |  0  |
 * 2 -  Black   |  -  |  0  |  +  |  +  |  0  |  -  |
 * 3 -  White   |  0  |  -  |  -  |  0  |  +  |  +  |
 *
 * An input of 0 to the commutate function will turn off the motor.
 * The PWM module runs at #PWM_FREQ_50_KHZ in
 * complementary mode to work with the HIP4086 BLDC driver.
 * In complementary mode each of the three PWM modules controls two outputs
 * whose states are the inverse of each other.
 * The module incorporates a dead time delay between the falling edge of one
 * signal and the rising edge of the next to prevent shoot through.
 */

#include <gibbot.h>

#define N_PS 7
#define PWM_FREQ_50_KHZ 50

/**
    Master Duty Cycle (all generators use one duty cycle)
    Independent Time Based Mode (prereq for center alignment)
    Center-aligned mode (PWM is center aligned, not edge aligned)

    supposedly CAM is more efficient way of switching for BLDC motors.
*/
#define SET_MDCS_ITB_CAM_BITS 0x0304
#define SET_MDCS_ITB_EAM_BITS 0x0300

/// PWM IOCONx settings for bits not part of the override bits IOCONx<9:6>
/**
    This macro affects all bits in the IOCONx register except for the override
    enable bits OVRENH and OVRENL and the override data bits OVRDAT1 and
    OVRDAT0.  The assumption is that all other bits never change.
    
    These other bits are set so that they 

    - enable PWM on output pins tied to PWMxH & PWMxL 
    - sets the polarity of PWMxH (POLH) to active low (i.e., ON = 0)
    - all other registers are at their default states.

    In particular, complementary output mode is a default setting at startup.
    
    @note The PWMxH pin is set to active low to satisfy the input requirement
    for the HIP4086 BLDC H-bridge driver.  The H-bridge is also the reason PWMxH
    and PWMxL need to be in complementary mode.
*/
#define PWMIO_MODE 0xE000

/// Override PWMxH and PWMxL pins IOCONx<9:8>
#define OVREN_HI_AND_LO 0x0300 
/// Set PWMxH = 1 and PWMxL = 0 IOCONx<7:6>
#define OVRDAT_HI_0_LO_1 0x0040 
/// Set PWMxH = 0 and PWMxL = 0 IOCONx<7:6> 
#define OVRDAT_HI_0_LO_0 0x0000 

/// Used to set IOCONx so that the associated pins see the PWM signal
#define PWM_PINS PWMIO_MODE
/// Used to set IOCONx so that the associated pins are tied to ground
#define GND_PINS (PWMIO_MODE + OVREN_HI_AND_LO + OVRDAT_HI_0_LO_1)
/// Used to set IOCONx so that the associated pins are floating
#define FLT_PINS (PWMIO_MODE + OVREN_HI_AND_LO + OVRDAT_HI_0_LO_0)

void (*commutate_cw[COMMUTATION_STATES])(void) = 
    {float_pins, cw1, cw2, cw3, cw4, cw5, cw6, float_pins};

void (*commutate_ccw[COMMUTATION_STATES])(void) = 
    {float_pins, ccw1, ccw2, ccw3, ccw4, ccw5, ccw6, float_pins};

bool is_motor_pwm_on()
{
    return PTCONbits.PTEN;
}

bool is_motor_floating()
{
    return (IOCON1 == FLT_PINS) && (IOCON2 == FLT_PINS) && (IOCON3 == FLT_PINS);
}

long double pwm_ticks_to_ms(unsigned int pwmcnts, int prescaler, bool centered)
{
    long double x = 1000ULL * pwmcnts * prescaler / 2;

    if(centered) {
        x *= 2;
    }

    return x / FCY;
}

unsigned int ms_to_pwm_ticks(long double ms, int prescaler, bool centered)
{
    unsigned long x = (unsigned long) (ms * 2 * FCY / 1000 / prescaler);

    if(centered) {
        x /= 2;
    }

    if(x > UINT16_MAX) {
        x = UINT16_MAX;
    }

    return (unsigned int) x;
}

long double dead_time_ticks_to_ms(unsigned int cnts, int prescaler)
{
    long double x = 1000ULL * cnts * prescaler / 2;

    return x / FCY;
}

unsigned int ms_to_dead_time_ticks(long double ms, int prescaler)
{
    unsigned long x = (unsigned long) (ms * 2 * FCY / 1000 / prescaler);

    if(x > UINT16_MAX) {
        x = UINT16_MAX;
    }

    return (unsigned int) x;
}

// maximize counts
void set_pwm_ticks(long double ms, VUI *con2, VUI *prd, VUI *dc, bool centered)
{
    int i, j;
    long double err, min_error;
    unsigned int tcnts[N_PS];
    unsigned int ps[N_PS] = {1, 2, 4, 8, 16, 32, 64};

    // compute the counts given the desired amount of time in ms
    for(i = 0; i < N_PS; i++) {
        tcnts[i] = ms_to_pwm_ticks(ms, ps[i], centered);
    }
    
    // find the prescaler that gives a count closest to the desired value
    j = 0;
    min_error = LDBL_MAX; // max value for unsigned int
    for(i = 0; i < N_PS; i++) {
        err = fabsl(ms - pwm_ticks_to_ms(tcnts[i], ps[i], centered));
        if(err < min_error) {
            min_error = err;
            j = i;
        }
    }

    // set the registers
    *con2 = j; // prescaler
    *prd = tcnts[j]; // period
    *dc = 0; // start value
}

#define DEAD_TIME_HALF_US (5.0L/10000)

/// Initializes the motor PWM module
/**
    The three pair of PWM generators of PWMxH and PWMxL (x = 1, 2, 3) are
    configured as 

        - Complementary PWM Mode 
        – Master Duty Cycle and Independent Phase, 
        - Fixed Primary Period
        - Edge-Aligned

    This is according to Fig. 14-17 of PWM FRM.
*/
void init_motor_pwm(void)
{
    unsigned int mdcs_and_alignment = SET_MDCS_ITB_CAM_BITS;
    bool centered = mdcs_and_alignment & _PWMCON1_CAM_MASK;

    // set PWM generators to same period 
    set_pwm_ticks(1.0L/PWM_FREQ_50_KHZ, &PTCON2, &PHASE1, &MDC, centered);
    PHASE3 = PHASE2 = PHASE1;

    // set PWM generators to use MDC (also sets alignment mode)
    PWMCON3 = PWMCON2 = PWMCON1 = mdcs_and_alignment;

    // set dead time of 0.5us
    if(!centered) {
        // only ALTDTRx sets dead time for center-aligned PWM
        DTR1 = DTR2 = DTR3 = 
            ms_to_dead_time_ticks(DEAD_TIME_HALF_US, (1 << PTCON2));
    }

    //DTR = Fosc * Deadtime / Prescaler
    //DTR = 80MHz * 0.5us / 4
    ALTDTR1 = ALTDTR2 = ALTDTR3 = 
        ms_to_dead_time_ticks(DEAD_TIME_HALF_US, (1 << PTCON2));

    // set PWM generator pins' I/O parameters
    IOCON1 = PWMIO_MODE;
    IOCON2 = PWMIO_MODE;
    IOCON3 = PWMIO_MODE;

    // set all outputs to float
    float_pins();

    // enable module
    PTCONbits.PTEN = 1;
}

void float_pins() 
            { IOCON1 = FLT_PINS;  IOCON2 = FLT_PINS;  IOCON3 = FLT_PINS; }

void cw1()  { IOCON2 = FLT_PINS;  IOCON1 = GND_PINS;  IOCON3 = PWM_PINS; }
void cw2()  { IOCON3 = FLT_PINS;  IOCON2 = GND_PINS;  IOCON1 = PWM_PINS; }
void cw3()  { IOCON1 = FLT_PINS;  IOCON2 = GND_PINS;  IOCON3 = PWM_PINS; }
void cw4()  { IOCON1 = FLT_PINS;  IOCON3 = GND_PINS;  IOCON2 = PWM_PINS; }
void cw5()  { IOCON3 = FLT_PINS;  IOCON1 = GND_PINS;  IOCON2 = PWM_PINS; }
void cw6()  { IOCON2 = FLT_PINS;  IOCON3 = GND_PINS;  IOCON1 = PWM_PINS; }

void ccw1() { IOCON2 = FLT_PINS;  IOCON3 = GND_PINS;  IOCON1 = PWM_PINS; }
void ccw2() { IOCON3 = FLT_PINS;  IOCON1 = GND_PINS;  IOCON2 = PWM_PINS; }
void ccw3() { IOCON1 = FLT_PINS;  IOCON3 = GND_PINS;  IOCON2 = PWM_PINS; }
void ccw4() { IOCON1 = FLT_PINS;  IOCON2 = GND_PINS;  IOCON3 = PWM_PINS; }
void ccw5() { IOCON3 = FLT_PINS;  IOCON2 = GND_PINS;  IOCON1 = PWM_PINS; }
void ccw6() { IOCON2 = FLT_PINS;  IOCON1 = GND_PINS;  IOCON3 = PWM_PINS; }

/// @TODO can motor encoder be used as a absolute endcoder?  Every 42 +'ve or -'ve
/// interrupts is 1 rev.  We may only need to calibrate once and then write to NV
/// ram.
