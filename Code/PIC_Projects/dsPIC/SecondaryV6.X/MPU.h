#ifndef MPU_H
#define	MPU_H

void initialize_MPU(void);
void write_MPU();
void read_Accel(unsigned char *data);
void read_Gyro(unsigned char *data);
void read_MPU_test(unsigned char *data);
double Accel_convert(unsigned char *data);
double Gyro_convert(unsigned char *data);
void read_Mag(unsigned char *data);

#endif	/* MPU_H */
