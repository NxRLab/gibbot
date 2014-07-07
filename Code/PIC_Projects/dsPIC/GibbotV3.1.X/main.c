/* First iteration of code to go with the Gibbot v3 board. This code
 * will be developed to interface with a python controler on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MC806.h>
#include "gibbot.h"
#include "motorcontrol.h"
#include "peripherals.h"
/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRCPLL)
//Select the internal fast RC oscilator with phase lock loop or as the clock
_FOSC(OSCIOFNC_OFF)
//OSC2 (pin 40) is clock output
_FWDT(FWDTEN_OFF)
//Watchdog timer not automatically enabled
_FICD(ICS_PGD1)
//Communicate on PGEC1 (pin 17) and PGED1 (pin 18)
_FPOR(FPWRT_PWR128)
//Wait 128ms after power on to initialize

int main(void) {
    Startup();
    while (1){
    }
    return 0;
}
