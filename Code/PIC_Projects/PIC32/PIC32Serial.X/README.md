This code enables a PIC32 to act as a pass-through serial port for the Gibbot
dsPIC.  It is a modified version of talkingPIC.c found in the ME 333 stock code.

# CHANGES
The following additions/modifications have been made to the code:
* UART2 is enabled.
* UART1 and UART2 have RX interrupts enabled.
* RX bytes from UART1 (i.e., TX from a  PC) are sent to UART2's TX register.
* RX bytes from UART2 (i.e., TX from a dsPIC) are sent to UART1's TX register.

These changes can be found in NU32.c.  Example usage is in talkingPIC.c.
 
# WIRING
Make sure to connect XBEE ground to PIC32 ground.  PIC32's RX pin (F4) to XBEE
TX pin and PIC32's TX pin (F5) to XBEE RX pin.  All XBEE pins are labeled on the
Gibbot PCB's silkscreen.

** Do not connect any other pins. **
