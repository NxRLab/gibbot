#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include "gibbot.h"

void High(int pin){
    if(pin == 1){
        P1OVDCONbits.POVD1H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD1L = 1;  //Turn overide off for low pin
    } else if(pin == 2){
        P1OVDCONbits.POVD2H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD2L = 1;  //Turn overide off for low pin
    } else if(pin == 3){
        P1OVDCONbits.POVD3H = 1;  //Turn overide off for high pin
        P1OVDCONbits.POVD3L = 1;  //Turn overide off for low pin
    }
}

void Low(int pin){
    if(pin == 1){
        P1OVDCONbits.POUT1H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT1L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD1H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD1L = 0; // Turn overide on for low pin
    } else if(pin == 2){
        P1OVDCONbits.POUT2H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT2L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD2H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD2L = 0; // Turn overide on for low pin
    } else if(pin == 3){
        P1OVDCONbits.POUT3H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT3L = 1; // PWM Low Pin override output is on
        P1OVDCONbits.POVD3H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD3L = 0; // Turn overide on for low pin
    }
}

void Float(int pin){
    if(pin == 1){
        P1OVDCONbits.POUT1H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT1L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD1H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD1L = 0; // Turn overide on for low pin
    } else if(pin == 2){
        P1OVDCONbits.POUT2H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT2L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD2H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD2L = 0; // Turn overide on for low pin
    } else if(pin == 3){
        P1OVDCONbits.POUT3H = 0; // PWM High Pin override output is off
        P1OVDCONbits.POUT3L = 0; // PWM Low Pin override output is off
        P1OVDCONbits.POVD3H = 0; // Turn overide on for high pin
        P1OVDCONbits.POVD3L = 0; // Turn overide on for low pin
    }
}

void duty(int duty){
    P1DC1 = duty;
    P1DC2 = duty;
    P1DC3 = duty;
}

void kick(void){
    char kick;
    char state;
    state = (!S3 << 2) | (!S2 << 1) | !S1;
    kick = ~state & 0b111;
    commutate(kick);
}

void commutate(int state){
    switch(state){
        case 0:
            Float(1); Float(2); Float(3);
            break;
        case 1:
            if(direction){
            High(1);  Float(2); Low(3);
            } else{
            Low(1);  Float(2); High(3);
            }
            break;
        case 2:
            if(direction){
            Low(1);   High(2);  Float(3);
            } else {
            High(1);   Low(2);  Float(3);
            }
            break;
        case 3:
            if(direction){
            Float(1); High(2);  Low(3);
            } else {
            Float(1); Low(2);  High(3);
            }
            break;
        case 4:
            if(direction){
            Float(1); Low(2);   High(3);
            } else {
            Float(1); High(2);   Low(3);
            }
            break;
        case 5:
            if(direction){
            High(1);  Low(2);   Float(3);
            } else{
            Low(1);  High(2);   Float(3);
            }
            break;
        case 6:
            if(direction){
            Low(1);   Float(2); High(3);
            } else {
            High(1);   Float(2); Low(3);
            }
            break;
    }
}
//Commutation pattern for the Maxon Motor
void state5() {
    if(direction){
    High(1);  Low(2);   Float(3);
    } else{
    Low(1);  High(2);   Float(3);
    }
}
void state1() {
    if(direction){
    High(1);  Float(2); Low(3);
    } else{
    Low(1);  Float(2); High(3);
    }
}
void state3() {
    if(direction){
    Float(1); High(2);  Low(3);
    } else {
    Float(1); Low(2);  High(3);
    }
}
void state2() {
    if(direction){
    Low(1);   High(2);  Float(3);
    } else {
    High(1);   Low(2);  Float(3);
    }
}
void state6() {
    if(direction){
    Low(1);   Float(2); High(3);
    } else {
    High(1);   Float(2); Low(3);
    }
}
void state4() {
    if(direction){
    Float(1); Low(2);   High(3);
    } else {
    Float(1); High(2);   Low(3);
    }
}
//Off State
void state0() { Float(1); Float(2); Float(3);}
//For Pittman Motor
//void state1() {High(1); Float(2); Low(3);}
//void state2() {Float(1); Low(2); High(3);}
//void state3() {High(1); Low(2); Float(3);}
//void state4() {Low(1); High(2); Float(3);}
//void state5() {Float(1); High(2); Low(3);}
//void state6() {Low(1); Float(2); High(3);}