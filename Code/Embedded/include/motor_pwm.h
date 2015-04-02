#ifndef MOTOR_PWM_H
#define	MOTOR_PWM_H

/// The master duty cycle to set the BLDC duty cycle for each motor phase
#define DUTY MDC
/// Sets the duty cycle value so there is no active PWM pulses
#define PWM_OFF 0
/// Max duty cycle
#define MAX_DUTY PHASE1
/// Min duty cycle
#define MIN_DUTY 0

// The length of the BLDC commutation pattern (6) plus two float states
#define COMMUTATION_STATES 8
/// Given the hall sensor state #HALL, commutates the motor clockwise
#define CW(hall) (commutate_cw[(hall)]())
/// Given the hall sensor state #HALL, commutates the motor counter-clockwise
#define CCW(hall) (commutate_ccw[(hall)]())


/// Defines a pointer to a commutation function type
typedef void (*commutate_func)(void);

/// An array of commutation functions for turning the motor clockwise
extern commutate_func commutate_cw[COMMUTATION_STATES];

/// An array of commutation functions for turning the motor counter-clockwise
extern commutate_func commutate_ccw[COMMUTATION_STATES];

/// Returns true of the motor PWM module is on
extern bool is_motor_pwm_on();
/// Returns true is all motor leads are floating
extern bool is_motor_floating();
/// Initializes the PWM module for the motor
extern void init_motor_pwm(void);
/// Returns the number of milliseconds given a PWM period count and prescaler
extern long double pwm_ticks_to_ms(unsigned int pwmcnts, int prescaler, 
                                    bool centered);
/// Returns the PWM period count given the desired milliseconds and prescaler 
extern unsigned int ms_to_pwm_ticks(long double ms, int prescaler, bool centered);
/// Sets the relevant PWM period generators to the desired time in milliseconds 
extern void set_pwm_ticks(long double ms, VUI *con2, VUI *prd, VUI *dc, 
                                    bool centered);
/// Returns the amount of dead time generated from PWM counts and a prescaler
extern long double dead_time_ticks_to_ms(unsigned int cnts, int prescaler);
/// Returns the dead time in counts given the desired time and prescaler
extern unsigned int ms_to_dead_time_ticks(long double ms, int prescaler);

/// Floats the Maxon EC 60 Flat motor pins
void float_pins();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 1
extern void cw1();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 2
extern void cw2();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 3
extern void cw3();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 4
extern void cw4();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 5
extern void cw5();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 6
extern void cw6();

/// Sets the Maxon EC 60 Flat motor pins based on commutation state 1
extern void ccw1();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 2
extern void ccw2();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 3
extern void ccw3();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 4
extern void ccw4();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 5
extern void ccw5();
/// Sets the Maxon EC 60 Flat motor pins based on commutation state 6
extern void ccw6();

#endif	/* MOTOR_PWM_H */

