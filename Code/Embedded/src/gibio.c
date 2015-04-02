/// Provides a set of functions for sending and receiving text.
/** @file

    @example hello.c
    hello.c provides example usage of various functions such as printf, getsn(),
    and info().
*/

#include <gibbot.h>

/** Places read, write, open, & close in .libc section

    @note See p. 48 Customizing STDIO 2.13.2 of 16-bit Language Tools Libraries
    for more info.
*/
#define GIBIO __attribute__((__section__(".libc.gibbot"))) 

/// Tells the compiler that the function's first two arguments are printf-like.
#define GIBPRNT __attribute__((format (printf, 1, 2)))

/// A list of handles.
enum gibio_handles {
    STDIN_HNDL, // by default 0-2 are reserved for stdin & friends
    STDOUT_HNDL,
    STDERR_HNDL, // place all handles **below** this one
    NUM_HANDLES // place all handles **above** this one
};

/// Controls whether color codes are sent to the PC terminal.  True by default.
bool color_stdout = true;

/// Turns off color output and sets the terminal back to its #DEFAULT state.
/** 
    This function should be called if unwanted characters are showing up in the
    terminal such as those corresponding to #RED, #DEFAULT, etc.
*/
void turn_off_color_output()
{
    color_stdout = false;
    printf(DEFAULT);
}

/// Returns a string from \c stdin with the terminating #LF or #CR removed.
/** 
    @param s Pointer to a valid pre-allocated array of at least \a len bytes.
    @param len The maximum number of bytes to write into \a s.
    @return Either the first \a len - 1 characters read from \c stdin unless a
    [line feed](\ref #LF) or [carriage return](\ref #CR) is encountered first.
    If the latter happens first, the resulting string will have the #LF or #CR
    removed.

    @note This functions works exactly as the getsn() function found in other
    libc libraries, but it is not implemented in Microchip version of libc.  To
    be fair, getsn() is not a standard (ANSI) C function.
*/
char *getsn(char *s, int len)
{
    char *c;
    s = fgets(s, len, stdin);
    if(s != NULL) {
        c = (char *) memchr(s, LF, len); 
        if(c != NULL) {
            *c = NUL;
        }
    }

    return s;
}

/// Prints informational text in #MAGENTA, if supported by PC terminal.
void GIBPRNT info(const char *format, ...)
{
    va_list ap;

    if(color_stdout) {
        // print in color 
        printf(MAGENTA);
    }

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);

    if(color_stdout) {
        // set back to default style
        printf(DEFAULT);
    }
}

/// Prints attn text in #BOLD #RED, if supported by PC terminal.
void GIBPRNT attn(const char *format, ...)
{
    va_list ap;

    if(color_stdout) {
        // print in color 
        printf(BOLD RED);
    }

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);

    if(color_stdout) {
        // set back to default style
        printf(DEFAULT);
    }
}

/// Prints warning text with a #CYAN background, if supported by PC terminal.
void GIBPRNT warn(const char *format, ...)
{
    va_list ap;

    if(color_stdout) {
        // print in color 
        printf(REVERSE CYAN);
    }

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);

    if(color_stdout) {
        // set back to default style
        printf(DEFAULT);
    }
}

/// Prints error text with a #RED background, if supported by PC terminal.
void GIBPRNT error(const char *format, ...)
{
    va_list ap;

    if(color_stdout) {
        // print in color 
        printf(REVERSE RED);
    }

    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);

    if(color_stdout) {
        // set back to default style
        printf(DEFAULT);
    }
}

/// The helper function required by Microchip for file I/O writes.
int GIBIO write(int handle, void *buffer, unsigned int len)
{
    switch (handle) {
        case STDIN_HNDL: // transmit over xbee
        case STDOUT_HNDL:
        case STDERR_HNDL:
            len = write_xbee(buffer, len);
            break;

        default:
            len = 0;
            break;
    }

    return len;
}

/// The helper function required by Microchip for file I/O reads.
int GIBIO read(int handle, void *buffer, unsigned int len)
{
    switch (handle) {
        case STDIN_HNDL: // receive over xbee
            len = read_xbee(buffer, len);
            break;

        default:
            printf("unrecognized handle: %d\n", handle);
            len = 0;
            break;
    }

    return len;
}

/** The helper function required by Microchip for file I/O close.
    @warning This function should never be called.
*/
int GIBIO close(int handle)
{
    // printf("close: closing handle %d (this shouldn't happen)\n", handle);
    return EOF;
}

/** The helper function required by Microchip for file I/O open.
    @warning This function should never be called.
*/
int GIBIO open(const char *name, int access, int mode)
{
    printf("open: %s is not a valid file name.\n", name);
    return EOF;
}
