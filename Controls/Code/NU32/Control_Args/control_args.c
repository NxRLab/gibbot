#include "NU32.h"
#include "swing_control.h"

int main(void) {
    NU32_Startup();

    //NU32_WriteUART1("HelloWorld\n");
    char buf[MESSAGE_MAX];
    int c='0';
    char state='x';
    int n=0;

    //allocate struct array of max size
    //struct args control_args = (struct args)malloc(N_MAX * sizeof(struct args));
    struct args control_args[N_MAX];

    
    while (1) {
    	NU32_WriteUART1("Press w to write, r to read, and x to swing\r\n");
        NU32_ReadUART1(buf,MESSAGE_MAX);

        c = buf[0];
        
        if(c=='w'){
            NU32_WriteUART1("Input n: \r\n");
            NU32_ReadUART1(buf, MESSAGE_MAX);
            sscanf(buf,"%d", &n);
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
