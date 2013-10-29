#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

void Startup(void);
void Initialize_QEI(void);
void Initialize_I2C_Slave(void);
void AllOfTheLights(void);

int sendandwait(char send);
void I2C_Send(void);
#endif	/* PERIPHERALS_H */