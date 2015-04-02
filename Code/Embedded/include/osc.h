#ifndef OSC_H
#define OSC_H
/// @file

/// Clock Speed (instructions per second) set in init_osc_40_MHz()
#define FCY 40000000UL 

/// Number of seconds in a nanosecond
#define SEC_TO_NS 1000000000ULL

/// Initializes the CPU clock to 40 MHz
extern void init_osc_40_MHz();

#endif /* OSC_H */
