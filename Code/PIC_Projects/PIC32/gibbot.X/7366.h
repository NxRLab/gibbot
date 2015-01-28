/**************************
 * 7366.h: 7366R header file
 **************************/
 


//fcn prototypes
void enable_7366(int module, int config1, int flags);
void disable_7366_counting(int module);
void write_7366(int module, int reg, unsigned char *bytearray); 
void read_7366(int module, int reg, unsigned char *bytearray);
void clear_reg_7366(int module, int reg);
 
 
 

