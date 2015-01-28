/**************************
 * 7366.h: 7366R header file
 **************************/
 
#define MOT_SS LATDbits.LATD1
#define MAG1_SS LATEbits.LATE6
#define MAG2_SS LATEbits.LATE9

#define MOT 1
#define MAG1 2
#define MAG2 3

//fcn prototypes
void delay();
void setup_counters();
void enable_7366(int module, int config1, int flags);
void disable_7366_counting(int module);
void write_7366(int module, int reg, unsigned char *bytearray); 
void read_7366(int module, int reg, unsigned char *bytearray);
void clear_reg_7366(int module, int reg);
 
//Use the following to specifity the number of bytes the counter is
// Valid range is 1-4
#define COUNTER_BYTES 2

//1,2,3,4 for SPI1, SPI2, SPI3, or SPI4
#define SPICHN 1
 
/* Configuration words - Use at most ONE per group */
//Count modes
#define NON_QUADRATURE 0
#define QUADRATURE_X1 0x01
#define QUADRATURE_X2 0x02
#define QUADRATURE_X4 0x03
//Running modes
#define FREE_RUN 0
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C
//Index modes
#define DISABLE_INDX 0
#define INDX_LOADC 0x10
#define INDX_RESET 0x20
#define INDX_LOADO 0x30
//Index synchronous modes
#define ASYNCH_INDX 0
#define SYNCH_INDX 0x80
//Clock filter modes
#define FILTER_1 0
#define FILTER_2 0x80

/* Valid flags- Any of these config words can be ORed together */
#define NO_FLAGS 0
#define IDX_FLAG 0x10;
#define CMP_FLAG 0x20;
#define BW_FLAG 0x40;
#define CY_FLAG 0x80;

/* Register list: for use with write_7366, read_7366, and clear_reg_7366 functions */
#define MDR0 0x1
#define MDR1 0x2
#define DTR 0x3		//1-4 bytesw
#define CNTR 0x4	//1-4 bytesw
#define OTR 0x5		//1-4 bytesw
#define STR 0x6
 

