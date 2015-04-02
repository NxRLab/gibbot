/// An example program showing how to use the motor.
/** @file
*/

#include <boards/pv7.h>
#include <gibbot.h>


volatile bool ccw;
volatile bool commutate;

int main()
{
    int i;
    char c;
    long double ms[] = 
        {1/50.0L, 1/20.0L, 1/5.0L, 1.0L, 5.0L, 20.0L, 50.0L, 1000.0L};
    int n = sizeof(ms)/sizeof(long double);

    initialize_board(&pv7);

    int pattern[COMMUTATION_STATES] = {0, 5, 1, 3, 2, 6, 4};
    i = 0;
    MDC = PHASE1 / 2;
    printf("MDC: %u PHASEx: %u\n", MDC, PHASE1);
    while(1) {
        read_xbee(&c, 1);
        printf("now pwm-ing state: %d\n", pattern[i]);
        read_xbee(&c, 1);
        CCW(pattern[i]);
        printf("ccw: %x %x %x\n", IOCON1, IOCON2, IOCON3);

        read_xbee(&c, 1);
        CW(pattern[i]);
        printf("cw: %x %x %x\n", IOCON1, IOCON2, IOCON3);

        i++;
        if(i == COMMUTATION_STATES) {
            i = 0;
        }
    }

    printf("\n\n");
    printf("*********************");
    printf("\n\n");

    for(i = 0; i < n; i++) {
        set_pwm_ticks(ms[i], &PTCON2, &PTPER, &MDC, false);
        printf("input: %Lg ms\n", ms[i]);
        printf("div: 1:%u, ticks: %u, initial duty: %u\n", 
            1 << PTCON2, PTPER, MDC);

        printf("pwm period: %Lg ms\n", 
            pwm_ticks_to_ms(PTPER, 1 << PTCON2 , false));

        printf("pwm freq: %Lg Hz\n", 
            1000.0L/pwm_ticks_to_ms(PTPER, 1 << PTCON2, false));

        printf("\n");
    }
    
    printf("edge aligned pwm:\n");
    printf("pwm period in counts: %u\n", ms_to_pwm_ticks(1.0L/20, 4, false));
    printf("pwm period in ms: %Lf\n", pwm_ticks_to_ms(1000, 4, false));

    printf("pwm period in counts: %u\n", ms_to_pwm_ticks(1.0L/50, 4, false));
    printf("pwm period in ms: %Lf\n", pwm_ticks_to_ms(400, 4, false));

    printf("center aligned pwm:\n");
    printf("pwm period in counts: %u\n", ms_to_pwm_ticks(1.0L/20, 4, true));
    printf("pwm period in ms: %Lf\n", pwm_ticks_to_ms(1000, 4, true));

    printf("pwm period in counts: %u\n", ms_to_pwm_ticks(1.0L/50, 4, true));
    printf("pwm period in ms: %Lf\n", pwm_ticks_to_ms(400, 4, true));

    DUTY = PWM_OFF;

    attn("Done!\n");
    while(1);

    return 0;
}

