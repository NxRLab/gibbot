#include <p32xxxx.h>
#include <plib.h>

#define SYS_FREQ 80000000        // 80 MHz
#define BAUDRATE 115200
#define MAX_ADC 1023
#define PWM_PRD MAX_ADC
#define SAMPLE_TIME 10000000//10
#define ADC_PIN 1
#define USER PORTCbits.RC13
#define LED3 LATAbits.LATA3
#define LED1 LATAbits.LATA4
#define LED2 LATAbits.LATA5

#define PCHANEN 1
#define NCHANEN 0
#define H1 LATDbits.LATD0
#define L1 LATDbits.LATD1
#define H2 LATDbits.LATD2
#define L2 LATDbits.LATD3
#define H3 LATDbits.LATD4
#define L3 LATDbits.LATD5

#define S1 PORTDbits.RD6
#define S2 PORTDbits.RD7
#define S3 PORTDbits.RD13

void init_cn_pins(void);
void init_h_bridges(void);
void init_uart1(int);
void init_adc(void);
int read_adc(unsigned int pin);

volatile int speed = 0;

void main(void)
{
    init_cn_pins();
    init_uart1(BAUDRATE);
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD13 = 1;


    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableSystemMultiVectoredInt();
    LED2 = 0;
    while (1) {

        // if the motor stops, trigger an interrupt
        if(!USER) {
            IFS1bits.CNIF = 1;
        }
    }
}

void High(int pin){
    if(pin == 1){
        H1 = PCHANEN;
        L1 = !NCHANEN;
    } else if(pin == 2){
        H2 = PCHANEN;
        L2 = !NCHANEN;
        
    } else if(pin == 3){
        H3 = PCHANEN;
        L3 = !NCHANEN;
    } 
}

void Low(int pin){
    if(pin == 1){
        H1 = !PCHANEN;
        L1 = NCHANEN;
    } else if(pin == 2){
        H2 = !PCHANEN;
        L2 = NCHANEN;
        
    } else if(pin == 3){
        H3 = !PCHANEN;
        L3 = NCHANEN;
    } 
}

void Float(int pin){
    if(pin == 1){
        H1 = !PCHANEN;
        L1 = !NCHANEN;
    } else if(pin == 2){
        H2 = !PCHANEN;
        L2 = !NCHANEN;
        
    } else if(pin == 3){
        H3 = !PCHANEN;
        L3 = !NCHANEN;
        
    }
}

// looking into longer shaft, CCW rotation
void state1() {High(1); Float(2); Low(3);}
void state2() {Float(1); Low(2); High(3);}
void state3() {High(1); Low(2); Float(3);}
void state4() {Low(1); High(2); Float(3);}
void state5() {Float(1); High(2); Low(3);}
void state6() {Low(1); Float(2); High(3);}

/*
// looking into longer shaft, CW rotation
void state1() {AIN = 0; CIN = speed; LATESET = 5;}
void state2() {BIN = speed; CIN = 0; LATESET = 3;}
void state3() {AIN = 0; BIN = speed; LATESET = 6;}
void state4() {AIN = speed; BIN = 0; LATESET = 6;}
void state5() {BIN = 0; CIN = speed; LATESET = 3;}
void state6() {AIN = speed; CIN = 0; LATESET = 5;}
*/

void __ISR(_CHANGE_NOTICE_VECTOR, ipl3) CNHandler(void)
{
    char state = 0;
    // Is this an CN interrupt?
    if (IFS1bits.CNIF) {
        LED1 = !S2;
        LED2 = !S1;
        LED3 = S3;
        state = (S1 << 2) | (S2 << 1) | S3;
        //printf("state: %d\tspeed: %d\r", state, speed);
        LATECLR = 7;
        switch(state) {
            case 1:
                /*
                AIN = speed;
                CIN = 0;
                LATESET = 5;*/
                state1();
                break;
            case 2:
                /*BIN = 0;
                CIN = speed;
                LATESET = 3;*/
                state2();
                break;
            case 3:
                /*AIN = speed;
                BIN = 0;
                LATESET = 6;*/
                state3();
                break;
            case 4:
                /*AIN = 0;
                BIN = speed;
                LATESET = 6;*/
                state4();
                break;
            case 5:
                /*BIN = speed;
                CIN = 0;
                LATESET = 3;*/
                state5();
                break;
            case 6:
                /*AIN = 0;
                CIN = speed;
                LATESET = 5;*/
                state6();
                break;
        }

        // clear mismatch condition
        PORTD;
        IFS1bits.CNIF = 0;
    }
}


void init_cn_pins()
{
    // initialization code from PIC32 RM Sec. 12, p. 15

    // make input pins
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD13 = 1;

    // turn on CN module
    CNCONbits.ON = 1;

    // set up change notification (CN) interrupt
    CNENbits.CNEN15 = 1; //D6
    CNENbits.CNEN16 = 1; //D7
    CNENbits.CNEN19 = 1; //D13


    // clear mismatch conditions
    PORTD;

    // set interrupt priority
    IPC6bits.CNIP = 3;
    IPC6bits.CNIS = 0;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

    // enable pull-up resistor -- what value are they pulled up to?
    //CNPUEbits.CNPUE14 = 1;
    //CNPUEbits.CNPUE15 = 1;
    //CNPUEbits.CNPUE16 = 1;
}

void _mon_putc(char c) {
    // echo data out UART1
    while (U1STAbits.UTXBF); // wait until tx buffer isn't full
    U1TXREG = c;
}

void init_uart1(int baud) {
    // redirect STDOUT to UART1 with no buffering
    setbuf(stdout, NULL);

    // set baudrate to 115,200 bps
    U1MODEbits.BRGH = 0;
    U1BRG = ((SYS_FREQ / baud) / 16) - 1;

    // transmit 8 data bits, no parity bit, and 1 stop bit (a.k.a 8N1 setup)
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

    // enable U1TX
    U1STAbits.UTXEN = 1;

    // finally, turn on the UART
    U1MODEbits.ON = 1;
}

void init_adc(void) {
    AD1PCFG = 0; // entire port B is used for analog input
    AD1CON3bits.ADCS = 3; // ADC clock period is Tad = 2 * ADCS * Tpb
    AD1CON1bits.ADON = 1; // turn on A/D converter
}

int read_adc(unsigned int pin) {
    AD1CHSbits.CH0SA = pin; // connect pin to MUXA for sampling
    AD1CON1bits.SAMP = 1; // start sampling
    WriteCoreTimer(0); // core timer has 1:2 prescaler
    while (ReadCoreTimer() < SAMPLE_TIME); // sample for more than 200 ns
    AD1CON1bits.SAMP = 0; // stop sampling and start converting
    while (!AD1CON1bits.DONE); // wait for the conversion process to finish
    return ADC1BUF0; // read the buffer with the result
}