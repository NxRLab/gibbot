/// Provides functions for reading and writing encoders
/** @file
*/

#include <gibbot.h>


Encoder my_magnet_enc;

bool is_magnet_enc_on()
{
    return QEI1CONbits.QEIEN;
}

long read_magnet_enc()
{
    my_magnet_enc.low16 = POS1CNTL;
    my_magnet_enc.high16 = POS1HLD;
    my_magnet_enc.value = 
        (my_magnet_enc.high16 << MSW_SHIFT)  | my_magnet_enc.low16;

    return my_magnet_enc.value;
}

void write_magnet_enc(long int value)
{
    POS1HLD = value >> MSW_SHIFT;
    POS1CNTL = value & LSW_MASK;
}

void init_magnet_enc(long int counts_per_revolution)
{
    my_magnet_enc.read = read_magnet_enc;
    my_magnet_enc.write = write_magnet_enc;
    my_magnet_enc.offset = read_magnet_enc();
    my_magnet_enc.cpr = counts_per_revolution;

    // MODE 5 PIMOD = 6 is modulo counting
    // MODE 6 PIMOD = 5 also has interesting modulo properties GEC & LEC

    // turn on QEI 1
    QEI1CONbits.QEIEN = true;
}

// TODO add to h file  also might as well add INT1TMR too (with func)
long double magnet_vel(long double ms)
{
    // must make sure that QEI1STATbits.VELOVIRQ != 1
    return VEL1CNT / ms;
}

// TODO is the INT1TMR a good measure of QEI speed? It's a 32-bit timer
// TODO do we want digital filtering on the pins?  yes find out min pulse from
// motor spec sheet.
