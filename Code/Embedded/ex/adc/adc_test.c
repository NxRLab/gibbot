#include <boards/pv7.h>
#include <gibbot.h>

#define PRINT_LEN 10

/// Sets current readings so 0 V = -1.5 mA and 3.3 V = 1.5 mA
#define SCALED_VOLTS (2.0/3.3*VOLTS_PER_12BIT_COUNT)

int main()
{
    int i;
    char c;
    fractional adc;
    double mA_cnts;

    initialize_board(&pv7);
    print_banner(&pv7);
    printf("Hello World!\n");

    mA_cnts = my_boards_current.q15_to_mA;
    
    long double conv = cur_12bit_conversion_time_in_ns() / 1000;
    printf("ADC clock: %Lg us --- %d samples will take %Lg us\n", 
        conv, ADC_SAMPS, ADC_SAMPS * conv);

    printf("for this demo we will effectively turn off the EMA used to ");
    printf("smooth the offset filter.  This will make the ");
    printf("current values reflect the raw ADC readings.\n");
    printf("the resolution will also be overwritten, so that ");
    printf(" ADC_MIN = -1.65 and ADC_MAX = 1.65\n");
    set_offset_ema_filter_alpha(0);
    my_boards_current.offset = 0;
    my_boards_current.q15_to_mA = VOLTS_PER_12BIT_COUNT / SCALED_VOLTS;

    attn("************* printing out current readings. **************\n");

    i = 0;
    c = 0;
    while(c != LF) {
        if(!(i++ % 30)) {
            warn("Press ENTER to stop or any other key to keep reading\n");
        }

        if(c == '=') {
            DUTY = MAX_DUTY;
            CCW(1);
        }
        else if(c == '-') {
            DUTY = MAX_DUTY;
            CW(1);
        }
        else {
            DUTY = PWM_OFF;
            float_pins();
        }

        printf("volts on ANx pin: %g V (%d counts) -- mA/cnts: %g offset: %d\n",
            1.65 * (1.0 + (double) Fract2Float(my_boards_current.counts)),
            my_boards_current.counts, my_boards_current.q15_to_mA,
            my_boards_current.offset);

        read_xbee(&c, 1);
    }

    printf("now we turn on the EMA with low alpha\n");
    float_pins();
    printf("is the motor floating? %d\n", is_motor_floating());
    set_offset_ema_filter_alpha(0.01);
    my_boards_current.q15_to_mA = mA_cnts;

    attn("************* printing out current readings. **************\n");

    i = 0;
    c = 0;
    char buf[128];
    double ref = 2.25;
    while(c != LF) {
        if(!(i++ % 30)) {
            warn("Press ENTER to stop or any other key to keep reading\n");
        }

        double offset = 1.65*(1+Fract2Float(my_boards_current.offset));
        mA_cnts = my_boards_current.mA - offset;
        double meas = mA_cnts*1000.0/37.0;

        printf("m: %1.4f \t o: %1.4f \t d: %1.4f \t a: %1.4f \t r: %1.4f e: %1.2f\n",
            my_boards_current.mA, offset, mA_cnts, meas, ref, fabs(meas) - ref);

        if(c == '=') {
            DUTY = MAX_DUTY;
            CCW(1);
        }
        else if(c == '-') {
            DUTY = MAX_DUTY;
            CW(1);
        }
        else if(c == 'u') {
            printf("enter new ref:\n");
            if(1 != sscanf(getsn(buf, sizeof(buf)), "%f", &ref)) {
                ref = 2.25;
                printf("invalid input.\n");
            }
            else {
                printf("new value: %f\n", ref);
            }
        }
        else {
            DUTY = PWM_OFF;
            float_pins();
        }




        /*
        printf("current: %g counts: %g (%d) -- mA/cnts: %g offset: %g (%d)\n",
            my_boards_current.mA, (double)
            Fract2Float(my_boards_current.counts), my_boards_current.counts,
            my_boards_current.q15_to_mA, (double)
            Fract2Float(my_boards_current.offset), my_boards_current.offset);
        */

        read_xbee(&c, 1);
    }

    float_pins();
    DUTY = PWM_OFF;

    printf("The current filter coefficients are:\n");
    for(i = 0; i < ADC_SAMPS; i++) {
        printf("cur_filter[%d]: %g (%d)\n", 
            i, (double) Fract2Float(cur_filter[i]), cur_filter[i]);
    }
#if 0
    int j;
    unsigned int time1;
    unsigned int time2;
    long double loop, dsp;
    unsigned short d;
    double current;
    fractional a[128];
    fractional b[128];

    //printf("TAD in cnts: %u\n", cur_clock_period_in_cnts(150));
    //while(1);

    //print_cur_bufs();
    init_cur();
    i = 0;
    while(0) {
        i++;
        while(!AD1CON1bits.DONE);
        if(!(i % 10000))
            printf("last dma write: %#x%x\n", DSADRH, DSADRL);
            //printf("buffer: %u\n", ADC1BUF0);
    }

    c = 0;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));


    //print_cur_bufs();

    for(i=0;i<10; i++){
        //printf("%d) bufA: %u\n", i, BufferA[i]);
        //printf("%d) bufa: %u bufb: %u\n", i, cur_buf_a[i], cur_buf_b[i]);
    }

    //printf("starting ADC module\n");

    for(i=0;i<10; i++){
        //printf("%d) bufA: %u\n", i, BufferA[i]);
        //printf("%d) bufa: %u bufb: %u\n", i, cur_buf_a[i], cur_buf_b[i]);
    }
    //print_cur_bufs();

    //printf("conversion time is: %Lf ns\n", cur_clock_period_in_ns());
    //printf("sampling time is: %Lf ns\n", cur_sampling_time_in_ns());

    current = (double) 0;
    //printf("ADC offset is %u cnts (%f A)\n", Avi, current);

    //printf("reading %d values:\n", PRINT_LEN);
    for(i = 0; i < PRINT_LEN; i++) {
        T1CONbits.TON = 0;
        T1CONbits.TCKPS = 0; // 1:1
        TMR1 = 0;
        PR1 =  -1;
        T1CONbits.TON = 1;
        //d = read_ADC();
        T1CONbits.TON = 0;
        time1 = TMR1;
        //current = (double) ADC_to_current(d);
        //printf("%d) %u cnts (%f A) (overflow? %u)\n", 
        //    i+1, d, current, IFS0bits.T1IF);

        for(j = 0; j < 128; j++) {
            //a[j] = Float2Fract((float)(BufferA[j]/4096.0));
            b[j] = Float2Fract(1/128.0);
        }

        T1CONbits.TON = 0;
        T1CONbits.TCKPS = 0; // 1:1
        TMR1 = 0;
        PR1 =  -1;
        T1CONbits.TON = 1;
        c = VectorDotProduct(128, a, b);
        T1CONbits.TON = 0;
        time2 = TMR1;
        //printf("dsp average: %f (overflow? %u)\n", 
        //    (double)(4096.0*Fract2Float(c)), IFS0bits.T1IF);

        loop = ticks_to_ms(time1, 1);
        dsp = ticks_to_ms(time2, 1);
        //printf("loop: %Lf ms dsp: %Lf ms loop/dsp: %Lf\n", loop, dsp, loop/dsp);

    }

    for(i=0;i<10; i++){
        //printf("%d) bufA: %u\n", i, BufferA[i]);
        //printf("%d) bufa: %u bufb: %u\n", i, cur_buf_a[i], cur_buf_b[i]);
    }
    //print_cur_bufs();
