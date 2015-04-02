/// Takes current readings from ADC1/DMA3 and stores them in a DMA buffer. 
/** @file
    The current ADC module samples data from the following active input pins

    - AN7

    using ADC1 and DMA3 with the following settings:

    - TAD = [150 ns](@ref TAD_150NS) derived from [system clock](@ref FCY)
    - sample period of [12 TAD](@ref SAMP_12_TAD)
    - automatic sample and convert
    - 12-bit conversion
    - CH0 scans active pins in AD1CSSL
    - samples written in [Q1.15](@ref ADC_Q15) format for use with DSP library
    - DMA transfers into two alternating DPSRAM buffers (#cur_buf_a, #cur_buf_b)
    - DMA interrupts after a buffer is full (every #DMA_TRFRS samples)

    If multiple pins are scanned by the ADC peripheral, the samples are written
    into the DMA buffers in the order they were scanned in.
*/

#include <gibbot.h>

/// Resolution of ADC in 12-bit mode in Amps per ADC count.
#define AMPS_PER_COUNT ((unsigned int)(3300.0L/4096.0L))

/// ADC FORM value for Q1.15 output after sample is converted
#define ADC_Q15 3 
/// ADC SSRC value for using the internal clock
#define INTERNAL_CLOCK 7
/// ADC SSRCG value for selecting the proper group for SSRC
#define CLOCK_SOURCE_GROUP 0
/// Samples ADC pin for 12 * TAD ns
#define SAMP_12_TAD 12 
/// Sets ADC conversion time to 150 ns
#define TAD_150NS 150 
/// Family Data sheet quoted minimum ADC clock period (i.e., TAD)
#define MIN_TAD 117.5L 
/// Family Data sheet quoted minimum ADC sample time multiplier
#define MIN_SAMP 3 

/// IRQ value to tie a DMA channel to ADC1
#define ADC_IRQ 13 
/// Set DMA to continuously switch between 2 buffers
#define SWITCH_BTW_2_BUFS 2 
/// AMODE value for DMA post-increment addressing
#define DMA_INCREMENTS_ADDR 0 
/// The total number of DMA transfers
#define DMA_TRFRS (ADC_SAMPS*ADC_PINS) 

/// The current's DMA channel interrupt priority level
/** @ingroup ints
*/
#define DMA3_PRIORITY 5

/// Attribute for defining variables in DPSRAM space
#define GIBDMA __attribute__((eds, space(dma)))

/// Keeps track of which buffer has new data each DMA interrupt
static volatile bool use_buf_a = true;

/// DMA3's "A" buffer
GIBDMA fractional cur_buf_a[ADC_PINS][ADC_SAMPS];

/// DMA3's "B" buffer
GIBDMA fractional cur_buf_b[ADC_PINS][ADC_SAMPS];

volatile Current my_boards_current;

/**
    The filter array for the current samples.  It is #ADC_SAMPS long and is
    always applied at every _DMA3Interrupt().  At startup, the filter is an
    averaging filter.  The default value for each element in the array is
    1/#ADC_SAMPS.  To change the default value, call set_cur_filter_coeffs()
    with an #ADC_LEN element array of desired coefficients.

    @see set_cur_filter_coeffs()
    @warning The initializer used for this variable is gcc specific.  It may not
    be portable to other compilers. 
*/
fractional cur_filter[ADC_SAMPS] = 
    {[0 ... (ADC_SAMPS - 1)] = Q15(1.0/ADC_SAMPS)};

/// Length of exponential moving average filter
#define EMA_LEN 2
/// coefficient of exponential moving average filter must be in the range [0, 1]
#define EMA_ALPHA 0.5
/// Coefficients for the exponential moving average based on #EMA_ALPHA
fractional offset_ema_filter[EMA_LEN] = {Q15(EMA_ALPHA), Q15(1.0 - EMA_ALPHA)};

bool is_cur_on()
{
    return AD1CON1bits.ADON && DMA3CONbits.CHEN;
}

