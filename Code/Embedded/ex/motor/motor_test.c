/// An example program showing how to use the motor.
/** @file
*/

#include <boards/pv7.h>
#include <gibbot.h>

volatile bool ccw;
volatile bool commutate;
volatile unsigned int last_state;
unsigned char states[1024];
RingBuffer rb;

int main()
{
    char c;
    unsigned int state = 0;

    initialize_board(&pv7);

    init_q(states, sizeof(states), &rb);

    CNENDbits.CNIED3 = true; //Turn on CN for RD3
    CNENDbits.CNIED4 = true; //Turn on CN for RD4
    CNENDbits.CNIED5 = true; //Turn on CN for RD5
    _CNIP = 4; //Set priority to 4 
    _CNIF = false;     //Clear interrupt flag
/*
    printf("press any key to start.\n");
    read_xbee(&c, 1);

    _CNIE = true;
    DUTY = MAX_DUTY / 2;
    _CNIF = true;
    while(!USER);
    _CNIE = false;
    float_pins();
//    while(1);
    unsigned int last_state = -1;
    while(!USER) {
        state = HALL;
        if(state == 0 || state == 7) {
            state = HALL;
        }

        if(last_state ^ state && state > 0 && state < 7) {
            CW(state);
        }

        last_state = state;
    }

    float_pins();

    while(1);

    last_state = PORTD;
    last_state = (last_state >> 3) & 7;
*/

    printf("ENTER THE GIBBOT\n");
    c = 0;
    while(c != 'q') {
        read_xbee(&c, 1);
        if(c == 'j') {
            commutate = false;
            printf("cw: %d (%x %x %x).\n", HALL, IOCON1, IOCON2, IOCON3);
            CW(HALL);
        }
        else if(c == 'k') {
            commutate = false;
            printf("ccw: %d (%x %x %x).\n", HALL, IOCON1, IOCON2, IOCON3);
            CCW(HALL);
        }
        else if(c == 'h') {
            printf("duty up %d -> ", DUTY);
            DUTY += 10;
            printf("%d.\n", DUTY);
        }
        else if(c == 'l') {
            printf("duty down %d -> ", DUTY);
            DUTY = (DUTY < 10) ? 0 : DUTY - 10;
            printf("%d.\n", DUTY);
        }
        else if(c == 'c') {
            _CNIF = false;
            _CNIE ^= true;
            printf("cn %d\n", _CNIE);
        }
        else if(c == 'a') {
            commutate = false;
            float_pins();
            commutate = true;
            ccw = true;
            _CNIF = false;
            _CNIE = true;
            _CNIF = true;
            printf("commutate ccw\n");
        }
        else if(c == 'b') {
            commutate = false;
            float_pins();
            commutate = true;
            ccw = false;
            _CNIF = false;
            _CNIE = true;
            _CNIF = true;
            printf("commutate cw\n");
        }
        else if(c == 'i') {
            printf("current state: %d\n", HALL);
        }
        else if(c == 'L') {
            LED1 = LED_OFF;
            LED2 = LED_OFF;
        }
        else {
            commutate = false;
            float_pins();
            DUTY = 0;
            printf("OFF (%x %x %x).\n", IOCON1, IOCON2, IOCON3);
        }
    }

    DUTY = 0;
    float_pins();

    attn("Done!\n");
    while(1);

    return 0;
}

const unsigned int ccwpat[] = {-1, 3, 6, 2, 5, 1, 4, -1};
const unsigned int cwpat[] = {-1, 5, 3, 1, 6, 4, 2, -1};
volatile unsigned int last_state = -1;
void GIBINT _CNInterrupt()
{
    unsigned int state, valid_ccw, valid_cw;

    // clear the interrupt flag
    _CNIF = false;

    state = HALL;

    // add nTries and return if failed
    if(state <= 0 || state >= 7) {
        state = HALL;
        LED2 = LED_ON;
    }

    if(state <= 0 || state >= 7) {
        return;
    }

    if(last_state ^ state) {
        if(last_state != -1) {
            valid_ccw = ccwpat[last_state];
            valid_cw = cwpat[last_state];
            if(state != valid_ccw && state != valid_cw) {
                // TODO clamp magnets too
                LED1 = LED_ON;
                /*
                float_pins();
                error("motor commutation pattern is out of sync: turning motor off\n");
                error("last state was %d. valid states are %d and %d, got %d\n", 
                    last_state, valid_ccw, valid_cw, state);
                error("stopping program\n");
                while(1);
                */
            }
        }
    }

    if(commutate) {
        ccw ? CCW(state) : CW(state);
    }
    else {
        printf("\t state: %u (%x) \n", state, state);
    }

    last_state = state;


    // mismatch condition cleared by read from state
}

#if 0
volatile int i;
void GIBINT _CNInterrupt(void) 
{
    unsigned int state;

    // clear the interrupt flag
    _CNIF = false;

    // to turn the motor
    // step 1: make sure you want the motor to move!
    // step 2: commutate(state);

    state = PORTD;
    state = (state >> 3) & 7;

    // for now just print the current state of the hall effect sensors and
    // toggle an LED
    //printf("turn %d\n", i++);
    LED3 = !(state & 0x1);
    LED2 = !(state & 0x2);
    LED1 = !(state & 0x4);

    unsigned char c, p;
    c = (unsigned char) state;
    if(!enq(c, &rb)) {
        float_pins();
        int i = 0;
        p = 0;
        while(deq(&c, &rb)) {
            if(p == c) {
                printf("%d) state: %u valid next states: %u %u previous: %u\n", 
                    ++i, c, ccwpat[c], cwpat[c], p);
            }
            else {
                error("%d) state: %u valid next states: %u %u previous: %u\n", 
                    ++i, c, ccwpat[c], cwpat[c], p);
            }
            p = c;
            read_xbee(&c, 1);
        }
    }


    if(false && (state != ccwpat[last_state] && state !=
        cwpat[last_state])) {
        error("noisy state...ending program\n");
        printf("last state: %u  next state: %u valid next states: %u %u\n", 
            last_state, state, ccwpat[last_state], cwpat[last_state]);
        while(1) {
            LED3 = !(state & 0x1);
            LED2 = !(state & 0x2);
            LED1 = !(state & 0x4);
        }
    }
    last_state = state;


    // mismatch condition cleared by read from state
    if(commutate) {
        if(ccw) {
            CCW(state);
        }
        else {
            CW(state);
        }
    }
    else {
        //printf("state: %u (%x) \n", state, state);
    }
}
#endif


// TODO incorporate following info into documentation.
// motor is 3-phase 7 pole-pairs there are six magnets in a pair such that wires
// of opposite polarity are in opposite groups of three (A+, B-, C-) and (A-,
// B+, C+) is one potential pole-pair grouping.  The six individual magnets make
// up an eletrical commutation sequence or 360e (electrical degrees).
// Therefore, one pole-pair is equal to 360e.  With respect to the motor being 7
// pole-pair, we have that 7 electrical revolution is then 1 mechanical (rotor)
// revolution.  Hence 7 pole-pairs.  This means that each magnet is spaced 360/(7
// * 6) degrees apart.  This can be useful information when testing the
// encoders.
