/// An example program showing how to use the Gibbot I/O functions.
/** @file
*/

#include <boards/pv7.h>
//#include <boards/breakout.h>
#include <gibbot.h>

#define PRINT_NTIMES 5
#define PRINT_DELAY 150
#define LEN 100

/// A simple example showing basic input/output functionality
int main()
{
    int i;
    char buf[LEN];

    // turn_off_color_output(); // call if color not supported by PC terminal
    initialize_board(&pv7);

   info("printing Hello World! %d times...\n", PRINT_NTIMES);
    for(i = 1; i <= PRINT_NTIMES; i++) {
        printf("%d) Hello World!\n", i);
        __delay_ms(PRINT_DELAY);
    }

    info("enter input %d times...\n", PRINT_NTIMES);
    for(i = 1; i <= PRINT_NTIMES; i++) {
        warn("%d) ", i);
        getsn(buf, LEN);
        error(">>>> %s\n", buf);
    }

    attn("Done!\n");
    while(1);

    return 0;
}
