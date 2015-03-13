/* First iteration of code to go with the Gibbot v5 control board. This code
 * will be developed to interface with a python controller on the PC that
 * can drive the motor, control the moagnets and read data from the Gibbot.
 */

#include <p33EP512MC806.h>
#include "ControlLib.h"
#include "swing_control.h"

#include "swing_control.h"

int main(void) {
    initialize();

    char buf[MESSAGE_MAX], message[MESSAGE_MAX];
    int c='0';
    char state='x';
    int n=0;

    //allocate struct array of max size
    //struct args control_args = (struct args)malloc(N_MAX * sizeof(struct args));
    struct args control_args[N_MAX];


    while (1) {
    	printf("Press w to write, r to read, and x to swing: ");
        read_string_UART(buf,MESSAGE_MAX);

        c = buf[0];
        printf("%c\r\n",c);

        if(c=='w'){
            printf("Input n: ");
            read_string_UART(buf, MESSAGE_MAX);
            sscanf(buf,"%d", &n);
            printf("%d\r\n",n);
            write_swing(n, control_args);
        }
        else if(c=='r'){
            read_swing(n,control_args);
        }
        else if(c=='x'){
            //swing robot
        }
    }
    //free(control_args);
}
