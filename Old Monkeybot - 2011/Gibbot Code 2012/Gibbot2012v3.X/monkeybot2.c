#include <plib.h>
#include <string.h>
#include <math.h>
#include "NU32v2.h"
#include "7366.h"
#define ISCMD(s1, s2) !strncmp(s1, s2, sizeof(s2))

// t1: 700 u1: 1000 f1: 10 t2: 800 u2: 0

#define T1 "t1"
#define T2 "t2"
#define T3 "t3"
#define T4 "t4"
#define F1 "f1"
#define F2 "f2"
#define F3 "f3"
#define F4 "f4"
#define U1 "u1"
#define U2 "u2"
#define U3 "u3"
#define U4 "u4"
#define ALL "all"
#define E1 "e1"
#define E2 "e2"
#define S1 "s1"
#define S2 "s2"
#define S3 "s3"
#define S4 "s4"
#define SW "sw"
#define MO "mo"
#define F "f"
#define J "j"
#define GO "go"
#define ON "on"
#define OFF "off"
#define DATA "dat"
#define SPACE ' '
#define SAMPLES 2000
#define NSENSORS 7

int t1, t2, t3, t4, f1, f2, f3, f4, u1, u2, u3, u4, tmp1, tmp2, tmp3, tmp4;
unsigned char readbuf[COUNTER_BYTES];

int sample, roll;

enum {
    MOTOR,
    MAGNET1,
    MAGNET2,
    ACCEL1,
    ACCEL2,
    GYRO1,
    GYRO2
};

int sensors[SAMPLES][NSENSORS];
volatile int oldth2, th2, dth2;

void printdata(int *samples);
void parse1arg(char *arg, int *dst, char *rsp);

void s1(void);
void s2(void);
void s3(void);
void s4(void);

void s1(void) {
    EMAG1 = 1;
    EMAG2 = 0;
    delayms(f1);
    DIR = 1;
    SetDCOC4PWM(u1);
    delayms(t1);
}

void s2(void) {
    EMAG1 = 0;
    EMAG2 = 1;
    delayms(f2);
    DIR = 0;
    SetDCOC4PWM(u2);
    delayms(t2);
}

void s3(void) {
    EMAG1 = 1;
    EMAG2 = 0;
    DIR = 0;
    delayms(f3);
    SetDCOC4PWM(u3);
    delayms(t3);
}

void s4(void) {
    EMAG1 = 0;
    EMAG2 = 1;
    delayms(f4);
    DIR = 1;
    SetDCOC4PWM(u4);
    delayms(t4);
}

