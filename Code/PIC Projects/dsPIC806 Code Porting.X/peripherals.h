#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

void initialize_cn(void);
void startup(void);
void initialize_pwm(void);
void initialize_uart (void);
void initialize_qei(void);
void initialize_timer1(void);
void initialize_adc(void);
short Read_ADC(void);

#endif	/* PERIPHERALS_H */