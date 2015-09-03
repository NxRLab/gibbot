#ifndef UTILS_H
#define UTILS_H
/// @file

/// Shorthand for volatile unsigned int.
#define VUI volatile unsigned int

/// 32-bit to 16-bit mask and shift amounts
#define LSW_MASK 0xFFFF
#define MSW_SHIFT 16

/// A function interrupt attribute
#define GIBINT __attribute__((interrupt, no_auto_psv))
/// Attribute for defining variables in DPSRAM space
#define GIBDMA __attribute__((eds, space(dma)))
/// Attribute for placing large arrays in extended data space memory (EDS)
#define GIBEDS __attribute__((eds, space(eds)))

extern void initialize_board(const Board *);
extern void print_banner(const Board *);
extern unsigned int calc_baud(unsigned long, bool);
extern long double calc_baud_error(unsigned long, bool);
extern size_t floor_power_of_two(size_t);

#endif /* UTILS_H */