int main(void) {
    char input[124];
    char *space;

    int enc = 0;
    initPIC();
    printf("Hello World 2 \r");
    while (1) {
        // read motor encoder
        read_7366(MOT, CNTR, readbuf);
        enc = (((int) (readbuf[0])) << 8) | ((int) (readbuf[1]));
        printf("enc: %d -- r0: 0x%x -- r1: 0x%x\r",
                enc, readbuf[0], readbuf[1]);
    }


    th2 = (int) (atan2(((float) ACC2X - 505.0), ((float) ACC2Y - 530.0))*180.0 / 3.1416);
    initPIC();

    t1 = 800;
    u1 = 1000;

    t2 = 800;
    f2 = 100;

    t3 = 850;

    t4 = 800;
    f4 = 100;
    u4 = 1000;

    LED0 = 1;
    LED1 = 1;
    tmp1 = 1;
    tmp2 = 0;

    t1 = 0;
    SetDCOC4PWM(t1);


    printf("Hello World!\r");
    while (1) {
        ReadUART3(input, sizeof (input));

        space = strchr(input, SPACE);
        if (space != NULL) {
            *space = '\0';
        }
        /*
                if (th2 - oldth2 > 0) {
                    DIR = 0;
                } else {
                    DIR = 1;
                }

                if (ISCMD(input, T1)) {
                    parse1arg(space, &t1, T1);
                    SetDCOC4PWM(t1);
                    printf("th2: %d\r", th2);
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
                }
                continue;
         */

        if (ISCMD(input, T1)) {
            parse1arg(space, &t1, T1);
        } else if (ISCMD(input, T2)) {
            parse1arg(space, &t2, T2);
        } else if (ISCMD(input, T3)) {
            parse1arg(space, &t3, T3);
        } else if (ISCMD(input, T4)) {
            parse1arg(space, &t4, T4);
        } else if (ISCMD(input, F1)) {
            parse1arg(space, &f1, F1);
        } else if (ISCMD(input, F2)) {
            parse1arg(space, &f2, F2);
        } else if (ISCMD(input, F3)) {
            parse1arg(space, &f3, F3);
        } else if (ISCMD(input, F4)) {
            parse1arg(space, &f4, F4);
        } else if (ISCMD(input, U1)) {
            parse1arg(space, &u1, "u1");
        } else if (ISCMD(input, U2)) {
            parse1arg(space, &u2, "u2");
        } else if (ISCMD(input, U3)) {
            parse1arg(space, &u3, "u3");
        } else if (ISCMD(input, U4)) {
            parse1arg(space, &u4, "u4");
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
        } else if (ISCMD(input, S1)) {
            printf("s1\r\t t1: %d f1: %d u1: %d\r", t1, f1, u1);
            EMAG1 = 1;
            EMAG2 = 0;
            delayms(f1);
            DIR = 1;
            SetDCOC4PWM(u1);
            delayms(t1);

            DIR = 1;
            SetDCOC4PWM(0);
            EMAG1 = 1;
            EMAG2 = 1;
        } else if (ISCMD(input, S2)) {
            printf("s2\r\t t2: %d f2: %d u2: %d\r", t2, f2, u2);
            EMAG1 = 0;
            EMAG2 = 1;
            delayms(f2);
            DIR = 0;
            SetDCOC4PWM(u2);
            delayms(t2);

            DIR = 1;
            SetDCOC4PWM(0);
            EMAG1 = 1;
            EMAG2 = 1;
        } else if (ISCMD(input, S3)) {
            printf("s3\r\t t3: %d t3: %d u3: %d\r", t3, f3, u3);
            EMAG1 = 1;
            EMAG2 = 0;
            DIR = 0;
            delayms(f3);
            SetDCOC4PWM(u3);
            delayms(t3);

            DIR = 1;
            SetDCOC4PWM(0);
            EMAG1 = 1;
            EMAG2 = 1;
        } else if (ISCMD(input, S4)) {
            printf("s4\r\t t4: %d f4: %d u4: %d\r", t4, f4, u4);
            EMAG1 = 0;
            EMAG2 = 1;
            delayms(f4);
            DIR = 1;
            SetDCOC4PWM(u4);
            delayms(t4);

            DIR = 1;
            SetDCOC4PWM(0);
            EMAG1 = 1;
            EMAG2 = 1;
        } else if (ISCMD(input, SW)) {
            if (space != NULL) {
                sscanf(space + 1, "%d %d %d %d", &tmp1, &tmp2, &tmp3, &tmp4);
                printf("sw\r\t em: %d t: %d dir: %d u: %d\r",
                        tmp1, tmp2, tmp3, tmp4);

                EMAG1 = tmp1 & 1;
                EMAG2 = tmp1 >> 1;
                DIR = tmp3;
                SetDCOC4PWM(tmp4);
                delayms(tmp2);

                DIR = 1;
                SetDCOC4PWM(0);
                EMAG1 = 1;
                EMAG2 = 1;
            } else {
                printf("sw ???\r");
            }
        } else if (ISCMD(input, MO)) {
            if (space != NULL) {
                sscanf(space + 1, "%d %d", &tmp1, &tmp2);
            }
            printf("motor:\r");
            printf("\t dir: %d dty: %d\r", tmp1, tmp2);
            DIR = tmp1;
            SetDCOC4PWM(tmp2);
        } else if (ISCMD(input, F)) {
            DIR = 1;
            SetDCOC4PWM(u1);
        } else if (ISCMD(input, J)) {
            DIR = 0;
            SetDCOC4PWM(u3);
        } else if (ISCMD(input, GO)) {
            printf("go!\r");
            printf("\t t1: %d f1: %d u1: %d t2: %d f2: %d u2: %d\r",
                    t1, f1, u1, t2, f2, u2);

            s3();
            s4();
            s3();
            s4();

            EMAG1 = 1;
            EMAG2 = 1;
            DIR = 0;
            SetDCOC4PWM(1000);
            delayms(100);

            s2();
            s1();
            s2();
            s1();

            EMAG1 = 1;
            EMAG2 = 1;
            DIR = 1;
            SetDCOC4PWM(0);
            /*
                        EMAG1 = 1;
                        EMAG2 = 0;
                        delayms(f1);
                        DIR = 1;
                        SetDCOC4PWM(u1);
                        delayms(t1);

                        EMAG1 = 0;
                        EMAG2 = 1;
                        delayms(f2);
                        DIR = 0;
                        SetDCOC4PWM(u2);
                        delayms(t2);

                        EMAG1 = 1;
                        EMAG2 = 1;
                        DIR = 1;
                        SetDCOC4PWM(0);
             */
        } else if (ISCMD(input, DATA)) {
            int i;
            // disable timer interrupt
            mT3IntEnable(0);
            if (roll) {
                for (i = sample + 1; i < SAMPLES; i++) {
                    printdata(sensors[i]);
                }
            }

            for (i = 0; i <= sample; i++) {
                printdata(sensors[i]);
            }

            sample = 0;
            roll = 0;
            mT3ClearIntFlag();
            mT3IntEnable(1);

        } else {
            printf("???\r");
        }
    }
}

void printdata(int *samples) {
    int i;
    for (i = 0; i < NSENSORS; i++) {
        printf("%d ", samples[i]);
    }
    printf("\r");
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
    sample++;
    if (sample >= SAMPLES) {
        sample = 0;
        roll = 1;
    }

    read_7366(MOT, CNTR, readbuf); //corresponds to encoders
    sensors[sample][MOTOR] =
            (((int) (readbuf[0])) << 8) | ((int) (readbuf[1]));

    read_7366(MAG1, CNTR, readbuf); //corresponds to encoders
    sensors[sample][MAGNET1] =
            (((int) (readbuf[0])) << 8) | ((int) (readbuf[1]));

    read_7366(MAG2, CNTR, readbuf); //corresponds to encoders
    sensors[sample][MAGNET2] =
            (((int) (readbuf[0])) << 8) | ((int) (readbuf[1]));

    sensors[sample][ACCEL1] =
            (int) (atan2(((float) ACC1X - 505.0), ((float) ACC1Y - 530.0))*180.0 / 3.1416);

    sensors[sample][ACCEL2] =
            (int) (atan2(((float) ACC2X - 505.0), ((float) ACC2Y - 530.0))*180.0 / 3.1416);

    sensors[sample][GYRO1] = GYRO1HI;
    sensors[sample][GYRO2] = GYRO2HI;

    oldth2 = th2;
    th2 = sensors[sample][ACCEL2];
    dth2 = th2 - oldth2;

    //printdata(sensors[sample]);

    // clear interrupt flag and exit
    mT3ClearIntFlag();
}
