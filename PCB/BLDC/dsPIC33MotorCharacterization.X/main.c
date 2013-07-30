#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

int main(void){
    init_pwm();
    init_cn();
    init_uart();
    init_qei();
    state0();
    while(1){
    }
    return 0;
}

