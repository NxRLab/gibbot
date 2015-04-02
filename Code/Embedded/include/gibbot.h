#ifndef GIBBOT_H
#define GIBBOT_H
/// @file

// microchip lib
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include <xc.h>
#include <dsp.h>
#include <libq.h>

// gibbot lib
#include <osc.h>
#include <brd.h>
#include <utils.h>
#include <timers.h>
#include <queue.h>
#include <gibio.h>
#include <xbee.h>
#include <pic2pic.h>
#include <current.h>
#include <motor_pwm.h>
#include <encoder.h>
#include <magnet_enc.h>

// microchip lib
#include <libpic30.h> // this header must come **after** FCY defined in <osc.h>

#endif /* GIBBOT_H */

// Modules to place code in.  All top-level @defgroups should be defined here.

/// Provides a set of functions for sending and receiving text.
/** @defgroup gibio Gibbot Serial I/O
*/

/// A list of interrupts used by the Gibbot library.
/** @defgroup ints Peripheral Interrupts
*/

/// Macros for profiling code.
/** @defgroup prof Timing Code

    #TxTICK and #TxTOCK are used to time code snippets.  They must be used
    together when timing code.  If \a msg is the empty string (""), then no
    output message is printed.  This can be useful for accurately recording how
    long multiple functions are taking without the overhead of the call to
    printf by these functions.  Otherwise, if \a msg is not empty, then a short
    summary of how long the code took to run is printed.  The time elapsed is
    considered valid if #TxIF == 0.

    @TODO: move stuff below out of here and into example code.

    To user Timer 1 to profile a piece of code that should take no more than 10
    ms to run, then macros can be used as follows:

    \code
    TxTICK(1, "Code Snippet", 10.0);

    // code snippet goes here

    TxTOCK(1, "Code Snippet");
    \endcode

    A summary would then be printed.  Providing a hint of 10 ms allows for the
    automatic selection of a prescaler that will give the highest resolution
    possible when timing the snippet of code.  If Timer 1's interrupt flag did
    not go off during the profiling of the code (given in the summary), then the
    results are valid.  Otherwise, 10 ms was not a good max value and a longer
    period of time will have to be chosen and the test rerun.

    If multiple instances of #TxTICK and #TxTOCK appear, then printing a summary
    will aversely affect the timing of the code.  To suppress a message being
    printed out, pass the empty string into these functions.  The count in the
    #TMRx register and the #TxIF will have to be stored/checked manually by the
    caller.  An example usage with the empty string would be:

    \code
    TxTICK(1, "", 10.0);

    // code snippet goes here

    TxTOCK(1, "");
    // now store TMR1 for later analysis and check _T1IF to make sure count is
    // valid.  It can also be stored for later analysis.
    \endcode

    @warning As these are macros, there is no real type checking.  The caller
    must make sure that the arguments are correct.
*/
