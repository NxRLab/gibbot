#ifndef ADC_H
#define	ADC_H

void initialize_ADC(void);
unsigned short read_ADC(void);
void initialize_ADC_Single(void);
unsigned short ADC_Read_Single(void);
void initialize_ADC_Offset(void);
float ADC_to_current(unsigned short data);
float ADC_to_torque(unsigned short data);

extern unsigned short Avi;

#endif	/* ADC_H */

