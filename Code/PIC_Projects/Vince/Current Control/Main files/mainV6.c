/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "initializeV6.h"
#include "motor.h"
#include "test.h"
//#include "core.h"
#include "menu.h"

int main(void) {
    initialize();

    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;

    write_string_UART("Hello World!\n",100);

    menu_run();
    
    return 0;







    /*initialize();
    write_string_UART("Hello world\r\n",100);
    __delay32(40000000);
    initialize_CurrentControl();
    while (1){
        if(USER){
            LED1 = !LED1;
            LED2 = !LED2;
            LED3 = !LED3;
            LED4 = !LED4;
            //TOPMAG = !TOPMAG;
            //commutate(7);
        }
       //test_MayDay();
    }
    return 0;
    */
}
