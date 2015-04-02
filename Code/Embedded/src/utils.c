#include <gibbot.h>
/// @file

/** Initializes peripherals and sets the board's FCY to 40 MHz.
    @param b The board being initialized with valid pointers to its content.
    @warning This functions does not do any error checking.  The pointers stored
    in \b b must be non-null and point to valid objects.

The initialization process consists of the following:
    - setting the board's frequency,
    - mapping the peripherals to the dsPIC's I/O pins,
    - flashing the board's status LEDs, and
    - initialize onboard peripherals.
    - if the resolution of the current sensor is non-zero
        + setting the resolution of the current sensor
*/
void initialize_board(const Board *b)
{
    init_osc_40_MHz();

    // initialize board
    b->init_pins();
    b->flash_lights();
    b->init_periphs();
    close(-1);
}

/** Prints a short message that includes the last time the gibbot library 
    was compiled.

    @param b The board with a non-null name field.
*/
void print_banner(const Board *b)
{
    info("Hey!  I think the XBee is dropping characters.\n");
    info("Test with FTDI cable.\n");
    info("\n\n");
    info("*********************************************\n");
    info("Welcome!  Code last compiled on %s %s\n", __DATE__, __TIME__);
    info("Code is running on the %s\n", b->name);
    info("Waiting for a connection with a PC\n");
    /// @TODO: enter PC sync code
    info("****** OK, not really, TODO: enter PC sync code *******\n");
    info("Gibbot is on-line!\n");
    info("*********************************************\n");
    info("\n\n");
}

/** Calculates a baud rate given desired bits per second.
    @param bps The desired bits per second
    @param hs True if the UART is being used in high speed mode
    @return the closest UxBRG setting to \b bps

    @note The baud rate is based on p. 12 of Microchip's DS70000582E
    pdf (the dsPIC33 UART reference manual).
*/
unsigned int calc_baud(unsigned long bps, bool hs)
{
    return hs ? (FCY / (4 * bps)) - 1 : (FCY / (16 * bps)) - 1;
}

/** Calculates the baud rate error between the desired and actual setting
    @param bps The desired bits per second
    @param hs True, if high speed baud rate generation is desired
    @return (\a bps - actual bps)/\a bps, as a floating point number

    @note The error is based on p. 12 of Microchip's DS70000582E
    pdf (the dsPIC33 UART FRM).
*/
long double calc_baud_error(unsigned long bps, bool hs)
{
    return (calc_baud(bps, hs) - bps)/((double) bps);
}

/** Computes the largest power of two less than x.
    @param x an integer whose floor is to be taken.
    @note The algorithm's run time is reported as 4 * (# of ones in x).

    The code is taken from 
    [p. 48](http://www.pearsonhighered.com/samplechapter/0201914654.pdf) of 
    Hacker's Delight, 2/E, Henry S. Warren, ISBN-10: 0321842685.
*/
size_t floor_power_of_two(size_t x)
{
    size_t y;
    do {
        y = x;
        x = x & (x - 1);
    } while(x != 0);

    return y;
}
