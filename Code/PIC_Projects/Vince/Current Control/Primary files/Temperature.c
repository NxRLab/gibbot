/*This function is used to get the motor temperature from the secondary board.*/

#include <p33EP512MC806.h>
#include "UART.h"
#include "Temperature.h"
#include "initializeV6.h"


float read_motor_temp(void){
    /*Sends command to dsPIC on secondary board to read the motor temperature and
     waits for the data to be sent to primary board.  It is then typecast back to
     a float from the four unsigned chars sent over UART.
     */
    float temp;
    unsigned char data[5];
    unsigned short i;
    write_UART2('b');
    while(!(uart_buffer.len>3));
    for (i=0;i<5;i++){
        data[i] = read_UART();
    }
    temp = *((float *)data);
    return temp;
}
