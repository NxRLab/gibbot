#ifndef  GIBIO_H
#define  GIBIO_H
/// @file

/// Definitions for formatting text sent to a terminal.
/** @defgroup colors Gibbot Serial I/O Color Macros
    @ingroup gibio

    To output text in color simply place the macros in this group into a printf
    statement. For example,
    
    @code
    // start printing in BOLD RED font. 
    printf(BOLD RED);

    print more stuff...

    printf(DEFAULT);
    @endcode

    Note the space between #BOLD and #RED! C/C++ will automatically combine the
    two separate strings.  When done printing in a specific color make sure to
    return the terminal back to its default settings by calling printf(DEFAULT)
    as in the above example.
     
    @note The following post was helpful in learning how to set color in a
    terminal: http://stackoverflow.com/questions/2616906
    
    @warning Failure to use a #DEFAULT in a printf can lead to your terminal
    printing in color even after exiting the PIC program. 
*/
/// @{

/// Print in black text. 
#define BLACK "\033[30m"
/// Print in red text. 
#define RED "\033[31m"
/// Print in green text. 
#define GREEN "\033[32m"
/// Print in yellow text. 
#define YELLOW "\033[33m"
/// Print in blue text. 
#define BLUE "\033[34m"
/// Print in magenta text. 
#define MAGENTA "\033[35m"
/// Print in cyan text. 
#define CYAN "\033[36m"
/// Print in white text. 
#define WHITE "\033[37m"
/// Return the terminal back to it's default settings.
#define DEFAULT "\033[0m"
/// Print in bold text.
#define BOLD "\033[1m"
/// Prints text with foreground and background colors reversed.
#define REVERSE "\033[7m"

extern bool color_stdout;
extern void turn_off_color_output();

/// @}

/// Low-level Helper Functions for <stdio.h> functions
/** @defgroup stdio Gibbot Serial I/O Helper Functions
    @ingroup gibio

    These functions allow for the useful <stdio.h> functions that are found in
    typical desktop programming environments.  These functions (should) enable
    the use of every function found in <stdio.h>, including printf, fprintf,
    fgets, etc.

    @note These functions do not have to be called directly.  The stdio
    functions will call them internally.
*/
/// @{

extern int open(const char *name, int access, int mode);
extern int write(int handle, void *buffer, unsigned int len);
extern int read(int handle, void *buffer, unsigned int len);
extern int close(int handle);

/// @}

/// @addtogroup gibio
/// @{

/// The carriage return character
#define CR '\r'
/// The new line (line feed) character
#define LF '\n'
/// The string terminator character
#define NUL '\0'

extern char *getsn(char *s, int len);
extern void info(const char *, ...);
extern void attn(const char *, ...);
extern void warn(const char *, ...);
extern void error(const char *, ...);

/// @}

#endif /*  GIBIO_H */