/** 
    @param ns the desired period for TAD in nanoseconds.
    @see cur_clock_period_in_ns()

    This function is intended to be used to set ADxCON3bits.ADCS to the right
    value in counts for the desired period in nanoseconds.  The formula is
    derived from ADC FRM Section 16, p. 11.  It is referred to as TAD in the
    FMR.
*/
unsigned int cur_clock_period_in_cnts(long double ns)
{
    return (unsigned int) (ns * FCY / SEC_TO_NS) - 1;
}

/** 
    @see cur_clock_period_in_cnts()

    The formula is derived from ADC FRM Section 16, p. 11.  It is referred to as
    TAD in the FMR.
*/
long double cur_clock_period_in_ns()
{ 
    return (AD1CON3bits.ADCS + 1) * SEC_TO_NS / FCY;
}

long double cur_sampling_time_in_ns()
{
    return  AD1CON3bits.SAMC * cur_clock_period_in_ns();
}

long double cur_12bit_conversion_time_in_ns()
{
    return cur_sampling_time_in_ns() + 14 * cur_clock_period_in_ns();
}

/**
    @param arr an array of #ADC_SAMPS entires or NULL if an averaging filter is
    fine.

    @note The values of arr will be truncated to a Q15 fixed point number.  This
    may lead to loss of precision of the filter coefficients.  If this is a
    concern then the user should only store values that can be represented by a
    Q15 number.  Useful functions provided by Microchip's DSP library in dsp.h
    are Fract2Float and Float2Fract, which takes in a 32-bit \c float / \c
    double (by default they're the same in xc16 v1.24) or a \c fractional type
    depending on which way the conversion is being done.

    @warning The results of applying the new filter may not appear immediately.
    It may take a few DMA transfers to see correct operation.  It is up to the
    user to determine when this has occurred.  A simple solution is to call one
    of Microchip's __delay functions after calling this function.  This should
    not be necessary though.
*/
void set_cur_filter_coeffs(double *arr) 
{ 
    int i; 
    double c;

    c = 1.0 / ADC_SAMPS;
    for(i = 0; i < ADC_SAMPS; i++) {
        c = (arr == NULL) ? c : arr[i];
        cur_filter[i] = Float2Fract(c);
    }
}

/**
    @param alpha The EMA coefficient, 0 <= alpha <= 1.
    An exponential moving average is applied to the offset in #Current.offset
    whenever the motor pins are floating.  The equation is defined recursively:

        EMA(i) = alpha * x + (1-alpha) * EMA(i-1).

    The weighting coefficient alpha is by default #EMA_ALPHA at startup.

    @warning values exceeding the range for alpha are clamped at 0 or 1,
    whichever number is closest.
*/
void set_offset_ema_filter_alpha(double alpha) 
{ 
    if(alpha < 0) {
        alpha = 0;
    }
    else if(alpha > 1) {
        alpha = 1;
    }

    offset_ema_filter[0] = Float2Fract(alpha);
    offset_ema_filter[1] = Float2Fract(1.0 - alpha);
}

/// @TODO convert all double to long double if fast enough

