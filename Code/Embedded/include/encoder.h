#ifndef ENCODER_H
#define	ENCODER_H

struct Encoder {
    /// most recent encoder value
    long int value;
    /// last read of POSxCNTL register
    long int low16;
    /// last read of POSxHLD register
    long int high16;
    /// the encoder's offset position, this can be changed at any time
    long int offset;
    /// the encoder's resolution in counts per revolution
    long int cpr;
    /// the encoder's read function
    long int (*read)(void);
    /// the encoder's write function
    void (*write)(long int value);
};

typedef struct Encoder Encoder;

#define LOW_ENC_MASK 0xFFFF
#define HI_ENC_SHIFT 16
#define MODULO_COUNT 6
#define DEGREES(enc) ((enc.read() - enc.offset) * 360.0L / enc.cpr)

#endif /* ENCODER_H */

