#include <plib.h>
#include "data.h"
#include "library.h"
#include "math.h"

// Perform startup routines
void startupPIC(void)
{
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableSystemMultiVectoredInt();
}

// Perform initial initialization
void initalizePIC(void)
{
    initLEDs();
    initSerialPort();
}

// Initialize LEDs on G12 and G13 as output and the switch on G6 as input
// G6 has an internal pullup resistor enabled by the bootloader
void initLEDs(void)
{
    TRISGCLR = 0x3000; 
    TRISGSET = 0x0040;
    LED0 = 1;
    LED1 = 1;
}

// Initialize the serial port
// Note: hard wired to use UART3 (= UART2A)
void initSerialPort(void)
{
    int pbClk;
    // Configure the system performance
    pbClk = SYSTEMConfigPerformance(SYS_FREQ);

    UARTConfigure(UART3, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART3, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART3, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART3, pbClk, DESIRED_BAUDRATE_NU32);
    UARTEnable(UART3, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    // Configure UART3 RX Interrupt
    INTEnable(INT_U3RX, INT_ENABLED);
    INTSetVectorPriority(INT_UART_3_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_UART_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
}

// Write a string over the serial port
void WriteString(UART_MODULE id, const char *string) {
  while(*string != '\0') {
  while(!UARTTransmitterIsReady(id));
  UARTSendDataByte(id, *string);
  string++;
  while(!UARTTransmissionHasCompleted(id));
  }
}

// Put a character over the serial port, called by WriteString
void PutCharacter(UART_MODULE id, const char character) {
  while(!UARTTransmitterIsReady(id));
  UARTSendDataByte(id, character);
  while(!UARTTransmissionHasCompleted(id));
}

// 20kHz PWM signal, duty from 0-1000, pin D3
void initTimer2Interrupt(void)
{
    OpenTimer2(T2_ON | T2_PS_1_4, 1000);
    OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    HBridgeDuty = 0;
    SetDCOC4PWM(HBridgeDuty);
}

// 20Hz ISR
void initTimer3Interrupt(void)
{
    OpenTimer3(T3_ON | T3_PS_1_256, 15625);
    mT3SetIntPriority(1);
    mT3ClearIntFlag();
    mT3IntEnable(1);
}

void delaysec(int tref) {
	int t1 = timesec;
	while(timesec - t1 < tref) {};
}

// initialize the analog input
void initAnalogInput(void)
{
    CloseADC10();
    #define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
    #define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_16 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
    #define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_31
    #define PARAM4  ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN5_ANA | ENABLE_AN15_ANA
    OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4,0);
    EnableADC10();
}

void initMagnets(void)
{
    // Setup and turn off electromagnets
    EMAG1 = 0; EMAG2 = 0;
    TRISEbits.TRISE7 = 0; TRISCbits.TRISC1 = 0;

    //Direction Output
    DIR = 1;
    TRISAbits.TRISA9 = 0;

    //g-select Outputs
    GSEL1 = 0; GSEL2 = 0;
    TRISEbits.TRISE2 = 0; TRISCbits.TRISC13= 0;
    
    //0g Inputs
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA4 = 1;
}
