#ifndef CURRENT_H
#define	CURRENT_H
/// @file

/// Reference zero voltage for current sensor
#define CURRENT_ZERO_VREF (3.3/2.0)
/// Resolution of current ADC
#define VOLTS_PER_12BIT_COUNT (3.3/4096.0)
/// Number of ADC pins connected to the 12-bit ADC module
#define ADC_PINS 1 
/// Number of ADC samples DMA will store per pin
#define ADC_SAMPS 16 

/// A struct for holding current information
struct Current {
    fractional counts; ///< The raw ADC count
    fractional offset; ///< The raw (automatically computed) zero Amp offset
    double q15_to_mA; ///< Conversion from Q15 number to milliamps
    double mA; ///< The number of milliamps corresponding to the ADC count
};

/// A type for holding current information
typedef struct Current Current;


/// Returns true if current's ADC module is running
extern bool is_cur_on();

/// Returns the ADC clock period in nanoseconds.
extern long double cur_clock_period_in_ns();
/// Returns the sampling time in nanoseconds
extern long double cur_sampling_time_in_ns();
/// Returns the number of counts given a desired period in ns.
extern unsigned int cur_clock_period_in_cnts(long double ns);
/// Returns the total time to sample and convert an analog pin
extern long double cur_12bit_conversion_time_in_ns();
/// Sets the filter coefficients of #cur_filter; @a arr can be NULL
extern void set_cur_filter_coeffs(double *arr);
/// Sets the filter coefficient of #offset_ema_coeffs for 0 <= alpha <= 1
extern void set_offset_ema_filter_alpha(double alpha);
/// Initializes the ADC1 and DMA3 peripherals to start taking current readings.
extern void init_cur(double mV_per_A);

/// Current (as in Amps) information for each board
extern volatile Current my_boards_current;

/// List of coefficients to multiply by
extern fractional cur_filter[ADC_SAMPS];


#endif	/* CURRENT_H */

