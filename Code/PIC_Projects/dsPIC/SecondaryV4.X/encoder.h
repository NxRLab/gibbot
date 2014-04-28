#ifndef ENCODER_H
#define	ENCODER_H

void initialize_encoders(void);
void encoder_Read(char which);
#define MOTENC    0b00000100
#define LOWMAGENC 0b00000010
#endif	/* ENCODER_H */

