#include <math.h>
#include "Temperature.h"


/*float thermistor_resistance(void){
 * /* This function returns the resistance of the thermistor.  This is done by
 * using the voltage divider equation Vout = Vin*R2/(R1+R2), where Vin is 3.3V,
 * R2 is 10k and R1 is the thermistor resistance.
    float voltage, resistance;
    voltage = read_ADC()*3.3/4096;
    resistance = 33000/voltage - 10000;
    return resistance;   
}

float motor_temp(float resistance){
 * /* This function takes the resistance of the thermistor as an input, and
 * using the function provided in the Vishay thermistor datasheet, calculates
 * the temperature in Kelvin.  This was then converted into fahrenheit.
    float temp;
    temp = 1/(3.354016e-03 + 2.933908e-04*log(resistance/10000) + 2*3.494314e-06*log(resistance/10000) - 3*7.712690e-07*log(resistance/10000));
    temp = temp * 9 / 5 - 459.67;
    return temp;
}
*/