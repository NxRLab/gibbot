#ifndef ENCODER_H
#define	ENCODER_H

void initialize_QEI(void);
void write_MOTENC(long val);
void write_LOWMAGENC(long val);
void write_TOPMAGENC(long val);
long read_MOTENC(void);
long read_LOWMAGENC(void);
long read_TOPMAGENC(void);
int encoder_to_angle(long val, char num);
void initialize_encoder_values(long val1,long val2,long val3);
#endif

