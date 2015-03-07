#ifndef CORE_H__
#define CORE_H__ 
/// @file core.h
/// @brief Maintains the global state of the system, and handles all sensing.  
/// @author Matthew Elwin
/// @version 1.0 
/// @date 2014-02-28


/// @brief Initializes the core module, including the ADC and SPI (for reading the encoder)
void core_init(void);


/// @brief Reads the current ADC value
///
/// @return The adc tick count
short core_adc_read(void);


/// @brief Resets the encoder count
void core_encoder_reset(void);


/// @brief Get the encoder reading
///
/// @return The current encoder reading, in encoder ticks
int core_encoder_read(void);


/// @brief Call this function on your integer gains.
///	   Say you have a gain int kp;
///	   In your initialization code call core_register_int(&kp).  The value can now be saved to and loaded from flash
///	   Details:
///	   	Registers an integer for saving to flash
///	   	This should be called during initialization.	
///	   	Subsequently, core_load() and core_save() can be used to save
///	   	and restore these values from flash memory.
///	   	There is a maximum number of values that can be registered, subsequent values will not be saved
/// @param a pointer to the variable to save
void core_register_int(int * a);


/// @brief Registers a float for saving to flash
///	   Subsequently, core_load() and core_save() can be used to save
///	   and restore these values from flash memory
///	   There is a maximum number of values that can be registered, subsequent values will not be saved
/// @param a pointer to the variable to save
void core_register_float(float * a);


/// @brief Saves all registered values to flash
///	    values are registered using core_register_int and core_register_float
///	    are written to the flash
void core_gains_save();

/// @brief loads all registered values from flash.
///	   if no values were indeed saved, no changes occur
void core_gains_load();

/// @brief A list of constants that determines the current state of the PIC
/*
enum State {
		IDLE=0, 		/// The motors are off
		PWM=1,		/// The motor PWM is directly controlled
	    	TUNE=2, 		/// The current loop is being tuned
		TRACK=3, 		/// The motor is tracking a trajectory
		HOLD=4,		/// The motor is holding its position
                TEST=5 //added by Vince on 1/24/15 to test the output of an error value by the PI controller
	   };
*/
#define COAST 0
#define PWM 1
#define TUNE 2
#define TRACK 3
#define HOLD 4
#define TEST 5


/// @brief The current state of the system. extern means it is instantiated (assigned memory) elsewhere 
//extern enum State core_state;
extern int core_state;
#endif
