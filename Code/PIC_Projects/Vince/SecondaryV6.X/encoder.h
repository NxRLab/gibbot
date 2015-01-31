#ifndef ENCODER_H
#define	ENCODER_H

void initialize_QEI(void);
void read_encoder(void);
long read_LOWMAGENC(void);
long read_MOTENC(void);
void write_LOWMAGENC(long val);
void write_MOTENC(long val);
#endif	/* ENCODER_H */

