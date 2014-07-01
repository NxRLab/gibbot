#ifndef ENCODER_H
#define	ENCODER_H

void initialize_QEI(void);
void read_encoder(void);
long read_LOWMAGENC(void);
long read_MOTENC(void);
#endif	/* ENCODER_H */

