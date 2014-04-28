#ifndef __LIBRARY_H__
#define __LIBRARY_H__

// Startup & Initalization
void startupPIC(void);
void initalizePIC(void);
void initLEDs(void);

// Serial Functions
void initSerialPort();
void WriteString(UART_MODULE id, const char *string);
void PutCharacter(UART_MODULE id, const char character);

// Timer Functions
void initTimer2Interrupt(void);
void initTimer3Interrupt(void);
void delaysec(int tref);

// Pin Initalization functions
void initAnalogInput(void);
void initMagnets(void);

// misc fxns
void delay();
void setup_counters();


#endif /* __LIBRARY_H_ */
