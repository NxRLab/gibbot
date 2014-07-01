#ifndef ENCODER_H
#define	ENCODER_H

void initialize_QEI(void);
void write_MOTENC(long val);
void write_LOWMAGENC(long val);
void write_TOPMAGENC(long val);
long read_MOTENC(void);
long read_LOWMAGENC(void);
long read_TOPMAGENC(void);
#endif

