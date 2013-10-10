#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

void Initialize_CN(void);
void Startup(void);
void Initialize_PWM(void);
void Initialize_UART(void);
void Initialize_QEI(void);
void Initialize_Timer1(void);
void Initialize_I2C(void);
void Initialize_ADC(void);
void AllOfTheLights(void);
short Read_ADC(void);

#endif	/* PERIPHERALS_H */