#endif

    attn("Done!\n");
    while(1);

    return 0;
}


#if 0

void print_cur_bufs()
{
    unsigned int ba, bb, ll;
    char c;
    __eds__ fractional *buf_a, *buf_b;

    ll = DSADRL;
    ba = __builtin_dmaoffset(cur_buf_a); 
    bb = __builtin_dmaoffset(cur_buf_b);

    printf("last dma write: %u %x (%u)  (%u) \t", 
            DMALCA, ll, ll - ba + 1, ll - bb + 1); 

    printf("ba: %x -- %x bb: %x -- %x\n", 
            ba, ba+sizeof(cur_buf_a), bb, bb+sizeof(cur_buf_a)); 

    int i, j;
    printf("-------  bufa -------  bufb\n");
    for(i = 0; i < ADC_PINS; i++) {
        buf_a = cur_buf_a[i];
        buf_b = cur_buf_b[i];
        for(j = 0; j < ADC_SAMPS; j++) {
            //printf("[%d, %d]  %x: %d (%f) %x: %d (%f)\n", 
            //        i, j, 
            //        ba, cur_buf_a[i][j], (double) Fract2Float(cur_buf_a[i][j]), 
            printf("[%d, %d]  %x: %d (%f) \t %x: %d (%f)\n", i, j, ba, buf_a[j],
                (double) Fract2Float(buf_a[j]), bb, buf_b[j], (double)
                Fract2Float(buf_b[j])); 

            ba+=2;
            bb+=2;
        }
        read_xbee(&c, 1); 
    }

    printf("BNDRY: %u bufa len: %u bytes  (%u words)\n", 
            sizeof(cur_buf_a), (unsigned) sizeof(cur_buf_a), DMA_TRFRS);
}




#endif
