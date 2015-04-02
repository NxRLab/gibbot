#ifndef UTILS_H
#define UTILS_H
/// @file

/// Shorthand for volatile unsigned int.
#define VUI volatile unsigned int

/// A function interrupt attribute
#define GIBINT __attribute__((interrupt, no_auto_psv))

extern void initialize_board(const Board *);
extern void print_banner(const Board *);
extern unsigned int calc_baud(unsigned long, bool);
extern long double calc_baud_error(unsigned long, bool);
extern size_t floor_power_of_two(size_t);

#endif /* UTILS_H */
