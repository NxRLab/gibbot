#ifndef MAGNET_ENC_H
#define	MAGNET_ENC_H

extern bool is_magnet_enc_on();
extern long read_magnet_enc();
extern void write_magnet_enc(long int value);
extern void init_magnet_enc(long int counts_per_revolution);

extern Encoder my_magnet_enc;

#endif /* MAGNET_ENC_H */

