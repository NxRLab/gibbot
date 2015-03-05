/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "ControlLib.h"
#include "swing_control.h"

int main(void) {
    initialize();
    
    unsigned char c='0';
    unsigned char state='x';
    int n=0;

    //allocate struct array of max size
    struct args* control_args = (struct args*)malloc(N_MAX * sizeof(struct args));

    //Give control arguments to PIC, check parameters and run swing
        printf("Press w to write, r to read, and x to swing\n");

    while (1) {
        c = read_UART();
        if(c=='w'){
            printf("Input n: \n");
            scanf("%d",&n);
            write_swing(n, control_args);
        }
        else if(c=='r'){
            printf('Enter n to print everything, or specify state to check\n');
            state = read_UART();
            read_swing(state,n,control_args);
        }
        else if(c=='x'){
            //swing robot
        }
    }
    free(control_args);
}