/** 
    @see current.c Detailed Description for more details.
    @warning This initialization function assumes PIC restart conditions
*/
void init_cur(double mV_per_A)
{
    long double tad;

    // save the sensor's resolution (mV / A = V / mA)
    my_boards_current.q15_to_mA = CURRENT_ZERO_VREF / mV_per_A;

    // ADC mode -- use system clock (running at FCY) as clock source for TAD
    // with samples in Q1.15 format
    AD1CON1bits.ASAM = true;
    AD1CON1bits.AD12B = true;
    AD1CON1bits.FORM = ADC_Q15;
    AD1CON1bits.SSRCG = CLOCK_SOURCE_GROUP;
    AD1CON1bits.SSRC = INTERNAL_CLOCK;

    // ADC sampling -- automatic sample and convert
    AD1CON3bits.ADCS = cur_clock_period_in_cnts(TAD_150NS);
    AD1CON3bits.SAMC = SAMP_12_TAD;

    // pins scanned
    AD1CON2bits.CSCNA = true;
    // assumes pins to scan (AD1CSSL) have been set by board

    // ADC DMA settings
    AD1CON4bits.ADDMAEN = true;
    // DMA FRM (p. 22-35, Example 22-5) claims other ADC specific DMA options
    // are ignored by the DMA controller when DMAxCONbits.MODE != PIA


    // DMA set up -- DMA3 will use ADC as source peripherial
    DMA3REQbits.IRQSEL = ADC_IRQ;
    DMA3PAD = (volatile unsigned int) &ADC1BUF0;

    // DMA determines where in memory to place data
    DMA3CONbits.AMODE = DMA_INCREMENTS_ADDR;

    // DMA alternates writes between two buffers
    DMA3CONbits.MODE = SWITCH_BTW_2_BUFS;
    DMA3STAL = __builtin_dmaoffset(cur_buf_a);
    DMA3STBL = __builtin_dmaoffset(cur_buf_b);
    DMA3CNT = DMA_TRFRS - 1; // this is a 14-bit register

    // enable interrupts
    _DMA3IP = DMA3_PRIORITY;
    _DMA3IF = false;
    _DMA3IE = true;

    // everything is set up start sampling
    DMA3CONbits.CHEN = true;
    AD1CON1bits.ADON = true;

    // delay for a bit so ADC can stabilize; found in all ADC FRM sample code
    __delay_us(20);

    // print warnings if conversion or sampling times are too short
    tad = cur_clock_period_in_ns(); 
    if(tad < MIN_TAD) {
        warn("init_cur: the conversion time is %Lf\n", tad);
        warn("init_cur: the minimum conversion time (TAD) is %Lf\n", MIN_TAD);
        warn("init_cur: expect erratic ADC behaviour.\n");
    }

    if(AD1CON3bits.SAMC < MIN_SAMP) {
        warn("init_cur: the sampling multiplier is %u.\n", AD1CON3bits.SAMC);
        warn("init_cur: the minimum multiplier allowed is %u\n", MIN_SAMP);
        warn("init_cur: expect erratic ADC behaviour.\n");
    }
}

/// Current DMA interrupt.
/**
    This interrupt services the ADC1/DMA3 current samples.  The interrupt must
    execute faster than the ADC and DMA channel can produce and transfer
    #DMA_TRFRS samples into a DMA buffer.  A good upper-bound is
    cur_12bit_conversion_time_in_ns().  If the ADC clock period is #TAD_150NS
    and the sampling time is #SAMP_12_TAD, then #DMA_TRFRS would take 16 * 150 *
    (12 + 14) = 62.4 us.  There is some overhead due to the DMA transfer, but
    it's safe to stay under this limit.  When the interrupt was timed last using
    #TxTICK and #TxTOCK, it was executing in under 20 us (when branch is taken). 

    @warning this function assumes that there is only one pin being sampled for
    current.  If multiple pins are ever sampled, this function @b must be
    updated.

    @ingroup ints
*/
void GIBINT _DMA3Interrupt(void)
{
    fractional c, offset;

    // clear the interrupt right away so we can service next request
    _DMA3IF = false;

    // filter data
    if(use_buf_a) {
        c = VectorDotProduct(ADC_SAMPS, cur_buf_a[0], cur_filter);
    }
    else {
        c = VectorDotProduct(ADC_SAMPS, cur_buf_b[0], cur_filter);
    }

    // update offset
    if(is_motor_floating()) {
        // take exponential moving average
        fractional ema_data[EMA_LEN] = {c, my_boards_current.offset};
        my_boards_current.offset = 
            VectorDotProduct(EMA_LEN, ema_data, offset_ema_filter);
    }
    offset = my_boards_current.offset;

    // update current 
    my_boards_current.counts = c;
    //c = _Q15sub(c, offset);
    //my_boards_current.mA = (1.65*(1+Fract2Float(c))-1.65) * 1000.0 / 37.0;
    my_boards_current.mA = (1.65*(1+Fract2Float(c)));
    //my_boards_current.mA = Fract2Float(c) * my_boards_current.q15_to_mA;

    use_buf_a ^= true;
}

