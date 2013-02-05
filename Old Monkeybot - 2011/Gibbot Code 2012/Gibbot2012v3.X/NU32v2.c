#include <plib.h>
#include "NU32v2.h"

// have printf send to UART3

void _mon_putc(char c) {
    PutCharacter(UART3, c);
}

void initPIC() {
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);

    initLEDs();
    initSerialNU32v2();

    // Setup and turn off electromagnets
    EMAG1 = 0;
    EMAG2 = 0;
    TRISEbits.TRISE7 = 0;
    TRISCbits.TRISC1 = 0;

    // Direction Output
    DIR = 1;
    TRISAbits.TRISA9 = 0;

    setup_counters();

    CloseADC10();
#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_16 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_31
#define PARAM4  ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN5_ANA | ENABLE_AN15_ANA
    OpenADC10(PARAM1, PARAM2, PARAM3, PARAM4, 0);
    EnableADC10();

    // 20kHz PWM signal, duty from 0-1000, pin D3
    OpenTimer2(T2_ON | T2_PS_1_4, 1000);
    OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    SetDCOC4PWM(0);

    // 200 Hz ISR
    OpenTimer3(T3_ON | T3_PS_1_256, (6250/4 - 1));
    //OpenTimer3(T3_ON | T3_PS_1_256, (62500 - 1));
    mT3SetIntPriority(1);
    mT3ClearIntFlag();
    mT3IntEnable(1);

    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableSystemMultiVectoredInt();
}

// Initialize LEDs on G12 and G13 as output and the switch on G6 as input
// G6 has an internal pullup resistor enabled by the bootloader

void initLEDs(void) {
    TRISGCLR = 0x3000;
    TRISGSET = 0x0040;
}

// Initialize the serial port 
// Note: the NU32v2 is hard wired to use UART3 (= UART2A)

void initSerialNU32v2() {
    int pbClk;
    // Configure the system performance
    pbClk = SYSTEMConfigPerformance(SYS_FREQ);

    UARTConfigure(UART3, UART_ENABLE_PINS_TX_RX_ONLY);
    //UARTSetFifoMode(UART3, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART3, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART3, pbClk, DESIRED_BAUDRATE_NU32);
    UARTEnable(UART3, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    // unbuffered i/o works well for printf and gets, but not for scanf
    //setbuf(stdin, NULL); //no input buffer (for scanf)
    //setbuf(stdout, NULL); //no output buffer (for printf)

    // in the future want to set both to line buffering.
    // This would make the UART a character stream, a
    // different set up would be required for byte streams.

    // Configure UART3 RX Interrupt
    //INTEnable(INT_U3RX, INT_ENABLED);
    //INTSetVectorPriority(INT_UART_3_VECTOR, INT_PRIORITY_LEVEL_2);
    //INTSetVectorSubPriority(INT_UART_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
}

// Put a character over the serial port, called by WriteString

void PutCharacter(UART_MODULE id, const char character) {
    while (!UARTTransmitterIsReady(id));
    UARTSendDataByte(id, character);
    while (!UARTTransmissionHasCompleted(id));
}

int GetCharacter(UART_MODULE id) {
    while (!UARTReceivedDataIsAvailable(id))
        return UARTGetDataByte(id);
}

// Write a string over the serial port

void WriteString(UART_MODULE id, const char *string) {
    while (*string != '\0') {
        PutCharacter(id, *string);
        string++;
    }
}

void ReadUART3(char *message, int max) {
    char data;
    int complete = 0, num_bytes = 0;
    // loop until you get a '\r' or '\n'
    while (!complete) {
        if (UARTReceivedDataIsAvailable(UART3)) {
            data = UARTGetDataByte(UART3);
            if ((data == '\n') || (data == '\r')) {
                complete = 1;
            } else {
                message[num_bytes] = data;
                num_bytes++;
                // roll over if the array is too small
                if (num_bytes >= max) {
                    num_bytes = 0;
                }
            }
        }
    }
    // clear the remaining elements in the array
    int i;
    for (i = num_bytes; i < max; i++) {
        message[i] = '\0';
    }
}

/*
void delaysec(int tref) {
    int t1 = timesec;
    while (timesec - t1 < tref) {
    };
}
*/

void delayms(unsigned t)
// This uses Timer 1, can be changed to another timer.
{
    OpenTimer1(T1_ON | T1_PS_1_256, 0xFFFF);
    while (t--) { // t x 1ms loop
        WriteTimer1(0);
        while (ReadTimer1() < SYS_FREQ / 256 / 1000);
    }
    CloseTimer1();
} // Delayms

void delayus(unsigned t) {
    OpenTimer1(T1_ON | T1_PS_1_256, 0xFFFF);
    while (t--) { // t x 1ms loop
        WriteTimer1(0);
        while (ReadTimer1() < SYS_FREQ / 256 / 1000000);
    }
    CloseTimer1();
}// Delayus
