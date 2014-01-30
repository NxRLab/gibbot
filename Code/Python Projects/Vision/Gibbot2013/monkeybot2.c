#include <plib.h>
#include <string.h>
#include <math.h>
#include "NU32v2.h"
#include "7366.h"
#define ISCMD(s1, s2) !strncmp(s1, s2, sizeof(s2))

#define E1 "e1"
#define E2 "e2"
#define U "u"
#define MO "mo"
#define F "f"
#define J "j"
#define SWITCH "s"
#define Q "q"
#define ON "on"
#define OFF "off"
#define SPACE ' '

int u, dir;

void printdata(int *samples);
void parse1arg(char *arg, int *dst, char *rsp);

int main(void) {
    char input[124];
    char *space;

    dir = 1;
    u = 0;
    initPIC();

    printf("Hello World!\r");
    while (1) {
        ReadUART3(input, sizeof (input));

        space = strchr(input, SPACE);
        if (space != NULL) {
            *space = '\0';
        }

        if (ISCMD(input, Q)) {
            DIR = 1;
            SetDCOC4PWM(0);
            printf("motor off\r");
        } else if (ISCMD(input, E1)) {
            if (space != NULL) {
                if (ISCMD(space + 1, ON)) {
                    EMAG1 = 1;
                } else if (ISCMD(space + 1, OFF)) {
                    EMAG1 = 0;
                }
            } else {
                EMAG1 = !EMAG1;
            }
            printf("e1 is %s\r", EMAG1 ? ON : OFF);
        } else if (ISCMD(input, E2)) {
            if (space != NULL) {
                if (ISCMD(space + 1, ON)) {
                    EMAG2 = 1;
                } else if (ISCMD(space + 1, OFF)) {
                    EMAG2 = 0;
                }
            } else {
                EMAG2 = !EMAG2;
            }
            printf("e2 is %s\r", EMAG2 ? ON : OFF);
        } else if (ISCMD(input, U)) {
            parse1arg(space, &u, "u");
        } else if (ISCMD(input, MO)) {
            if (space != NULL) {
                sscanf(space + 1, "%d %d", &dir, &u);
            }
            printf("motor:\r");
            printf("\t dir: %d dty: %d\r", dir, u);
            DIR = dir;
            SetDCOC4PWM(u);
        } else if (ISCMD(input, F)) {
            DIR = 1;
            SetDCOC4PWM(u);
            printf("swing!");
        } else if (ISCMD(input, J)) {
            DIR = 0;
            SetDCOC4PWM(MAX_DUTY - u);
            printf("swing!\r");
        } else if (ISCMD(input, SWITCH)) {
            if (DIR) {
                DIR = 0;
                SetDCOC4PWM(MAX_DUTY - u);
            } else {
                DIR = 1;
                SetDCOC4PWM(u);
            }
            printf("switch\r");
        } else {
            printf("???\r");
        }
    }
}

void parse1arg(char *arg, int *dst, char *rsp) {
    if (arg != NULL) {
        sscanf(arg + 1, "%d", dst);
        printf("updated ");
    }
    printf("%s: %d\r", rsp, *dst);
}

// timer3 ISR
// Read the encoder, and send over the data desired by printMode

void __ISR(_TIMER_3_VECTOR, ipl1) T3Interrupt(void) {
    // deleted old code -NR

    // clear interrupt flag and exit
    mT3ClearIntFlag();
}
