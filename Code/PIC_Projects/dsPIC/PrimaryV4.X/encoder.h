#ifndef ENCODER_H
#define	ENCODER_H

void initialize_QEI(void);
void clear_MOTENC(void);
void clear_LOWMAGENC(void);
short read_MOTENC(void);
long read_LOWMAGENC(void);
#endif

