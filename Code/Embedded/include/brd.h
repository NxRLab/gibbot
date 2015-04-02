#ifndef BOARD_H
#define BOARD_H
/// @file

/// A struct to hold board-specific properties.
/**
@remark See p. 147 of XC16 C Compiler User Guide for why const is repeated twice
in member name.  The desired behaviour is a pointer whose address cannot be
changed and points to a string literal.
*/
struct Board {
    /// the board's name
    const char * const name; 
    /// the function that set's the board's I/O pins
    void (*init_pins)(void); 
    /// the function that starts onboard peripherals
    void (*init_periphs)(void); 
    /// the function that flashes onboard LEDs
    void (*flash_lights)(void); 
    /// the function for the current commutation state of the robot
};

typedef struct Board Board;

#endif /* BOARD_H */
